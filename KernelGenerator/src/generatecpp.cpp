#include "generatecpp.h"

GenerateCPP::GenerateCPP(std::string projectpath, std::string projectname/*, std::string configfile*/)
{
    this->projectname = projectname;
    this->projectpath = projectpath;
    // this->configfile = configfile;
}

int GenerateCPP::generateCPP()
{
    generateConfigdata();
    generateSHMHandler();
    generateLogger();
    generateMain();
    return 1;
}

int GenerateCPP::generateConfigdata()
{
    std::stringstream text;
    text << "#include \"configdata.h\"" <<std::endl <<
            "#include <string.h>" <<std::endl <<
            "" <<std::endl <<
            "ConfigData::ConfigData(string path)" <<std::endl <<
            "    :m_path(path)" <<std::endl <<
            "{" <<std::endl <<
            "    setConfigObject();" <<std::endl <<
            "}" <<std::endl <<
            "" <<std::endl <<
            "ConfigData::~ConfigData()" <<std::endl <<
            "{" <<std::endl
         <<std::endl <<
           "}" <<std::endl <<
           "" <<std::endl <<
           "void ConfigData::setConfigObject()" <<std::endl <<
           "{" <<std::endl <<
           "  ifstream datei(m_path);" <<std::endl <<
           "  while(datei.good())" <<std::endl <<
           "  {" <<std::endl <<
           "    string zeile;" <<std::endl <<
           "    getline(datei,zeile);" <<std::endl <<
           "    if(boost::starts_with(zeile,\"[Process]\"))" <<std::endl <<
           "    {" <<std::endl <<
           "      getline(datei,zeile);" <<std::endl <<
           "    }" <<std::endl <<
           "    else if(zeile == \"#\")" <<std::endl <<
           "    {" <<std::endl <<
           "      break;" <<std::endl <<
           "    }" <<std::endl <<
           "" <<std::endl <<
           "    size_t val = zeile.find(' ');" <<std::endl <<
           "    addItemToProcessMap(zeile.substr(0,val),zeile.substr(val,zeile.length()-1));" <<std::endl <<
           "  }" <<std::endl <<
           "}" <<std::endl <<
           "" <<std::endl <<
           "void ConfigData::addItemToProcessMap(string key, string value)" <<std::endl <<
           "{" <<std::endl <<
           "    m_ProcessMap[key] = value;" <<std::endl <<
           "}" <<std::endl <<
           "" <<std::endl <<
           "map<string,string> ConfigData::returnProcessMap()" <<std::endl <<
           "{" <<std::endl <<
           "    return m_ProcessMap;" <<std::endl <<
           "}" <<std::endl
        <<std::endl <<
          "string ConfigData::trim(string& str)" <<std::endl <<
          "{" <<std::endl <<
          "    size_t first = str.find_first_not_of(' ');" <<std::endl <<
          "    if (string::npos == first)" <<std::endl <<
          "    {" <<std::endl <<
          "        return str;" <<std::endl <<
          "    }" <<std::endl <<
          "    size_t last = str.find_last_not_of(' ');" <<std::endl <<
          "    return str.substr(first, (last - first + 1));" <<std::endl <<
          "}";

    std::ofstream out;

    std::string path = projectpath;
    path.append("/");
    path.append(projectname);
    path.append("/src/configdata.cpp");

    out.open(path);
    out << text.str();
    out.flush();
    out.close();
    return 1;
}

int GenerateCPP::generateLogger()
{
    std::stringstream text;
    text << "#include \"logger.h\"" <<std::endl <<
            "#include <boost/log/support/date_time.hpp>" <<std::endl <<
            "#include <boost/log/core.hpp>" <<std::endl <<
            "#include <boost/log/expressions.hpp>" <<std::endl <<
            "#include <boost/log/sinks/text_file_backend.hpp>" <<std::endl <<
            "#include <boost/log/utility/setup/file.hpp>" <<std::endl <<
            "#include <boost/log/utility/setup/common_attributes.hpp>" <<std::endl <<
            "#include <boost/log/sources/severity_logger.hpp>" <<std::endl <<
            "#include <boost/log/sources/record_ostream.hpp>" <<std::endl <<
            "#include <boost/filesystem.hpp>" <<std::endl <<
            "" <<std::endl <<
            "Logger::Logger()" <<std::endl <<
            "{" <<std::endl <<
            "" <<std::endl <<
            "}" <<std::endl <<
            "" <<std::endl <<
            "Logger* Logger::_instance = nullptr;" <<std::endl <<
            "Logger* Logger::Instance()" <<std::endl <<
            "{" <<std::endl <<
            "  if(_instance == nullptr){" <<std::endl <<
            "    _instance = new Logger();" <<std::endl <<
            "  }" <<std::endl <<
            "  return _instance;" <<std::endl <<
            "}" <<std::endl <<
            std::endl <<
            "void Logger::initLogger(unsigned int rotationSizeInMB, boost::log::trivial::severity_level severityLevel, std::string directory, std::string file)" <<std::endl <<
            "{" <<std::endl <<
            "  createOrReplaceDirectory(directory);" <<std::endl <<
            "" <<std::endl <<
            "  boost::log::add_file_log" <<std::endl <<
            "      (" <<std::endl <<
            "        boost::log::keywords::file_name = directory + file," <<std::endl <<
            "        boost::log::keywords::auto_flush = true," <<std::endl <<
            "        boost::log::keywords::rotation_size = rotationSizeInMB * 1024 * 1024," <<std::endl <<
            "        boost::log::keywords::target = directory," <<std::endl <<
            "        boost::log::keywords::format = (" <<std::endl <<
            "        boost::log::expressions::stream" <<std::endl <<
            "        << boost::log::expressions::attr< unsigned int >(\"LineID\")" <<std::endl <<
            "        << \" \"" <<std::endl <<
            "        << std::setw(10)" <<std::endl <<
            "        << boost::log::expressions::format_date_time<boost::posix_time::ptime>(\"TimeStamp\", \"%d-%m-%Y %H:%M:%S.%f\")" <<std::endl <<
            "        << std::setw(10)" <<std::endl <<
            "        << boost::log::trivial::severity" <<std::endl <<
            "        << std::setw(10)" <<std::endl <<
            "        << boost::log::expressions::smessage" <<std::endl <<
            "        )" <<std::endl <<
            "      );" <<std::endl <<
            "  boost::log::core::get()->set_filter(boost::log::trivial::severity >= severityLevel);" <<std::endl <<
            "  boost::log::add_common_attributes();" <<std::endl <<
            "}" <<std::endl <<
            "" <<std::endl <<
            "void Logger::logInfo(std::string message)" <<std::endl <<
            "{" <<std::endl <<
            "  BOOST_LOG_SEV(_log, boost::log::trivial::severity_level::info) << message;" <<std::endl <<
            "}" <<std::endl <<
            "" <<std::endl <<
            "void Logger::logDebug(std::string message)" <<std::endl <<
            "{" <<std::endl <<
            "  BOOST_LOG_SEV(_log, boost::log::trivial::severity_level::debug) << message;" <<std::endl <<
            "}" <<std::endl <<
            "" <<std::endl <<
            "void Logger::logWarn(std::string message)" <<std::endl <<
            "{" <<std::endl <<
            "  BOOST_LOG_SEV(_log, boost::log::trivial::severity_level::warning) << message;" <<std::endl <<
            "}" <<std::endl <<
            "" <<std::endl <<
            "void Logger::logError(std::string message)" <<std::endl <<
            "{" <<std::endl <<
            "  BOOST_LOG_SEV(_log, boost::log::trivial::severity_level::error) << message;" <<std::endl <<
            "}" <<std::endl <<
            "" <<std::endl <<
            "void Logger::logFatal(std::string message)" <<std::endl <<
            "{" <<std::endl <<
            "  BOOST_LOG_SEV(_log, boost::log::trivial::severity_level::fatal) << message;" <<std::endl <<
            "}" <<std::endl <<
            "" <<std::endl <<
            "void Logger::createOrReplaceDirectory(std::string directory)" <<std::endl <<
            "{" <<std::endl <<
            "  boost::filesystem::path dir(directory.c_str());" <<std::endl <<
            "  if(boost::filesystem::create_directory(dir))" <<std::endl <<
            "  {" <<std::endl <<
            "    std::cout << \"Directory created: \" << directory << std::endl;" <<std::endl <<
            "  }" <<std::endl <<
            "  else" <<std::endl <<
            "  {" <<std::endl <<
            "    std::cout << \"Using directory: \" << directory << std::endl;" <<std::endl <<
            "  }" <<std::endl <<
            "}";

    std::ofstream out;

    std::string path = projectpath;
    path.append("/");
    path.append(projectname);
    path.append("/src/logger.cpp");

    out.open(path);
    out << text.str();
    out.flush();
    out.close();
    return 1;
}

int GenerateCPP::generateSHMHandler()
{
    std::stringstream text;
    text << "#include \"simplesharedmemoryhandler.h\"" <<std::endl << std::endl <<
            "SimpleSharedMemoryHandler::SimpleSharedMemoryHandler(std::string sharedMemoryName, std::string segmentname, int size)" <<std::endl <<
            "{" <<std::endl <<
            "  boost::interprocess::shared_memory_object::remove(sharedMemoryName.c_str());" << std::endl <<
            "  mySharedMemory = new boost::interprocess::managed_shared_memory( " <<std::endl <<
            "  boost::interprocess::open_or_create, sharedMemoryName.c_str(), size);" <<std::endl <<
            "  if(mySharedMemory == NULL)" <<std::endl <<
            "  {" <<std::endl <<
            "      Logger *ugv_logger = Logger::Instance();" <<std::endl <<
            "      ugv_logger->logError(\"SharedMemory is NULL\");" <<std::endl <<
            "      return;"<<std::endl <<
            "  }" << std::endl <<
            "  this->sharedMemoryName = sharedMemoryName;" <<std::endl <<
            "  this->segmentname = segmentname;" <<std::endl <<
            "}" <<std::endl <<
            "SimpleSharedMemoryHandler::~SimpleSharedMemoryHandler()" <<std::endl <<
            "{" <<std::endl <<
            "    mySharedMemory->destroy<std::string>(segmentname.c_str());"<<std::endl <<
            "    boost::interprocess::shared_memory_object::remove(sharedMemoryName.c_str());"<<std::endl <<
            "}";

    std::ofstream out;
    std::string path = projectpath;
    path.append("/");
    path.append(projectname);
    path.append("/src/simplesharedmemoryhandler.cpp");

    out.open(path);
    out << text.str();
    out.flush();
    out.close();
    return 1;
}

int GenerateCPP::generateMain()
{
    std::stringstream text;
    text <<"#include <iostream>" << std::endl <<
           "#include <map>"<< std::endl <<
           "#include <configdata.h>"<< std::endl <<
           "#include <string>"<< std::endl <<
           "#include \"logger.h\""<< std::endl <<
           "#include <string.h>"<< std::endl <<
           "#include \"boost/program_options.hpp\""<< std::endl <<
           "#include \"simplesharedmemoryhandler.h\""<< std::endl <<
           "\n"<< std::endl <<
           "using namespace std;"<< std::endl <<
           "namespace po = boost::program_options;" <<std::endl<<
           "\n"<< std::endl <<
           "int main(int argc, const char *argv[])"<< std::endl <<
           "{"<< std::endl <<
           "    po::options_description desc{\"Options\"};"<<std::endl<<
           "    desc.add_options()"<<std::endl<<
           "        (\"help,h\", \"\")"<<std::endl<<
           "        (\"configfile,c\", po::value<std::string>()->default_value(\"./config.cfg\"), \"Configfile\");"<<std::endl<<
           "        po::variables_map vm;" <<std::endl<<
           "    po::store(po::parse_command_line(argc, argv, desc), vm);"<<std::endl<<
           "    po::notify(vm);"<<std::endl<<std::endl<<
           "    string path = vm[\"configfile\"].as<std::string>();"<< std::endl <<
           "    ConfigData cfg(path);"<< std::endl <<
           "    map<string,string> processMap = cfg.returnProcessMap();"<< std::endl <<
           "    string shmName = cfg.trim(processMap[\"SharedMemoryName\"]);"<< std::endl <<
           "    string shmSize = cfg.trim(processMap[\"SharedMemorySize\"]);"<< std::endl <<
           "    string shmSegment = cfg.trim(processMap[\"SharedMemorySegment\"]);" << std::endl <<
           "    string logfileName = cfg.trim(processMap[\"LogFileName\"]);"<< std::endl <<
           "    string logDirectory = cfg.trim(processMap[\"LogDirectoryPath\"]);"<< std::endl <<
           "\n"<< std::endl <<
           "    Logger *ugv_logger = Logger::Instance();"<< std::endl <<
                  "    ugv_logger->initLogger(3, boost::log::trivial::severity_level::info, logDirectory, logfileName);"<< std::endl <<
                  "\n"<< std::endl <<
                  "    ugv_logger->logDebug(\"debug\");"<< std::endl <<
                  "    ugv_logger->logFatal(\"fatal\");"<< std::endl <<
                  "    ugv_logger->logError(\"error\");"<< std::endl <<
                  "    ugv_logger->logInfo(\"info\");"<< std::endl <<
                  "    ugv_logger->logWarn(\"warning\");"<< std::endl <<
           "\n"<< std::endl <<
           "    SimpleSharedMemoryHandler ssmH(shmName, shmSegment ,stoi(shmSize));"<< std::endl <<
           "    return 0;"<< std::endl <<
           "}";

    std::ofstream out;
    std::string path = projectpath;
    path.append("/");
    path.append(projectname);
    path.append("/src/main.cpp");

    out.open(path);
    out << text.str();
    out.flush();
    out.close();
    return 1;
}
