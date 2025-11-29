#include "SplitTool.h"
#include "../include/cppjieba/Jieba.hpp"
#include <iostream>
using std::cout;
using std::map;

//Configuration &conf
SplitToolCppJieba::SplitToolCppJieba(Configuration &conf)
:_conf(conf)
{
}
SplitToolCppJieba::~SplitToolCppJieba()
{
}
vector<string> SplitToolCppJieba::cut(const string &sentence)
{
    auto map = _conf.getConfigMap();

    const char *const DICT_PATH = map["DICT_PATH"].c_str(); //c++风格字符串转换为c风格字符串
    const char *const HMM_PATH = map["HMM_PATH"].c_str();
    const char *const USER_DICT_PATH = map["USER_DICT_PATH"].c_str();
    const char *const IDF_PATH = map["IDF_PATH"].c_str();
    const char *const STOP_WORD_PATH = map["STOP_WORD_PATH"].c_str();

    cppjieba::Jieba jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);   //使用配置文件创建分词对象
    vector<string> result;  //结果向量

    jieba.Cut(sentence, result, true);

    return result;
}