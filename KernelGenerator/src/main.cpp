#include <iostream>
#include <boost/program_options.hpp>
#include <string>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <sstream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <boost/filesystem.hpp>
#include <fstream>
#include "generatestructure.h"
#include "generateheaders.h"
#include "generatecpp.h"

namespace fs = boost::filesystem;
namespace po = boost::program_options;

int main(int argc, const char *argv[])
{
    try
    {
        po::options_description desc{"Options"};
        /*desc.add_options()
                ("projectname,p", po::value<std::string>()->default_value("Kernel"), "Projectname")
                ("shmname,n", po::value<std::string>()->default_value("theSHM"), "Shmname")
                ("shmsize,z", po::value<std::string>()->default_value("65536"), "Shmsize")
                ("segmentname,s", po::value<std::string>()->default_value("theSegment"), "Segmentname")
                ("configfile,c", po::value<std::string>()->default_value("./config.cfg"), "Configfile")
                ("loglevel,l", po::value<int>()->default_value(1), "Loglevel")
                ("logpath,f", po::value<std::string>()->default_value("/tmp"), "Logpath")
                ("projectpath,d", po::value<std::string>()->default_value("/tmp"), "Projectpath");*/
        desc.add_options()
                ("help,h", "")
                ("configfile,c", po::value<std::string>()->default_value("./config.cfg"), "Configfile")
                ("projectpath,d", po::value<std::string>()->default_value("/tmp"), "Projectpath")
                ("projectname,p", po::value<std::string>()->default_value("Kernel"), "Projectname");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")){
            std::cout << desc << '\n';
            return 1;
        }

        std::string projectname = vm["projectname"].as<std::string>();
        std::string projectpath = vm["projectpath"].as<std::string>();
        std::string configfile = vm["configfile"].as<std::string>();
        GenerateStructure gs(projectpath, projectname);
        gs.generateStructure();

        GenerateCPP gCpp(projectpath, projectname, configfile);
        gCpp.generateCPP();
        std::cout<<"C++ Files erstellt"<<std::endl;

        GenerateHeaders gh(projectpath, projectname);
        gh.generateHeaders();
        std::cout<<"Header Files erstellt"<<std::endl;
    }
    catch (const po::error &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 1;
}
