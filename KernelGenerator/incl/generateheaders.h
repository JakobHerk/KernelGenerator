#ifndef GENERATEHEADERS_H
#define GENERATEHEADERS_H
#include <string>
#include <fstream>
#include <sstream>

class GenerateHeaders
{
public:
    GenerateHeaders(std::string projectpath, std::string projectname);
    int generateHeaders();
private:
    std::string projectpath, projectname;
    int generateLogger();
    int generateConfigdata();
    int generateSHMHandler();
};

#endif // GENERATEHEADERS_H
