#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>
#include "configer.h"
int main()
{
    auto console_sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
    console_sink->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
    auto logger = std::make_shared<spdlog::logger>("logger",console_sink);
    spdlog::set_default_logger(logger);
    Configer_NSP::Json_Configer json;
    int code = json.Load_Conf("../a.json");
    std::cout<<code<<std::endl;
    Configer_NSP::Json_Configer::Json_Praser_Ptr json_praser_ptr = json.Get_Praser();
    rapidjson::Value val,m;
    json_praser_ptr->Get_Value<rapidjson::Value>(json_praser_ptr->Get_Root(),"array",val);
    for(rapidjson::SizeType i = 0 ;i < val.Size() ; i++)
    {
        if(val[i].IsInt()){
            std::cout<<val[i].GetInt()<<std::endl;
        }else if(val[i].IsString())
        {
            std::cout<<val[i].GetString()<<std::endl;
        }
    }
    json_praser_ptr->Get_Value<rapidjson::Value>(json_praser_ptr->Get_Root(),"map",m);
    int dis;
    json_praser_ptr->Get_Value<int>(m,"sichuan",dis);
    std::cout<<"dis  :"<<dis<<std::endl;

    Configer_NSP::Yaml_Configer yaml;
    yaml.Load_Conf("../a.yaml");
    Configer_NSP::Yaml_Configer::Yaml_Praser_Ptr yaml_praser_ptr=yaml.Get_Praser();
    std::string ret;
    yaml_praser_ptr->Get_Value<std::string>(yaml_praser_ptr->Get_Root(),"name",ret);
    std::cout<<"yaml name :"<<ret<<std::endl;
    YAML::Node node;
    yaml_praser_ptr->Get_Value<YAML::Node>(yaml_praser_ptr->Get_Root(),"info",node);
    yaml_praser_ptr->Get_Value<std::string>(node,"address",ret);
    std::cout<<"yaml info address : "<<ret<<std::endl;
    YAML::Node fin;
    yaml_praser_ptr->Get_Value<YAML::Node>(node,"phone",fin);
    for(YAML::const_iterator it=fin.begin();it!=fin.end();it++)
    {
        std::cout<< (*it).as<std::string>()<<std::endl;
    }

    Configer_NSP::Config_Configer config;
    config.Load_Conf("../a.conf");
    Configer_NSP::Config_Configer::Config_Praser_Ptr config_praser_ptr = config.Get_Praser();
    std::string config_val;
    config_praser_ptr->Get_Value("name",config_val);
    std::cout<< config_val<<std::endl;
    config_praser_ptr->Get_Value("ip",config_val);
    std::cout<<config_val<<std::endl;
    return 0;
}