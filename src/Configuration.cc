#include "Configuration.h"
#include "../include/tinyxml/tinyxml2.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <string>

using std::cout;
using namespace tinyxml2;
using std::cerr;
using std::endl;
using std::ifstream;
using std::map;
using std::string;
using std::vector;

Configuration &Configuration::getInstance(const string &filePath)
{
   static Configuration instance(filePath);
   return instance;
}

// 导入文件路径，构造
Configuration::Configuration(const string &filePath)
    : _filePath(filePath)
{
}

Configuration::~Configuration()
{
}

// 获取对应配置项内容
map<string, string> &Configuration::getConfigMap()
{
   // 如果已经加载过配置，直接返回
   if (!_configMap.empty())
   {
      return _configMap;
   }

   XMLDocument doc;
   doc.LoadFile(_filePath.c_str());
   if (doc.ErrorID())
   {
      cerr << "LoadFile Error" << endl;
      exit(1);
   }
   _configMap.clear();
   XMLElement *item = nullptr;

   string DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH;
   string jieba_dict_path, hmm_model_path, idf_path, stop_words_path;

   // JIEBA_DICT_UTF8

   // 获取根节点下的path节点
   XMLElement *pathElement = doc.FirstChildElement("path");
   if (!pathElement)
   {
      cerr << "Cannot find path element" << endl;
      exit(1);
   }

   // 获取CPPJIEBA_PATH节点
   XMLElement *cppjiebaElement = pathElement->FirstChildElement("CPPJIEBA_PATH");
   if (cppjiebaElement)
   {
      // JIEBA字典路径
      item = cppjiebaElement->FirstChildElement("DICT_PATH");
      if (item)
      {
         DICT_PATH = item->GetText();
      }

      // HMM模型路径
      item = cppjiebaElement->FirstChildElement("HMM_PATH");
      if (item)
      {
         HMM_PATH = item->GetText();
      }

      // 用户字典路径
      item = cppjiebaElement->FirstChildElement("USER_DICT_PATH");
      if (item)
      {
         USER_DICT_PATH = item->GetText();
      }

      // IDF路径
      item = cppjiebaElement->FirstChildElement("IDF_PATH");
      if (item)
      {
         IDF_PATH = item->GetText();
      }

      // 停用词路径
      item = cppjiebaElement->FirstChildElement("STOP_WORD_PATH");
      if (item)
      {
         STOP_WORD_PATH = item->GetText();
      }
   }

   XMLElement *simhashElement = pathElement->FirstChildElement("SIMHASH_PATH");
   if (simhashElement)
   {
      item = simhashElement->FirstChildElement("jieba_dict_path");
      if (item)
      {
         jieba_dict_path = item->GetText();
      }
      item = simhashElement->FirstChildElement("hmm_model_path");
      if (item)
      {
         hmm_model_path = item->GetText();
      }
      item = simhashElement->FirstChildElement("idf_path");
      if (item)
      {
         idf_path = item->GetText();
      }
      item = simhashElement->FirstChildElement("stop_words_path");
      if (item)
      {
         stop_words_path = item->GetText();
      }
   }

   _configMap = {
       {"DICT_PATH", DICT_PATH},
       {"HMM_PATH", HMM_PATH},
       {"USER_DICT_PATH", USER_DICT_PATH},
       {"IDF_PATH", IDF_PATH},
       {"STOP_WORD_PATH", STOP_WORD_PATH},

       {"jieba_dict_path", jieba_dict_path},
       {"hmm_model_path", hmm_model_path},
       {"idf_path", idf_path},
       {"stop_words_path", stop_words_path}};

   return _configMap;
}

// 获取停用词词集
set<string> Configuration::getStopWordList()
{
   XMLDocument doc;
   doc.LoadFile(_filePath.c_str());
   if (doc.ErrorID())
   {
      cerr << "LoadFile Error" << endl;
      exit(1);
   }

   XMLElement *item = nullptr;
   vector<string> paths;

   // 获取根节点下的path节点
   XMLElement *pathElement = doc.FirstChildElement("path");
   if (!pathElement)
   {
      cerr << "Cannot find path element" << endl;
      exit(1);
   }

   XMLElement *stopWordElement = pathElement->FirstChildElement("STOP_WORD_LIST");
   if (!stopWordElement)
   {
      cerr << "Cannot find STOP_WORD_LIST element" << "\n";
      exit(1);
   }

   item = stopWordElement->FirstChildElement("STOP_WORDS_EN");
   if (item)
   {
      paths.push_back(item->GetText());
   }
   item = stopWordElement->FirstChildElement("STOP_WORDS_CN");
   if (item)
   {
      paths.push_back(item->GetText());
   }

   for (auto &path : paths)
   {
      ifstream ifs(path);
      if (!ifs)
      {
         cerr << "open file error in getStopWordList: " << path << "\n";
      }

      string line;
      while (getline(ifs, line))
      {
         
         string stop;
         std::istringstream iss(line);
         while (iss >> stop)
         {
            _stopWordList.insert(stop);
         }
      }

      ifs.close();
   }

   // 暂时返回空集合
   return _stopWordList;
}