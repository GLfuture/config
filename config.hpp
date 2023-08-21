#pragma once
#include <cstdint>
#include <string>
#ifndef CONFIG_HPP
#define CONFIG_HPP
#endif
#include <iostream>
#include <fstream>
#include <rapidjson/document.h>
namespace Config_NSP {
    using namespace rapidjson;
    class Config_Base{
    public:
        Config_Base(const Config_Base&&) = delete;
        Config_Base& operator=(const Config_Base&) = delete;
        Config_Base(const Config_Base&)=delete;
        Config_Base& operator=(const Config_Base&&) = delete;
        Config_Base(const char* config_file)
        {
          std::ifstream file;
          file.open(config_file);
          if (!file.is_open()||file.fail()) {
            printf("open config file failed!\n");
            exit(-1);
          }
          file.seekg(0, std::ios::end);
          uint64_t length = file.tellg();
          file.seekg(0, std::ios::beg);
          char *buffer = new char[length];
          memset(buffer, 0, length);
          file.read(buffer, length);
          doc.Parse(buffer);
          if (doc.HasParseError()) {
            printf("Prase Error!\n");
            file.close();
            exit(-1);
          }
          file.close();
        }
        virtual void Generate_Config();
    protected:
        Document doc;
    };

    
}