# ifndef __SPLIT_TOOL_CPP_JIEBA_H__
#define __SPLIT_TOOL_CPP_JIEBA_H__

#include "SplitTool.h"
#include "Configuration.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

class SplitToolCppJieba: public SplitTool
{
public:
    SplitToolCppJieba(Configuration &conf);
    virtual ~SplitToolCppJieba();
    virtual vector<string> cut(const string &sentence);


private:
    Configuration & _conf;  //配置文件路径
};
#endif