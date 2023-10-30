#include "praser.h"

int Praser_NSP::Praser_Json::Prase(const std::string& content)
{
    rapidjson::Document doc;
    doc.Parse(content.c_str());
    if (doc.HasParseError())
    {
        spdlog::error("Json Parse Error : ErrorCode is {}", std::to_string(doc.GetParseError()));
        return RARSE_ERROR;
    }
    m_root.CopyFrom(doc,doc.GetAllocator());
    return OK;
}


int Praser_NSP::Praser_Yaml::Prase(const std::string& content)
{
    m_root = YAML::Load(content);
    if(m_root.IsNull()) return RARSE_ERROR;
    return OK;
}

int Praser_NSP::Praser_Config::Prase(const std::string &content)
{
    std::stringstream iss(content);
    std::string line;
    while(std::getline(iss,line)){
        if(line[0] == '#') continue; //#为注释
        int indx = line.find('=');
        if(indx == std::string::npos || indx == 0 || indx == line.size()-1) return RARSE_ERROR;//没有等号或者没有key或value为错误
        m_root[line.substr(0,indx)] = line.substr(indx+1);
    }
    return OK;
}
