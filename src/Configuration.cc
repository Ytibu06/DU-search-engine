#include "Configuration.h"
#include "../include/tinyxml/tinyxml2.h"
#include <iostream>
#include <string>
#include <map>
using std::cout;
using namespace tinyxml2;
using std::cerr;
using std::endl;
using std::string;
using std::map;

// 导入文件路径，构造
Configuration::Configuration(const string &filePath)
: _filePath(filePath)
{
   
}

// 获取对应配置项内容
map<string, string> &Configuration::getConfigMap()
{
   // 如果已经加载过配置，直接返回
    if (!_configMap.empty()) {
        return _configMap;
    }

   XMLDocument doc;
	doc.LoadFile( _filePath.c_str() );
   if(doc.ErrorID()){
      cerr << "LoadFile Error" << endl;
      exit(1);
   }
   _configMap.clear();
   XMLElement *item = nullptr;

   string DICT_PATH,HMM_PATH,USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH;
    //JIEBA_DICT_UTF8
	item = doc.FirstChildElement( "path" )->FirstChildElement( "CPPJIEBA_PATH" )->FirstChildElement( "DICT_PATH" );
   if(item){
      DICT_PATH = item->GetText();
   }
   //HMM_PATH
   item = doc.FirstChildElement( "path" )->FirstChildElement( "CPPJIEBA_PATH" )->FirstChildElement( "HMM_PATH" );
   if(item){
      HMM_PATH = item->GetText();
   }
   //USER_DICT_PATH
   item = doc.FirstChildElement( "path" )->FirstChildElement( "CPPJIEBA_PATH" )->FirstChildElement( "USER_DICT_PATH" );
   if(item){
      USER_DICT_PATH = item->GetText();
   }
   //IDF_PATH
   item = doc.FirstChildElement( "path" )->FirstChildElement( "CPPJIEBA_PATH" )->FirstChildElement( "IDF_PATH" );
   if(item){
      IDF_PATH = item->GetText();
   }
   //STOP_WORD_PATH
   item = doc.FirstChildElement( "path" )->FirstChildElement( "CPPJIEBA_PATH" )->FirstChildElement( "STOP_WORD_PATH" );
   if(item){
      STOP_WORD_PATH = item->GetText();
   }


   _configMap = {
      {"DICT_PATH", DICT_PATH},
      {"HMM_PATH", HMM_PATH},
      {"USER_DICT_PATH", USER_DICT_PATH},
      {"IDF_PATH", IDF_PATH},
      {"STOP_WORD_PATH", STOP_WORD_PATH}
   };

   return _configMap;
}


// 获取停用词词集
set<string> Configuration::getStopWordList()
{
    // 暂时返回空集合
    return _stopWordList;
}