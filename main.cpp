#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  int furthest(const vector<int> &heights, int from, int bricks, int ladders) {
    int to = from + 1;
    while (to < heights.size()) {
      int h = heights[to] - heights[from];
      if (0 < h) { break; }
      ++to, ++from;
    }
    if (to < heights.size()) {
      int h = heights[to] - heights[from];
      int pos_ladder = (0 < ladders) ? furthest(heights, to, bricks, ladders - 1) : from;
      int pos_bricks = (h <= bricks) ? furthest(heights, to, bricks - h, ladders) : from;
      return max(pos_ladder, pos_bricks);
    }

    return from;
  }

 public:
  int furthestBuilding(vector<int> &heights, int bricks, int ladders) {
    return furthest(heights, 0, bricks, ladders);
  }
};

void TestFurthestBuilding() {
  Solution s;
  {
    vector<int> heights{4, 2, 7, 6, 9, 14, 12};
    assert(4 == s.furthestBuilding(heights, 5, 1));
  }
  {
    vector<int> heights{4, 12, 2, 7, 3, 18, 20, 3, 19};
    assert(7 == s.furthestBuilding(heights, 10, 2));
  }
  {
    vector<int> heights{14, 3, 19, 3};
    assert(3 == s.furthestBuilding(heights, 17, 0));
  }
  {
    vector<int> heights{1, 5, 1, 2, 3, 4, 10000};
    assert(5 == s.furthestBuilding(heights, 4, 1));
  }

}

int main() {
  TestFurthestBuilding();
  cout << "Ok!" << endl;
  return 0;
}
