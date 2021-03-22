#include <string>

#include "cinder/gl/gl.h"
#include "particle.h"
namespace idealgas {
/**
 * Histogram that graphs the particles and their speeds. The class updates
 * their speeds every frame and shows them in the simulation.
 */
class Histogram {
 public:
  Histogram(const int bottom_wall, const int top_wall, const int left_wall,
            const int right_wall, const std::string& color, const int amount,
            const double mass);

  /**
   * Draws all the components of the histogram.
   * @param particles passed all of the same mass from gas simulation app class.
   */
  void DrawHistogram(const std::vector<Particle>& particles);

  /**
   * Gets the speed of every particle passed in the list.
   * @param particles passed all of the same mass from gas simulation app class.
   * @return the particles' speeds as a list.
   */
  const std::vector<double> GetSpeedsOfParticlesList(
      const std::vector<Particle>& particles) const;

  const std::vector<int> GetBarsList() const;

 private:
  int bottom_wall_;
  int top_wall_;
  int left_wall_;
  int right_wall_;
  int amount_;
  std::string color_;
  double mass_;
  std::vector<double> particles_speeds_;

  const static int kNumberOfBars = 10;
  std::vector<int> bars_ = std::vector<int>(kNumberOfBars);
  constexpr const static double max_speed_ = 10;
  constexpr const static double factor = 5;
  constexpr const static double increment = 5;

  /**
   * Counts the number of particles to be drawn out in each bar
   */
  void CountParticlesInEachBar();

  /**
   * Draws the bars of the histogram.
   */
  void DrawBars();

  /**
   * Draws the X axis.
   */
  void DrawXAxis();

  /**
   * Draws the Y axis.
   */
  void DrawYAxis();

  /**
   * Draws the title.
   */
  void DrawTitle();

  /**
   * Draws the Y-axis title.
   */
  void DrawYTitle();

  /**
   * Draws the X-axis title.
   */
  void DrawXTitle();
};

}  // namespace idealgas
