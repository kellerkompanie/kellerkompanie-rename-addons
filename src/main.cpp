#include <iostream>
#include <vector>
#include <filesystem>
#include <string>

using namespace std;

string to_lower(string str) {
    std::transform(str.begin(), str.end(), str.begin(), [](char c){
        return std::tolower(c);
    });
    return str;
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

        for (const auto &dir_entry: filesystem::recursive_directory_iterator(directory, filesystem::directory_options::follow_directory_symlink)) {
            string filename = dir_entry.path().filename().string();
            string lowerFilename = to_lower(filename);
            if (dir_entry.is_directory() && to_lower(filename) == "addons" && filename != lowerFilename) {
                // check addons
                string absolutePath = filesystem::absolute(dir_entry.path()).string();
                string lowerAbsPath = absolutePath.substr(0, absolutePath.length() - 6) + "addons";
                cout << "renaming:" << endl;
                cout << "\t" << absolutePath << endl;
                cout << "\t" << lowerAbsPath << endl;
                cout << endl;
                filesystem::rename(absolutePath, lowerAbsPath);
            } else if (dir_entry.is_regular_file() && dir_entry.path().extension().string() == ".pbo" && filename != lowerFilename) {
                // check lowercase pbo
                string absolutePath = filesystem::absolute(dir_entry.path()).string();
                string lowerAbsPath = absolutePath.substr(0, absolutePath.length() - filename.length()) + lowerFilename;
                cout << "renaming:" << endl;
                cout << "\t" << absolutePath << endl;
                cout << "\t" << lowerAbsPath << endl;
                cout << endl;
                filesystem::rename(absolutePath, lowerAbsPath);
            }
        }
    }
}