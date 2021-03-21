

#include <string>
#include "particle.h"
#include "cinder/gl/gl.h"
namespace idealgas {
class Histogram {

  //3 separate graphs, not combined

  // create 5 bars, size depends of max - min speed range, find number of particles within each size range of bar
 public:
  Histogram(const int bottom_wall, const int top_wall, const int left_wall,
            const int right_wall, const std::string& color);

  void DrawHistogram(const std::vector<Particle> &particle);

  void UpdateHistogram(const std::vector<Particle> &particle);

  std::vector<double> GetSpeedsOfParticlesList(const std::vector<Particle> &particles);

 private:

  int bottom_wall_;
  int top_wall_;
  int left_wall_;
  int right_wall_;
  std::string color_;

  std::vector<Particle> particles_;
  std::vector<double> particles_speeds_;

  const static int kNumberOfBars = 10;
  std::vector<int> bars_ = std::vector<int>(kNumberOfBars);
  double max_speed_;
  double min_speed_;

  double histogram_length_;

  std::vector<int> particles_in_bar_;

  void DrawXAxis();

  void DrawYAxis();
};

}
