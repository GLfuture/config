#ifndef CONFIG_H
#define CONFIG_H
#include "praser.h"

namespace Configer_NSP
{
    class Configer_Base
    {
    public:
        virtual int Load_Conf(const std::string &filepath) = 0;

    protected:
        int Read_Conf(const std::string &filepath, std::string &result);
    };

    class Json_Configer:public Configer_Base
    {
    public:
        using Ptr = std::shared_ptr<Json_Configer>;
        using Json_Praser_Ptr = Praser_NSP::Praser_Json::Ptr;
        Json_Configer()
        {
            praser= std::make_shared<Praser_NSP::Praser_Json>();
        }
        
        Json_Praser_Ptr Get_Praser()
        {
            return praser;
        }

        int Load_Conf(const std::string& filepath) override;
    private:
        Json_Praser_Ptr praser;
    };

    class Yaml_Configer:public Configer_Base
    {
    public:
        using Ptr = std::shared_ptr<Yaml_Configer>;
        using Yaml_Praser_Ptr = Praser_NSP::Praser_Yaml::Ptr;
        Yaml_Configer(){
            praser = std::make_shared<Praser_NSP::Praser_Yaml>();
        }

        Yaml_Praser_Ptr Get_Praser()
        {
            return praser;
        }
        

        int Load_Conf(const std::string& filepath) override;
    private:
        Yaml_Praser_Ptr praser;
    };

    class Config_Configer:public Configer_Base
    {
    public:
        Config_Configer()
        {
            praser = std::make_shared<Praser_NSP::Praser_Config>();
        }
        using Ptr = std::shared_ptr<Config_Configer>;
        using Config_Praser_Ptr = Praser_NSP::Praser_Config::Ptr;

        int Load_Conf(const std::string& filepath) override;

        Config_Praser_Ptr Get_Praser()
        {
            return praser;
        }

    private:
        Config_Praser_Ptr praser;
    };
}


#endif