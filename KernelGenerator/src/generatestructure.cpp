#include "generatestructure.h"

GenerateStructure::GenerateStructure(std::string projectpath, std::string projectname)
{
    this->projectname = projectname;
    this->projectpath = projectpath;
}

int GenerateStructure::generateStructure()
{
    std::string completePath = projectpath + "/" + projectname;
    std::string srcPathDir = completePath + "/src";
    std::string inclPathDir = completePath + "/incl";

    char pPath[completePath.size() + 1];
    char srcpath[srcPathDir.size() + 1];
    char inclpath[inclPathDir.size() + 1];
    std::string cmakepath = completePath + "/CMakeLists.txt";

    strcpy(pPath, completePath.c_str());
    strcpy(srcpath, srcPathDir.c_str());
    strcpy(inclpath,inclPathDir.c_str());

    fs::path p(pPath);
    fs::path src(srcpath);
    fs::path incl(inclpath);

    if(fs::create_directories(p)){
        std::cout << "Directory erstellt" << std::endl;
    }
    if(fs::create_directories(src)){
        std::cout << "src erstellt" << std::endl;
    }
    if(fs::create_directories(incl)){
        std::cout << "incl erstellt" << std::endl;
    }

    return setupCMake(cmakepath);
}

int GenerateStructure::setupCMake(std::string cmakepath){
    std::ofstream cmakefile(cmakepath);
    std::transform(projectname.begin(), projectname.end(), projectname.begin(), ::tolower);
    cmakefile <<"project("<< projectname <<")" << std::endl << std::endl <<
                "cmake_minimum_required(VERSION 3.5)"<< std::endl<<
                "find_package(Boost 1.58.0)"<<std::endl<<

                "set(CMAKE_C_COMPILER gcc)"<<std::endl<<
                "set(CMAKE_CXX_COMPILER /usr/bin/g++)"<<std::endl<<
                "set(CMAKE_CXX_STANDARD 14)"<<std::endl<<
                "set(CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS} -Wall -pedantic\")"<<std::endl<<
                "set(CMAKE_CXX_FLAGS_DEBUG \"${CMAKE_CXX_FLAGS_DEBUG} -Wall\")"<<std::endl<<
                std::endl<<
                "# Find source files"<<std::endl<<
                "FILE(GLOB SOURCES src/*.cpp)"<<std::endl<<
                "FILE(GLOB_RECURSE INC_ALL \"incl/*.h\")"<<std::endl<<

                "# Include header files"<<std::endl<<
                "include_directories(incl)"<<std::endl<<
                "ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)"<< std::endl << std::endl <<
                "# Create an executable"<<std::endl<<
                "add_executable (${PROJECT_NAME} ${SOURCES} ${INC_ALL})"<<std::endl<<

                "target_link_libraries(${PROJECT_NAME}"<<std::endl<<
                "    ${Boost_LIBRARIES}"<<std::endl<<
                "    boost_system"<<std::endl<<
                "    boost_log" <<std::endl <<
                "    boost_log_setup" <<std::endl <<
                "    boost_thread"<<std::endl <<
                "    boost_filesystem"<<std::endl<<
                "    boost_program_options"<<std::endl<<
                "    rt"<<std::endl<<
                "    pthread"<<std::endl<<
                ")";
    std::cout<<"CMakeFile erstellt"<<std::endl;
    cmakefile.close();
    return 1;
}
