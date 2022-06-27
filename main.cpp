#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  vector<int> GetClimbs_(const vector<int>& heights) {
    vector<int> climbs;
    auto first = heights.begin();
    auto second = next(first);
    while (heights.end() != second) {
      climbs.push_back(*second++ - *first++);
    }

    return climbs;
  }

 public:
  int furthestBuilding(vector<int> &heights, int bricks, int ladders) {
    vector<int> climbs = GetClimbs_(heights);
    while (!climbs.empty()) {
      vector<int> ordered_climbs = climbs;
      sort(ordered_climbs.begin(), ordered_climbs.end());
      int b = bricks, l = ladders;
      for (int i = ordered_climbs.size() - 1; 0 <= i; --i) {
        if (0 < ordered_climbs[i]) {
          if (0 < l) { --l; }
          else if (ordered_climbs[i] <= b) { b -= ordered_climbs[i]; }
          else { break; }
        }
        ordered_climbs.pop_back();
      }
      if (ordered_climbs.empty()) { break; }
      climbs.pop_back();
    }

    return climbs.size();
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
