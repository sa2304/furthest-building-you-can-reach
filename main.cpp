#include <algorithm>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>

#include <boost/timer/timer.hpp>

using namespace std;
using namespace std::filesystem;

class Solution {
  vector<int> GetClimbs_(const vector<int> &heights) {
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
    set<int> jumps;
    int bricks_required = 0;
    int i = 0;
    for (; i < climbs.size(); ++i) {
      if (climbs[i] <= 0) { continue; }

      const int c = climbs[i];
      if (0 < ladders) {
        jumps.insert(c);
        --ladders;
      } else if (!jumps.empty() && *jumps.begin() < c) {
        bricks_required += *jumps.begin();
        jumps.erase(jumps.begin());
        jumps.insert(c);
      } else {
        bricks_required += c;
      }
      if (bricks < bricks_required) { break; }
    }

    return i;
  }
};

void ParseVector(const string &s, vector<int> &out) {
  size_t pos = s.find_first_of("1234567890"s);
  while (pos < s.length()) {
    size_t shift;
    int value = stoi(s.substr(pos), &shift);
    out.push_back(value);
    pos += shift;
    pos = s.find_first_of("1234567890"s, pos);
  }
}

void ParseTestFile(path filename, vector<int> &heights, int &bricks, int &ladders) {
  ifstream in{filename};
  if (in.is_open()) {
    string line;
    getline(in, line);
    ParseVector(line, heights);

    getline(in, line);
    bricks = stoi(line);

    getline(in, line);
    ladders = stoi(line);
  } else {
    stringstream sout;
    sout << "Cannot open "s << filename.generic_string();
    throw runtime_error{sout.str()};
  }
}

void TestFurthestBuilding() {
  Solution s;
  {
    boost::timer::auto_cpu_timer t;
    vector<int> heights{4, 2, 7, 6, 9, 14, 12};
    assert(4 == s.furthestBuilding(heights, 5, 1));
  }
  {
    boost::timer::auto_cpu_timer t;
    vector<int> heights{4, 12, 2, 7, 3, 18, 20, 3, 19};
    assert(7 == s.furthestBuilding(heights, 10, 2));
  }
  {
    boost::timer::auto_cpu_timer t;
    vector<int> heights{14, 3, 19, 3};
    assert(3 == s.furthestBuilding(heights, 17, 0));
  }
  {
    boost::timer::auto_cpu_timer t;
    vector<int> heights{1, 5, 1, 2, 3, 4, 10000};
    assert(5 == s.furthestBuilding(heights, 4, 1));
  }
  {
    boost::timer::auto_cpu_timer t;
    vector<int> heights;
    int bricks, ladders;
    ParseTestFile(current_path() / "test-data/100.txt", heights, bricks, ladders);
    assert(10 == s.furthestBuilding(heights, bricks, ladders));
  }
  {
    boost::timer::auto_cpu_timer t;
    vector<int> heights;
    int bricks, ladders;
    ParseTestFile(current_path() / "test-data/13.txt", heights, bricks, ladders);
    assert(72329 == s.furthestBuilding(heights, bricks, ladders));
  }
}

int main() {
  TestFurthestBuilding();
  cout << "Ok!" << endl;
  return 0;
}
