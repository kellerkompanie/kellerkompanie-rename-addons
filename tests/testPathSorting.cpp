#include <gtest/gtest.h>

#include <string>
#include <algorithm>
#include <vector>

using namespace std;

bool sort_by_path(const tuple<string, string> &a,
                  const tuple<string, string> &b) {
    if (get<0>(a).size() == get<0>(b).size()) {
        // if paths are equally long, sort lexicographically
        return get<0>(a) < get<0>(b);
    }
    // if paths are of different length, sort descending by length
    return get<0>(a).size() > get<0>(b).size();
}

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    vector<pair<string, string>> paths = {
            {"/mods/@b/Addons",       "/mods/@b/addons"},
            {"/mods/@b/Addons/B.pbo", "/mods/@b/addons/b.pbo"},
            {"/mods/@b/Addons/A.pbo", "/mods/@b/addons/a.pbo"},
            {"/mods/@a/Addons",       "/mods/@a/addons"},
            {"/mods/@a/Addons/B.pbo", "/mods/@a/addons/b.pbo"},
            {"/mods/@a/Addons/A.pbo", "/mods/@a/addons/a.pbo"},
    };

    sort(paths.begin(), paths.end(), sort_by_path);

    vector<pair<string, string>> expectedPaths = {
            {"/mods/@a/Addons/A.pbo", "/mods/@a/addons/a.pbo"},
            {"/mods/@a/Addons/B.pbo", "/mods/@a/addons/b.pbo"},
            {"/mods/@b/Addons/A.pbo", "/mods/@b/addons/a.pbo"},
            {"/mods/@b/Addons/B.pbo", "/mods/@b/addons/b.pbo"},
            {"/mods/@a/Addons",       "/mods/@a/addons"},
            {"/mods/@b/Addons",       "/mods/@b/addons"},
    };

    EXPECT_EQ(paths, expectedPaths);
}
