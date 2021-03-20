

#include <string>
namespace idealgas {
class Histogram {

  //3 separate graphs, not combined
 public:
  Histogram(const int bottom_wall, const int top_wall, const int left_wall,
            const int right_wall, const std::string& color);

  void DrawHistogram();

  void CreateHistogram();

  void UpdateHistogram();

 private:

  int bottom_wall_;
  int top_wall_;
  int left_wall_;
  int right_wall_;
  std::string color_;
};

}
