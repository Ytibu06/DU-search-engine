#include "SplitToolCppJieba.h"
#include "../include/cppjieba/Jieba.hpp"

SplitToolCppJieba::SplitToolCppJieba(Configuration &conf)
    : _conf(conf)
{
}

vector<string> SplitToolCppJieba::cut(const string &sentence)
{
    // // 从配置中获取路径
    // string dict_path = _conf.getConfigValue(ConfigKey::DICT_PATH);
    // string hmm_path = _conf.getConfigValue(ConfigKey::HMM_PATH);
    // string user_dict_path = _conf.getConfigValue(ConfigKey::USER_DICT_PATH);
    // string idf_path = _conf.getConfigValue(ConfigKey::IDF_PATH);
    // string stop_word_path = _conf.getConfigValue(ConfigKey::STOP_WORD_PATH);

    // cppjieba::Jieba jieba(dict_path.c_str(), 
    //                       hmm_path.c_str(), 
    //                       user_dict_path.c_str(), 
    //                       idf_path.c_str(), 
    //                       stop_word_path.c_str());

    // vector<string> words;
    // jieba.Cut(sentence, words);
    // return words;
}

SplitToolCppJieba::~SplitToolCppJieba()
{
}
