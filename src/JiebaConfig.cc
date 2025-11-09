#include "JiebaConfig.h"

JiebaConfig::JiebaConfig()
{
    _conf[ConfigKey::DICT_PATH] = "../include/cppjieba/dict/jieba.dict.utf8";
    _conf[ConfigKey::HMM_PATH] = "../include/cppjieba/dict/hmm_model.utf8";
    _conf[ConfigKey::USER_DICT_PATH] = "../include/cppjieba/dict/user.dict.utf8";
    _conf[ConfigKey::IDF_PATH] = "../include/cppjieba/dict/idf.utf8";
    _conf[ConfigKey::STOP_WORD_PATH] = "../include/cppjieba/dict/stop_words.utf8";
}

JiebaConfig::~JiebaConfig()
{
}

map<int, string> JiebaConfig::GetConfigMap()
{
    map<int, string> result;
    for (const auto& pair : _conf) {
        result[static_cast<int>(pair.first)] = pair.second;
    }
    return result;
}

string JiebaConfig::getConfigValue(ConfigKey key) {
    auto it = _conf.find(key);
    if (it != _conf.end()) {
        return it->second;
    }
    return "";
}