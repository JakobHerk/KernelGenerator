#include "generateheaders.h"

GenerateHeaders::GenerateHeaders(std::string projectpath, std::string projectname)
{
    this->projectname = projectname;
    this->projectpath = projectpath;
}

int GenerateHeaders::generateHeaders(){
    generateConfigdata();
    generateLogger();
    generateSHMHandler();
}

int GenerateHeaders::generateLogger(){

    std::stringstream text;
    text << "#pragma once"<< std::endl << std::endl <<
            "#include <boost/thread/mutex.hpp>" << std::endl <<
            "#include <boost/log/trivial.hpp>"<< std::endl <<
            "#include <iomanip>"<< std::endl <<
            "#include <string>"<< std::endl << std::endl <<
            "class Logger"<< std::endl <<
            "{"<< std::endl <<
            "public:"<< std::endl <<
            "  static Logger* Instance();"<< std::endl <<
            "  void initLogger(unsigned int rotationSizeInMB, boost::log::trivial::severity_level severityLevel, std::string directory, std::string file);"<< std::endl <<
            "  void logInfo(std::string message);"<< std::endl <<
            "  void logDebug(std::string message);"<< std::endl <<
            "  void logWarn(std::string message);"<< std::endl <<
            "  void logError(std::string message);"<< std::endl <<
            "  void logFatal(std::string message);"<< std::endl <<
            "private:"<< std::endl <<
            "  void createOrReplaceDirectory(std::string directory);"<< std::endl <<
            "  static Logger* _instance;"<< std::endl <<
            "  boost::mutex _mutex;"<< std::endl <<
            "  boost::log::sources::severity_logger<boost::log::trivial::severity_level> _log;"<< std::endl <<
            "protected:"<< std::endl <<
            "  Logger();"<< std::endl <<
            "};";

    std::ofstream out;
    std::string path = projectpath;
    path.append("/");
    path.append(projectname);
    path.append("/incl/logger.h");

    out.open(path);
    out << text.str();
    out.flush();
    out.close();
    return 1;
}

int GenerateHeaders::generateConfigdata()
{
    std::stringstream text;
    text << "#ifndef CONFIGDATA_H" << std::endl <<
            "#define CONFIGDATA_H" << std::endl <<
            "#include <string.h>" << std::endl <<
            "#include <iostream>" << std::endl <<
            "#include <fstream>" << std::endl <<
            "#include <map>" << std::endl <<
            "#include <boost/algorithm/string/predicate.hpp>" << std::endl <<
            "#include <boost/lexical_cast.hpp>" << std::endl <<
            "using namespace std;" << std::endl <<
            "class ConfigData" << std::endl <<
            "{" << std::endl <<
            "public:" << std::endl <<
            "    ConfigData(string path);" << std::endl <<
            "    ~ConfigData();" << std::endl <<
            "    void setConfigObject();" << std::endl <<
            "    map<string,string> returnProcessMap();" << std::endl <<
            "    void addItemToProcessMap(string key,string value);" << std::endl <<
            "    string trim(string& str);" << std::endl <<
            "private:" << std::endl <<
            "    string m_path;" << std::endl <<
            "    map<string,string> m_ProcessMap;" << std::endl <<
            "};" << std::endl <<
            "#endif // CONFIGDATA_H";

    std::ofstream out;
    std::string path = projectpath;
    path.append("/");
    path.append(projectname);
    path.append("/incl/configdata.h");

    out.open(path);
    out << text.str();
    out.flush();
    out.close();
    return 1;
}

int GenerateHeaders::generateSHMHandler()
{
    std::stringstream text;
    text <<"#ifndef SIMPLESHAREDMEMORYHANDLER_H" <<std::endl <<
           "#define SIMPLESHAREDMEMORYHANDLER_H" << std::endl <<
           "#include <boost/interprocess/managed_shared_memory.hpp>" << std::endl <<
           "#include <string>" << std::endl <<
           "#include \"logger.h\""<<std::endl<<
           "#include <iostream>" << std::endl <<
           "class SimpleSharedMemoryHandler" << std::endl <<
           "{" << std::endl <<
           "public:" << std::endl <<
           "    SimpleSharedMemoryHandler(std::string sharedMemoryName, std::string segmentname, int size);" << std::endl <<
           "    ~SimpleSharedMemoryHandler();" << std::endl <<
           "private:" << std::endl <<
           "    boost::interprocess::managed_shared_memory* mySharedMemory;" << std::endl <<
           "    std::string sharedMemoryName, segmentname;" << std::endl <<
           "};" << std::endl <<
           "#endif // SIMPLESHAREDMEMORYHANDLER_H";


    std::ofstream out;
    std::string path = projectpath;
    path.append("/");
    path.append(projectname);
    path.append("/incl/simplesharedmemoryhandler.h");

    out.open(path);
    out << text.str();
    out.flush();
    out.close();
    return 1;
}
