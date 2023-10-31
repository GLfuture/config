#include "configer.h"

int Configer_NSP::Configer_Base::Read_Conf(const std::string &filepath, std::string &result)
{
    if (!std::filesystem::exists(filepath))
    {
        return errno;
    }
    std::ifstream fin;
    fin.open(filepath);
    if (fin.fail())
    {
        return errno;
    }
    fin.seekg(0, std::ios_base::end);
    std::streampos len = fin.tellg();
    fin.seekg(0, std::ios_base::beg);
    char *buffer = new char[len];
    memset(buffer, 0, len);
    fin.read(buffer, len);
    result.assign(buffer,len);
    return 0;
}

int Configer_NSP::Json_Configer::Load_Conf(const std::string &filepath)
{
    std::string content;
    int ret = Read_Conf(filepath, content);
    if (!!ret)
    {
        spdlog::error("Read Json Config Error : {}", std::string(strerror(ret)));
        return -1;
    }
    praser->Prase(content);
    return 0;
}

int Configer_NSP::Yaml_Configer::Load_Conf(const std::string &filepath)
{
    praser->Get_Root() = YAML::LoadFile(filepath);
    return 0;
}

int Configer_NSP::Config_Configer::Load_Conf(const std::string &filepath)
{
    std::string content;
    int ret = Read_Conf(filepath,content);
    if (!!ret)
    {
        spdlog::error("Read Config file Error : {}", std::string(strerror(ret)));
        return -1;
    }
    praser->Prase(content);
    return 0;
}
