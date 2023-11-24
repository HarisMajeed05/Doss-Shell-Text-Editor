
#include"Folder.h"
#include<iostream>
#include <chrono>
#include <ctime>
using namespace std;
class file
{
public:
    std::string name;
    std::string data; // Assuming there's some data associated with the file
    chrono::system_clock::time_point creation_time;
    string type; //this is the type of my file like .txt 
    std::string owner;
    bool hidden;

public:
    file(std::string n = "NULL", std::string user = "")
        : name(n), owner(user), hidden(false)
    {
        size_t dotIndex = name.find_last_of('.');
        if (dotIndex != std::string::npos && dotIndex + 1 < name.length()) {
            type = name.substr(dotIndex + 1);
        }
        else {
            type = "Unknown"; // Default if no extension found
        }
        creation_time = chrono::system_clock::now();

    }
    void writeData(const std::string& newData)
    {
        // Overwrite the existing data with the new data
        data = newData;
    }
    bool searchInFile(const std::string& searchString) const {
        size_t found = data.find(searchString);
        return (found != std::string::npos);
    }
    void print()
    {
        std::cout << "File Name: " << name << std::endl;
        std::cout << "Owner: " << owner << std::endl;
        std::cout << "File Type: " << type << std::endl;
        std::cout << "Data: " <<data << std::endl;
        std::time_t creation_time_t = std::chrono::system_clock::to_time_t(creation_time);

        // Using ctime_s to convert time_t to string
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &creation_time_t);

        // Remove the newline character from the buffer
        size_t length = strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n')
        {
            buffer[length - 1] = '\0';
        }

        std::cout << "Creation Time: " << buffer << std::endl;

    }

};
