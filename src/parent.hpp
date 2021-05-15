#pragma once
#include "pugl/pugl.hpp"
#include "pugl/cairo.hpp"
#include <cairomm/cairomm.h>


class ParentView : public pugl::View {
  public:
    ParentView(pugl::World& world, PuglRect view_frame) : pugl::View{world} {
      setEventHandler(*this);
      setFrame(view_frame);
      setWindowTitle("Pugl Host Test");
      setDefaultSize(frame().width, frame().height);
      setMinSize(64, 64);
      setMaxSize(1000, 1000);
      setAspectRatio(1, 1, 16, 9);
      setBackend(pugl::cairoBackend());
      realize();
    }

    pugl::Status onEvent(const pugl::CloseEvent& event) noexcept {
      _quit = true;
      return pugl::Status::success;
    };

    pugl::Status onEvent(const pugl::ConfigureEvent& event) noexcept {
      return pugl::Status::success;
    };

    pugl::Status onEvent(const pugl::ExposeEvent& event) noexcept {
      Cairo::Context ctx(static_cast<cairo_t*>(context()));
      ctx.set_source_rgb(1, 0, 0);
      ctx.paint();
      return pugl::Status::success;
    };
    // Fallback handler for all other events
    template<PuglEventType t, class Base>
    pugl::Status onEvent(const pugl::Event<t, Base>&) noexcept
    {
      return pugl::Status::success;
    }

    bool quit() const { return _quit; }

    bool _quit { false };
};
