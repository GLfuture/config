#pragma once
#ifndef PRASER_H
#define PRASER_H
#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string.h>
#include <yaml-cpp/yaml.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <type_traits>
#include <vector>
#include <spdlog/spdlog.h>
#include <memory>
namespace Praser_NSP {
    class Praser_Base
    {
    public:
      enum PARSER_RET_CODE{
        OK = 0,
        NO_MEMBER,
        RARSE_ERROR,
        VALUE_TYPE_ERROR,

      };
      using Ptr = std::shared_ptr<Praser_Base>;

      virtual int Prase(const std::string& content) = 0;

      virtual ~Praser_Base(){}
    };

    //解析json配置文件
    class Praser_Json : public Praser_Base
    {
    public:
      using Ptr = std::shared_ptr<Praser_Json>;
      using Value = rapidjson::Value;

      int Prase(const std::string& content) override; 

      template<class T>
      inline int Get_Value(const rapidjson::Value& root,const std::string& key,T& value)
      {
        spdlog::error("Get_Value function : argument value type error");
        return VALUE_TYPE_ERROR;
      }

      Value& Get_Root()
      {
        return m_root;
      }
    private:
      Value m_root;
    };

    class Praser_Yaml : public Praser_Base
    {
    public:
      using Ptr = std::shared_ptr<Praser_Yaml>;
      using Value = YAML::Node;
      int Prase(const std::string& content) override; 

      template <class T>
      inline int Get_Value(const YAML::Node &root,const std::string& key ,T& value)
      {
        if(root[key.c_str()].IsNull()){
          spdlog::info("Get_Value funcion : yaml has no member");
          return NO_MEMBER;
        }
        try
        {
          value = root[key.c_str()].as<T>();
        }
        catch(const std::exception& e)
        {
          std::cerr << e.what() << std::endl;
          return VALUE_TYPE_ERROR;
        }
        
        return OK;
      }

      Value &Get_Root(){
        return m_root;
      }
    private:
      Value m_root;
    };

    class Praser_Config:public Praser_Base
    {
    public:
      using Ptr = std::shared_ptr<Praser_Config>;


      int Prase(const std::string& content) override;

      std::string Get_Value(const std::string& key){
        return m_root[key];
      }
    private:
      std::map<std::string,std::string> m_root;
    };


}

//Config_Json的特化
//int 特化
template <>
inline int Praser_NSP::Praser_Json::Get_Value<int>(const rapidjson::Value& root,const std::string& key,int& value)
{
  if(root.HasMember(key.c_str())){
    if(root[key.c_str()].IsInt()){
      value = root[key.c_str()].GetInt();
    }else{
      spdlog::info("Get_Value function : value's type does not match to json's type");
      return VALUE_TYPE_ERROR;
    }
  }else{
    spdlog::info("Get_Value function : json has no member");
    return NO_MEMBER;
  }
  return OK;
}

//uint 特化
template <>
inline int Praser_NSP::Praser_Json::Get_Value<uint>(const rapidjson::Value& root,const std::string& key,uint& value)
{
  if(root.HasMember(key.c_str())){
    if(root[key.c_str()].IsUint()){
      value = root[key.c_str()].GetUint();
    }else{
      spdlog::info("Get_Value function : value's type does not match to json's type");
      return VALUE_TYPE_ERROR;
    }
  }else{
    spdlog::info("Get_Value function : json has no member");
    return NO_MEMBER;
  }
  return OK;
}

//int64特化
template <>
inline int Praser_NSP::Praser_Json::Get_Value<int64_t>(const rapidjson::Value& root,const std::string& key,int64_t& value)
{
  if(root.HasMember(key.c_str())){
    if(root[key.c_str()].IsInt64()){
      value = root[key.c_str()].GetInt64();
    }else{
      spdlog::info("Get_Value function : value's type does not match to json's type");
      return VALUE_TYPE_ERROR;
    }
  }else{
    spdlog::info("Get_Value function : json has no member");
    return NO_MEMBER;
  }
  return OK;
}

//uint64特化
template <>
inline int Praser_NSP::Praser_Json::Get_Value<uint64_t>(const rapidjson::Value& root,const std::string& key,uint64_t& value)
{
  if(root.HasMember(key.c_str())){
    if(root[key.c_str()].IsUint64()){
      value = root[key.c_str()].GetUint64();
    }else{
      spdlog::info("Get_Value function : value's type does not match to json's type");
      return VALUE_TYPE_ERROR;
    }
  }else{
    spdlog::info("Get_Value function : json has no member");
    return NO_MEMBER;
  }
  return OK;
}

//float特化
template <>
inline int Praser_NSP::Praser_Json::Get_Value<float>(const rapidjson::Value& root,const std::string& key,float& value)
{
  if(root.HasMember(key.c_str())){
    if(root[key.c_str()].IsFloat()){
      value = root[key.c_str()].GetFloat();
    }else{
      spdlog::info("Get_Value function : value's type does not match to json's type");
      return VALUE_TYPE_ERROR;
    }
  }else{
    spdlog::info("Get_Value function : json has no member");
    return NO_MEMBER;
  }
  return OK;
}

//double特化
template <>
inline int Praser_NSP::Praser_Json::Get_Value<double>(const rapidjson::Value& root,const std::string& key,double& value)
{
  if(root.HasMember(key.c_str())){
    if(root[key.c_str()].IsDouble()){
      value = root[key.c_str()].GetDouble();
    }else{
      spdlog::info("Get_Value function : value's type does not match to json's type");
      return VALUE_TYPE_ERROR;
    }
  }else{
    spdlog::info("Get_Value function : json has no member");
    return NO_MEMBER;
  }
  return OK;
}

//string特化
template <>
inline int Praser_NSP::Praser_Json::Get_Value<std::string>(const rapidjson::Value& root,const std::string& key,std::string& value)
{
  if(root.HasMember(key.c_str())){
    if(root[key.c_str()].IsString()){
      value = root[key.c_str()].GetString();
    }else{
      spdlog::info("Get_Value function : value's type does not match to json's type");
      return VALUE_TYPE_ERROR;
    }
  }else{
    spdlog::info("Get_Value function : json has no member");
    return NO_MEMBER;
  }
  return OK;
}

//bool特化
template <>
inline int Praser_NSP::Praser_Json::Get_Value<bool>(const rapidjson::Value& root,const std::string& key,bool& value)
{
  if(root.HasMember(key.c_str())){
    if(root[key.c_str()].IsBool()){
      value = root[key.c_str()].GetBool();
    }else{
      spdlog::info("Get_Value function : value's type does not match to json's type");
      return VALUE_TYPE_ERROR;
    }
  }else{
    spdlog::info("Get_Value function : json has no member");
    return NO_MEMBER;
  }
  return OK;
}

//Value特化
template <>
inline int Praser_NSP::Praser_Json::Get_Value<rapidjson::Value>(const rapidjson::Value& root,const std::string& key,rapidjson::Value& value)
{
  if(root.HasMember(key.c_str())){
    const rapidjson::Value& jsonval = root[key.c_str()];
    rapidjson::Document doc;
    value.CopyFrom(jsonval,doc.GetAllocator());
  }else{
    spdlog::info("Get_Value function : json has no member");
    return NO_MEMBER;
  }
  return OK;
}
#endif