#include "SplitTool.h"

class SplitToolCppJieba: public SplitTool
{
public:
    SplitToolCppJieba(Configuration &conf);
    virtual ~SplitToolCppJieba();
    virtual vector<string> cut(const string &sentence);
    

private:
    Configuration & _conf;  //配置文件路径
};