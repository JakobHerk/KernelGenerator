#ifndef GENERATESTRUCTURE_H
#define GENERATESTRUCTURE_H
#include <string>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

class GenerateStructure
{
public:
    GenerateStructure(std::string projectpath, std::string projectname);
    int generateStructure();
private:
    std::string projectpath, projectname;
private:
    int setupCMake(std::string cmakepath);
};

#endif // GENERATESTRUCTURE_H
