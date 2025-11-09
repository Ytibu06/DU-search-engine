#ifndef __JIEBA_CONFIG_H__
#define __JIEBA_CONFIG_H__

#include "Configuration.h"

class JiebaConfig : public Configuration
{
public:
    JiebaConfig();
    ~JiebaConfig();
    virtual map<int, string> GetConfigMap() override;
    virtual string getConfigValue(ConfigKey key) override;
};

#endif