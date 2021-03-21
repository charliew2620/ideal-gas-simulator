#include "histogram.h"

#include "particle.h"

namespace idealgas {
using glm::vec2;

Histogram::Histogram(const int bottom_wall, const int top_wall,
                     const int left_wall, const int right_wall,
                     const std::string& color, const int amount,
                     const double mass) {
  bottom_wall_ = bottom_wall;
  top_wall_ = top_wall;
  left_wall_ = left_wall;
  right_wall_ = right_wall;
  color_ = color;
  amount_ = amount;
  mass_ = mass;
}

void Histogram::DrawHistogram(const std::vector<Particle>& particles) {
  DrawTitle();
  DrawXTitle();
  DrawYTitle();
  DrawXAxis();
  DrawYAxis();

  ci::gl::color(ci::Color(color_.c_str()));
  ci::gl::drawStrokedRect(
      ci::Rectf(vec2(left_wall_, top_wall_), vec2(right_wall_, bottom_wall_)));

  particles_speeds_ = GetSpeedsOfParticlesList(particles);

  CountParticlesInEachBar();
  DrawBars();
}

const std::vector<double> Histogram::GetSpeedsOfParticlesList(
    const std::vector<Particle>& particles) const {
  std::vector<double> particles_speeds;

  if (particles.size() > 0) {
    for (Particle particle : particles) {
      particles_speeds.push_back(particle.GetSpeed());
    }
  }
  return particles_speeds;
}

void Histogram::DrawXAxis() {
  double speed_label = 0;
  double left_bound = left_wall_;
  double right_bound = right_wall_;

  double bar_range = (right_bound - left_bound) / kNumberOfBars;
  double speed_interval = max_speed_ / kNumberOfBars;

  ci::gl::color(ci::Color("white"));

  for (double bar = 0; bar <= max_speed_; bar += speed_interval) {
    ci::gl::drawStringCentered(std::to_string((size_t)speed_label),
                               glm::vec2(left_bound, (bottom_wall_ + 5)),
                               ci::Color("white"),
                               ci::Font("Times New Roman", 15));
    left_bound += bar_range;
    speed_label++;
  }
}

void Histogram::DrawYAxis() {
  double speed_label = 0;
  double lower_bound = bottom_wall_;

  ci::gl::color(ci::Color("white"));

  for (double bar = 0; bar <= amount_; bar += increment) {
    ci::gl::drawStringCentered(std::to_string((size_t)speed_label),
                               glm::vec2(left_wall_ - 10, lower_bound),
                               ci::Color("white"),
                               ci::Font("Times New Roman", 15));
    lower_bound -= amount_;
    speed_label += increment;
  }
}

void Histogram::DrawTitle() {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStringCentered(
      "Speeds of " + color_ + " particles with mass " +
          std::to_string((size_t) mass_),
      glm::vec2((right_wall_ + left_wall_) / 2, top_wall_ - 20),
      ci::Color("white"), ci::Font("Times New Roman", 20));
}

void Histogram::DrawYTitle() {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStringCentered(
      "Number of\nparticles",
      glm::vec2(left_wall_ - 50, (top_wall_ + bottom_wall_) / 2),
      ci::Color("white"), ci::Font("Times New Roman", 15));
}
void Histogram::DrawXTitle() {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStringCentered(
      "Speeds", glm::vec2((right_wall_ + left_wall_) / 2, bottom_wall_ + 20),
      ci::Color("white"), ci::Font("Times New Roman", 15));
}

void Histogram::CountParticlesInEachBar() {
  double speed_range = max_speed_ / kNumberOfBars;
  min_speed_ = *min_element(particles_speeds_.begin(), particles_speeds_.end());

  // Counts number of particles in speed range and adds the count to the bars_
  // list
  for (size_t bar = 0; bar < bars_.size(); bar++) {
    int particle_count = 0;
    for (size_t particle_speed = 0; particle_speed < particles_speeds_.size();
         particle_speed++) {
      if (particles_speeds_[particle_speed] >= min_speed_ &&
          particles_speeds_[particle_speed] < min_speed_ + speed_range) {
        particle_count++;
      }
    }
    bars_[bar] = particle_count;
    min_speed_ += speed_range;
  }
}

void Histogram::DrawBars() {
  double left_bound = left_wall_;
  double right_bound = right_wall_;

  double bar_range = (right_bound - left_bound) / kNumberOfBars;

  // Draws the height each bar in histogram based on the number of particles in
  // each bar_ index
  for (size_t bar = 0; bar < bars_.size(); bar++) {
    double height = bottom_wall_ - bars_[bar] * factor;
    ci::gl::color(ci::Color(color_.c_str()));
    ci::gl::drawSolidRect(ci::Rectf(vec2(left_bound, bottom_wall_),
                                    vec2(left_bound + bar_range, height)));
    left_bound += bar_range;
  }
}
}  // namespace idealgas
