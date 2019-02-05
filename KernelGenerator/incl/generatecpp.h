#ifndef GENERATECPP_H
#define GENERATECPP_H
#include <fstream>
#include <string>
#include <sstream>

class GenerateCPP
{
public:
    GenerateCPP(std::string projectpath, std::string projectname);
    int generateCPP();
private:
    std::string projectpath, projectname/*, configfile*/;
    int generateConfigdata();
    int generateLogger();
    int generateSHMHandler();
    int generateMain();
};

#endif // GENERATECPP_H
