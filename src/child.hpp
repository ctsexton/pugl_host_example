#pragma once
#include "pugl/pugl.hpp"
#include "pugl/cairo.hpp"
#include <cairomm/cairomm.h>


class ChildView : public pugl::View
{
public:
  ChildView(pugl::World& world, PuglRect view_frame)
      : pugl::View{world}
  {
    setEventHandler(*this);
    setFrame(view_frame);
    setBackend(pugl::cairoBackend());
  }

  pugl::Status onEvent(const pugl::ExposeEvent&) noexcept {
    Cairo::Context ctx(static_cast<cairo_t*>(context()));
    ctx.set_source_rgb(0, 0, 1);
    ctx.paint();
    return pugl::Status::success;
  }

  pugl::Status onEvent(const pugl::ConfigureEvent& event) noexcept {
    return pugl::Status::success;
  }

  template<PuglEventType t, class Base>
  pugl::Status onEvent(const pugl::Event<t, Base>&) noexcept
  {
       return pugl::Status::success;
  }
};
