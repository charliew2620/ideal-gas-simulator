#include "histogram.h"
#include "particle.h"

namespace idealgas {
using glm::vec2;

Histogram::Histogram(const int bottom_wall, const int top_wall,
                     const int left_wall, const int right_wall, const std::string& color) {
  bottom_wall_ = bottom_wall;
  top_wall_ = top_wall;
  left_wall_ = left_wall;
  right_wall_ = right_wall;
  color_ = color;

  histogram_length_ = right_wall_ - left_wall_;
}

//To get mass, call the getter? and make a method or constructor
void Histogram::DrawHistogram(const std::vector<Particle> &particles) {

  DrawXAxis();
  DrawYAxis();

  ci::gl::color(ci::Color(color_.c_str()));
  ci::gl::drawStrokedRect(
      ci::Rectf(vec2(left_wall_, top_wall_), vec2(right_wall_, bottom_wall_)));

  particles_speeds_ = GetSpeedsOfParticlesList(particles);

  CountParticlesInEachBar();
  DrawBars();
}

std::vector<double> Histogram::GetSpeedsOfParticlesList(const std::vector<Particle> &particles) {
  std::vector<double> particles_speeds;
  if (particles.size() >  0) {
    for (Particle particle : particles) {
      particles_speeds.push_back(particle.GetSpeed());
    }
  }
  return particles_speeds;
}
void Histogram::DrawXAxis() {
  double left_bound = left_wall_;
  double right_bound = right_wall_;
  double bar_range = (right_bound - left_bound) / kNumberOfBars;
  ci::gl::color(ci::Color("white"));

  double speed_label = 0;

  for (double bar = 0; bar <= max_speed_; bar++) {

    ci::gl::drawStringCentered(std::to_string((size_t) speed_label), glm::vec2
                                   (left_bound, (bottom_wall_ + 5)),
                               ci::Color("white"),
                               ci::Font("Times New Roman", 15));
    left_bound += bar_range;
    speed_label++;
  }
}
void Histogram::DrawYAxis() {
  int upper_bound = top_wall_;
  double lower_bound = bottom_wall_;
  double bar_range = 25;
  ci::gl::color(ci::Color("white"));

  double speed_label = 0;

  for (double bar = 0; bar <= 30; bar += 5) {

    ci::gl::drawStringCentered(std::to_string((size_t) speed_label), glm::vec2
                                   (left_wall_ - 10, lower_bound),
                               ci::Color("white"),
                               ci::Font("Times New Roman", 15));
    lower_bound -= 25;
    speed_label += 5;
  }
}
void Histogram::CountParticlesInEachBar() {
  min_speed_ = *min_element(particles_speeds_.begin(), particles_speeds_.end());

  double speed_range = max_speed_ / kNumberOfBars;

  //Should fill bars_ with number of particles in specified speed range
  for (size_t i = 0; i < bars_.size(); i++) {
    int particle_count = 0;
    for (size_t j = 0; j < particles_speeds_.size(); j++) {
      if (particles_speeds_[j] >= min_speed_ && particles_speeds_[j] < min_speed_ + speed_range) {
        particle_count++;
      }
    }
    bars_[i] = particle_count;
    min_speed_ += speed_range;

  }
}
void Histogram::DrawBars() {
  double left_bound = left_wall_;
  double right_bound = right_wall_;

  double bar_range = (right_bound - left_bound) / kNumberOfBars;

  //Should draw the graph here
  for (size_t i = 0; i < bars_.size(); i++) {
    double height = bottom_wall_ - bars_[i] * 5;
    ci::gl::color(ci::Color(color_.c_str()));
    ci::gl::drawSolidRect(ci::Rectf(vec2(left_bound, bottom_wall_), vec2(left_bound + bar_range, height)));
    left_bound += bar_range;

  }
}

}
