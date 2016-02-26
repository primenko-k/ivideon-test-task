#ifndef PIPELINE_H
#define PIPELINE_H

#include <fstream>

class Pipeline
{
public:
    Pipeline(bool out = false);
    Pipeline(const char *path, bool out = false);

    ~Pipeline();

    bool make(std::string path);
    bool make();
    bool exist();
    bool open();
    bool opened();
    std::string &readLineTo(std::string &buf);
    void write(const std::string &buf);
    void writeLine(const std::string &buf);
    void close();
    void remove();

private:
    void setMode(bool out);

private:
    std::fstream stream;
    std::string path;
    std::ios_base::openmode mode;
};

#endif // PIPELINE_H
