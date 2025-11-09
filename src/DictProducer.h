#include <vector>
#include <string>
#include <map>
#include "SplitTool.h"


/**
 * 词典生成类
 */



class DictProducer {
public:
    DictProducer(const string &dir);
    DictProducer(const string &dir, SplitTool *splitTool);  //中文词典构造函数
    void buildEnDict(); //创建英文词典
    void buildCnDict(); //创建中文词典
    void storeDict(const char *filePath);   //词典写入文件
    void showFiles()const;  //查看文件路径（测试）
    void showDict()const;   //查看词典（测试）

private:
    void getFiles();    //获取文件的绝对路径
    void pushDict(const std::string &word); //添加词典(存储某个单词)


private:
    std::vector<std::pair<std::string,int>> _dict;  //词典(词语,频数)
    std::map<std::string, int> _index;  //词典索引（单词,词典索引）
    SplitTool *_splitTool;  //分词工具
    vector<string> _files;  //语料库文件的路径
};