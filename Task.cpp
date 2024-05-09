#include "Task.h"
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>
// including string and vector isn't required because header already does it

void saveTasksToFile(const std::vector<Task>& tasks, const std::string& fileName)
{
    std::ofstream ostream(fileName);
    ostream << tasks.size();  // write the size to the file

    for (const Task& task : tasks) {
        std::string description = task.description;
        // replacing empty strings with _ makes loading faster because it views it as one giant string
        std::replace(description.begin(), description.end(), ' ', '_'); 
        ostream << '\n' << description << ' ' << task.done;  // writting to the file
    }
}

std::vector<Task> loadTasksFromFile(const std::string& fileName)
{
    if (!std::filesystem::exists(fileName)) {
        return std::vector<Task>();
    }
    std::vector<Task> tasks;
    std::ifstream istream(fileName);

    int n;
    istream >> n;  // the first line always has the amount of vectors

    for (int i = 0; i < n; i++) {
        std::string description;
        bool done;

        istream >> description >> done;
        std::replace(description.begin(), description.end(), '_', ' ');
        tasks.push_back(Task{ description, done });
    }
    return tasks;
}
