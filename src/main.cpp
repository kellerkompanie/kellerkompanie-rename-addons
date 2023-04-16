#include <iostream>
#include <vector>
#include <filesystem>
#include <string>

using namespace std;

string to_lower(string str) {
    std::transform(str.begin(), str.end(), str.begin(), [](char c) {
        return std::tolower(c);
    });
    return str;
}

bool sort_by_path(const tuple<string, string> &a,
                  const tuple<string, string> &b) {
    if (get<0>(a).size() == get<0>(b).size()) {
        // if paths are equally long, sort lexicographically
        return get<0>(a) < get<0>(b);
    }
    // if paths are of different length, sort descending by length
    return get<0>(a).size() > get<0>(b).size();
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        cerr << "No directory provided, please provide at least one directory as argument" << endl;
        return EXIT_FAILURE;
    }

    vector<string> directories;
    directories.assign(argv + 1, argv + argc);

    for (const auto &directory: directories) {
        if (!filesystem::is_directory(directory)) {
            cerr << "Error: '" << directory << "' is not a valid directory, skipping" << endl;
            continue;
        }

        // list of files to rename (old name, new name), list needs to be sorted, leaves have to be renamed first
        vector<pair<string, string>> filesToRename;

        for (const auto &dir_entry: filesystem::recursive_directory_iterator(directory,
                                                                             filesystem::directory_options::follow_directory_symlink)) {
            string filename = dir_entry.path().filename().string();
            string lowerFilename = to_lower(filename);
            if (dir_entry.is_directory() && to_lower(filename) == "addons" && filename != lowerFilename) {
                // check addons
                string absolutePath = filesystem::absolute(dir_entry.path()).string();
                string lowerAbsPath = absolutePath.substr(0, absolutePath.length() - 6) + "addons";
                filesToRename.emplace_back(absolutePath, lowerAbsPath);
            } else if (dir_entry.is_regular_file() && dir_entry.path().extension().string() == ".pbo" &&
                       filename != lowerFilename) {
                // check lowercase pbo
                string absolutePath = filesystem::absolute(dir_entry.path()).string();
                string lowerAbsPath = absolutePath.substr(0, absolutePath.length() - filename.length()) + lowerFilename;
                filesToRename.emplace_back(absolutePath, lowerAbsPath);
            }
        }

        // sort longest paths first
        sort(filesToRename.begin(), filesToRename.end(), sort_by_path);

        for (const auto &[absolutePath, lowerAbsPath]: filesToRename) {
            cout << "renaming:" << endl;
            cout << "\t" << absolutePath << endl;
            cout << "\t" << lowerAbsPath << endl;
            cout << endl;
            filesystem::rename(absolutePath, lowerAbsPath);
        }
    }
}