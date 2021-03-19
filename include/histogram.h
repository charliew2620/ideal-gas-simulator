


namespace idealgas {
class Histogram {

  //3 separate graphs, not combined
 public:
  Histogram();

  void DrawHistogram(const int bottom_wall, const int top_wall, const int left_wall,
                     const int right_wall);

  void CreateHistogram();

  void UpdateHistogram();

 private:
};

}
