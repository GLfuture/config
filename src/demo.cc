#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>
#include "config.h"
int main()
{
    auto console_sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
    console_sink->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
    auto logger = std::make_shared<spdlog::logger>("logger",console_sink);
    spdlog::set_default_logger(logger);
    Config_NSP::Config_Json json;
    json.Load_Conf("../a.json");
    rapidjson::Value val,m;
    json.Get_Value<rapidjson::Value>(json.Get_Root_Value(),"array",val);
    for(rapidjson::SizeType i = 0 ;i < val.Size() ; i++)
    {
        if(val[i].IsInt()){
            std::cout<<val[i].GetInt()<<std::endl;
        }else if(val[i].IsString())
        {
            std::cout<<val[i].GetString()<<std::endl;
        }
    }
    json.Get_Value<rapidjson::Value>(json.Get_Root_Value(),"map",m);
    int dis;
    json.Get_Value<int>(m,"sichuan",dis);
    std::cout<<"dis  :"<<dis<<std::endl;

    Config_NSP::Config_Yaml yaml;
    yaml.Load_Conf("../a.yaml");
    std::string ret;
    yaml.Get_Value<std::string>(yaml.Get_Root_Value(),"name",ret);
    std::cout<<"yaml name :"<<ret<<std::endl;
    YAML::Node node;
    yaml.Get_Value<YAML::Node>(yaml.Get_Root_Value(),"info",node);
    yaml.Get_Value<std::string>(node,"address",ret);
    std::cout<<"yaml info address : "<<ret<<std::endl;
    YAML::Node fin;
    yaml.Get_Value<YAML::Node>(node,"phone",fin);
    for(YAML::const_iterator it=fin.begin();it!=fin.end();it++)
    {
        std::cout<< (*it).as<std::string>()<<std::endl;
    }


    return 0;
}