#include "gas_container.h"

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer() {

}

void GasContainer::Display() const {
  // This function has a lot of magic numbers; be sure to design your code in a way that avoids this.
  ci::gl::color(ci::Color("red"));
  ci::gl::drawSolidCircle(vec2(x_position_, y_position_), 10);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(108, 767), vec2(767, 108)));
}

void GasContainer::AdvanceOneFrame() {
  ++x_position_;
  ++y_position_;
}

}  // namespace idealgas
