

#include <string>
#include "particle.h"
namespace idealgas {
class Histogram {

  //3 separate graphs, not combined
 public:
  Histogram(const int bottom_wall, const int top_wall, const int left_wall,
            const int right_wall, const std::string& color);

  void DrawHistogram();

  void CreateHistogram();

  void UpdateHistogram(const std::vector<Particle> &particle);

  std::vector<Particle> GetSpeedsOfParticlesList();

 private:

  int bottom_wall_;
  int top_wall_;
  int left_wall_;
  int right_wall_;
  std::string color_;

  std::vector<Particle> particles_;

  double max_speed_;
  double min_speed_;
};

}
