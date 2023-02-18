#include <iostream>
#include <fstream>
#include <string>

class TextEditor {
public:
    TextEditor() {
        filename_ = "";
        modified_ = false;
    }

    bool create_file(std::string filename) {
        if (filename_ != "") {
            std::cout << "Error: a file is already open." << std::endl;
            return false;
        }

        std::ofstream file(filename);

        if (!file.is_open()) {
            std::cout << "Error: could not create file." << std::endl;
            return false;
        }

        file.close();

        filename_ = filename;
        modified_ = true;

        std::cout << "Created file: " << filename_ << std::endl;

        return true;
    }

    bool open_file(std::string filename) {
        if (filename_ != "") {
            std::cout << "Error: a file is already open." << std::endl;
            return false;
        }

        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cout << "Error: could not open file." << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            content_ += line + "\n";
        }

        file.close();

        filename_ = filename;
        modified_ = false;

        std::cout << "Opened file: " << filename_ << std::endl;

        return true;
    }

    void edit_file() {
        if (filename_ == "") {
            std::cout << "Error: no file is open." << std::endl;
            return;
        }

        std::cout << "Enter text (type . on a new line to end):" << std::endl;

        std::string line;
        std::getline(std::cin, line);

        while (line != ".") {
            content_ += line + "\n";
            modified_ = true;
            std::getline(std::cin, line);
        }
    }

    bool save_file() {
        if (filename_ == "") {
            std::cout << "Error: no file is open." << std::endl;
            return false;
        }

        if (!modified_) {
            std::cout << "The file has not been modified." << std::endl;
            return true;
        }

        std::ofstream file(filename_);

        if (!file.is_open()) {
            std::cout << "Error: could not save file." << std::endl;
            return false;
        }

        file << content_;

        file.close();

        modified_ = false;

        std::cout << "File saved: " << filename_ << std::endl;

        return true;
    }

    bool close_file() {
        if (filename_ == "") {
            std::cout << "Error: no file is open." << std::endl;
            return false;
        }

        if (modified_) {
            std::cout << "The file has been modified. Do you want to save it? (y/n): ";
            std::string response;
            std::getline(std::cin, response);

            if (response == "y") {
                save_file();
            }
        }

        filename_ = "";
        content_ = "";
        modified_ = false;

        std::cout << "File closed." << std::endl;

        return true;
    }

private:
    std::string filename_;
    std::string content_;
    bool modified_;
};

int main() {}
   
