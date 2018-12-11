#include <iostream>
#include <boost/program_options.hpp>
#include <string>
#include <boost/interprocess/managed_shared_memory.hpp>

namespace po = boost::program_options;

int setupProjectEnvironment(std::string projectname);

int main(int argc, const char *argv[])
{
    try
    {
        po::options_description desc{"Options"};
        desc.add_options()
                //TODO add list of all available options
                ("help,h", "")
                ("projectname,p", po::value<std::string>()->default_value("Kernel"), "Projectname")
                ("shmname,n", po::value<std::string>()->default_value("theSHM"), "Shmname")
                ("shmsize,z", po::value<int>()->default_value(65536), "Shmsize")
                ("segmentname,s", po::value<std::string>()->default_value("theSegment"), "Segmentname")
                ("configfile,c", po::value<std::string>(), "Configfile")
                ("loglevel,l", po::value<int>()->default_value(1), "Loglevel")
                ("projectpath,d", po::value<std::string>()->default_value(""), "Projectpath");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")){
            std::cout << desc << '\n';
            return 1;
        }

        std::string projectname = vm["projectname"].as<std::string>();
        setupProjectEnvironment(projectname);
        std::string shmname = vm["shmname"].as<std::string>();
        std::string segmentname = vm["segmentname"].as<std::string>();
        int shmsize = vm["shmsize"].as<int>();

    }
    catch (const po::error &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 1;
}

//Garnele
int setupProjectEnvironment(std::string projectname){
    /*
     * 0) lösche falls existiert
     * 1) erstelle Ordner
     * 2) erstelle CMakeFile
     * 3) erstelle Unterordner src&incl
     */
}

//Sebastian Pack
int setupHeaderfiles(){

}

//Jakob Herk
int setupCppFiles(){

}
