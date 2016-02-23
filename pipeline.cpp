#include "pipeline.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>

Pipeline::Pipeline(bool out) : path("")
{
    setMode(out);
}

Pipeline::Pipeline(const char *path, bool out) : path(path)
{
    setMode(out);

    if (!exist())
        make();
}

Pipeline::~Pipeline()
{
    close();
}

void Pipeline::setMode(bool out)
{
    mode = out ? (std::ios_base::out|std::ios_base::trunc) : (std::ios_base::in);
}

bool Pipeline::make(std::string path)
{
    if (opened())
        close();

    this->path = path;

    return make();
}

bool Pipeline::make()
{
    if (mkfifo(path.c_str(), S_IRWXU|S_IRWXG|S_IRWXO) == 0)
        return true;
    else
        return false;
}

bool Pipeline::exist()
{
    struct stat fstat;

    if ((stat(path.c_str(), &fstat) == 0) && S_ISFIFO(fstat.st_mode))
        return true;
    else
        return false;
}

bool Pipeline::open()
{
    if (!exist())
        return false;

    stream.open(path.c_str(), mode);
    if (stream.is_open())
        return true;
    else
        return false;
}

bool Pipeline::opened()
{
    return (stream.is_open());
}

std::string Pipeline::readLine()
{
    std::string tmp;
    std::getline(stream, tmp);
    return tmp;
}

void Pipeline::write(std::string buf)
{
    stream.write(buf.c_str(), buf.size());
}

void Pipeline::writeLine(std::string buf)
{
    stream.write(buf.c_str(), buf.size()) << std::endl;
}

void Pipeline::close()
{
    if (stream.is_open())
        stream.close();
}

void Pipeline::remove()
{
    if (stream.is_open())
        stream.close();
    ::remove(path.c_str());
}
