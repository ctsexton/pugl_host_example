#include <iostream>
#include <string>
#include "pugl/pugl.hpp"
#include "suil/suil.h"
#include "lv2/core/lv2.h"
#include "lv2/ui/ui.h"
#include "lilv/lilvmm.hpp"
#include "parent.hpp"
#include "child.hpp"
#include "urid_map.hpp"

void write_func(SuilController controller, uint32_t port_index, uint32_t bufsize, uint32_t protocol, void const* buffer) {
  // do nothing
};

unsigned int index_func(SuilController controller, const char* port_symbol) {
  return 0;
};

unsigned int subscribe_func(SuilController controller, uint32_t port_index, uint32_t protocol, const LV2_Feature* const* features) {
  return 0;
};

unsigned int unsubscribe_func(SuilController controller, uint32_t port_index, uint32_t protocol, const LV2_Feature* const* features) {
  return 0;
};

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Usage: ./PuglHost <plugin_uri> OR ./PuglHost DUMMY_CHILD" << std::endl;
    return 0;
  }
  auto first_arg = std::string(argv[1]);
  Lilv::World lilv_world;
  lilv_world.load_all();
  Lilv::Plugins plugins = lilv_world.get_all_plugins();

  if (first_arg == std::string("DUMMY_CHILD")) {
    pugl::World pugl_world {pugl::WorldType::program};
    PuglRect parent_frame = {0, 0, 512, 512};
    PuglRect child_frame = {20, 20, 472, 472};
    ParentView parent_view {pugl_world, parent_frame};
    ChildView child_view {pugl_world, child_frame};
    child_view.setParentWindow(parent_view.nativeWindow());
    parent_view.show();
    child_view.show();

    while (!parent_view.quit()) {
      pugl_world.update(0.1);
    }
    return 0;
  } else if (first_arg == std::string("--list-all-plugins")) {
    LilvIter* pli = plugins.begin();
    while(!plugins.is_end(pli)) {
      Lilv::Plugin plg = plugins.get(pli);
      std::cout << plg.get_uri().as_string() << std::endl;
      pli = plugins.next(pli);
    }
    return 0;
  }
  auto SELECTED_PLUGIN_URI = first_arg;

  Lilv::Node plugin_uri = lilv_world.new_uri(SELECTED_PLUGIN_URI.c_str());
  Lilv::Plugin plugin = plugins.get_by_uri(plugin_uri);
  Lilv::UIs plugin_uis = plugin.get_uis();
  if (plugin_uis.begin() == nullptr) {
    std::cout << "Plugin does not have a UI\n";
    return 0;
  }
  Lilv::UI first_ui = plugin_uis.get(plugin_uis.begin());
  Lilv::Node ui_uri = first_ui.get_uri();
  Lilv::Node ui_bundle_uri = first_ui.get_bundle_uri();
  Lilv::Node ui_binary_uri = first_ui.get_binary_uri();

  std::cout << "Loading UI: " << ui_uri.as_string() << std::endl;
  std::cout << "Bundle URI: " << ui_bundle_uri.as_string() << std::endl;
  std::cout << "Binary UI: " << ui_binary_uri.as_string() << std::endl;

  suil_init(&argc, &argv, SUIL_ARG_NONE);
  SuilHost* host = suil_host_new(write_func, index_func, subscribe_func, unsubscribe_func);
  SuilController controller;

  pugl::World pugl_world{pugl::WorldType::program};
  PuglRect parent_frame = {0, 0, 512, 512};
  ParentView view{pugl_world, parent_frame};
  view.show();

  LV2_URID_Map urid_map {
    NULL,
    urid_map_fn
  };
  const LV2_Feature map_feature = {
    LV2_URID__map, &urid_map
  };
  const LV2_Feature parent_feature = {
    LV2_UI__parent, (void*)view.nativeWindow()
  };
  const LV2_Feature idle_feature = {
    LV2_UI__idleInterface, NULL
  };
  const LV2_Feature* ui_features[] = {
    &map_feature,
    &parent_feature,
    &idle_feature,
    NULL
  };

  auto instance = suil_instance_new(
    host, 
    controller, 
    LV2_UI__X11UI, 
    plugin_uri.as_uri(), 
    ui_uri.as_uri(), 
    LV2_UI__X11UI, 
    lilv_file_uri_parse(ui_bundle_uri.as_uri(), NULL), 
    lilv_file_uri_parse(ui_binary_uri.as_uri(), NULL), 
    ui_features
  );

  const LV2UI_Idle_Interface* idle_iface = (const LV2UI_Idle_Interface*)suil_instance_extension_data(instance, LV2_UI__idleInterface);

  while (!view.quit()) {
    pugl_world.update(1.0 / 30.0);
    idle_iface->idle(suil_instance_get_handle(instance));
  }

  return 0;
}
