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

  ci::gl::color(ci::Color(color_.c_str()));
  ci::gl::drawStrokedRect(
      ci::Rectf(vec2(left_wall_, top_wall_), vec2(right_wall_, bottom_wall_)));
  particles_speeds_ = GetSpeedsOfParticlesList(particles);

  max_speed_ = *max_element(particles_speeds_.begin(), particles_speeds_.end());
  min_speed_ = *min_element(particles_speeds_.begin(), particles_speeds_.end());

  double speed_range = 10 / kNumberOfBars;

  //Should fill bars_ with number of particles in specified speed range
  for (size_t i = 0; i < bars_.size(); i++) {
    int particle_count = 0;
    for (size_t j = 0; j < particles_speeds_.size(); j++) {
      if (particles_speeds_[i] >= min_speed_ && particles_speeds_[i] < min_speed_ + speed_range) {
        particle_count++;
      }
    }
    bars_[i] = particle_count;
    min_speed_ += speed_range;

  }

  double left_bound = left_wall_;
  double right_bound = right_wall_;

  double bar_range = (right_bound - left_bound) / kNumberOfBars;

  //Should draw the graph here
  for (size_t i = 0; i < bars_.size(); i++) {
    int height = bottom_wall_ - bars_[i] * 2;
    ci::gl::color(ci::Color(color_.c_str()));
    ci::gl::drawSolidRect(ci::Rectf(vec2(left_bound, bottom_wall_), vec2(left_bound + bar_range, height)));
    left_bound += bar_range;

  }
}

void Histogram::UpdateHistogram(const std::vector<Particle> &particles) {

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


  for (double bar = 0; bar <= kNumberOfBars; bar++) {

    ci::gl::drawStringCentered(std::to_string((size_t) speed_label), glm::vec2
                                   (left_bound, (bottom_wall_ + 5)),
                               ci::Color("white"),
                               ci::Font("Times New Roman", 15));
    left_bound += bar_range;
    speed_label++;
  }
}
void Histogram::DrawYAxis() {
}

}
