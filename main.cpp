#include "system.h"
#include "mainwindow.h"

#include <deque>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <sstream>

#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <QString>
#include <QDebug>

bool fileExists(const std::string &path)
{
    return std::filesystem::exists(path);
}

std::vector<uint8_t> getFileContents(const std::string &path)
{
    std::vector<uint8_t> contents;

    FILE *f = fopen(path.c_str(), "rb");
    if (!f)
        return contents;

    fseek(f, 0, SEEK_END);
    int filesize = ftell(f);
    fseek(f, 0, SEEK_SET);

    contents.resize(filesize);
    fread(&contents[0], 1, filesize, f);

    fclose(f);
    return contents;
}

bool putFileContents(const std::string &name, const std::vector<unsigned char> &contents)
{
    FILE *f = fopen(name.c_str(), "wb");
    if (!f)
        return false;

    fwrite(&contents[0], 1, contents.size(), f);

    fclose(f);

    return true;
}
bool writeToDisc(const std::string &name, const std::vector<uint8_t> &contents) { return putFileContents(name, contents); };

bool putFileContents(const std::string &path, const std::string contents)
{
    FILE *f = fopen(path.c_str(), "wb");
    if (!f)
        return false;

    fwrite(&contents[0], 1, contents.size(), f);

    fclose(f);

    return true;
}

std::string getFileContentsAsString(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Could not open file");

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

size_t getFileSize(const std::string &path)
{
    return std::filesystem::file_size(path);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
        
    MainWindow window;
    window.show();

    return a.exec();
}