#include "DictProducer.h"

/**/
DictProducer::DictProducer(const string &dir)
{

}

/*中文词典构造函数*/
DictProducer::DictProducer(const string &dir, SplitTool *splitTool)
{

}
DictProducer::~DictProducer(){}

/*英文词典建立*/
void DictProducer::buildEnDict(){}
/*中文词典建立*/
void DictProducer::buildCnDict(){}
void DictProducer::storeDict(const char *filePath){}
void DictProducer::showFiles() const{}
void DictProducer::showDict() const{}
void DictProducer::getFiles(){}
void DictProducer::pushDict(const std::string &word){}

/*std::vector<std::pair<std::string,int>> _dict;  //词典(词语,频数)
    std::map<std::string, int> _index;  //词典索引（单词,词典索引）
    SplitTool *_splitTool;  //分词工具
    vector<string> _files;  //语料库文件的路径*/