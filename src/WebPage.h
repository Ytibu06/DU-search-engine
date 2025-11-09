#ifndef __WEBPAGE_H__
#define __WEBPAGE_H__ 

#include "Configuration.h"
#include "WordSegmentation.h"
#include <string>
#include <vector>
#include <map>
using std::string;
using std::vector;
using std::map;

/**
 * 网页类
 */


friend bool operator==(const WebPage & lhs, const WebPage & rhs);   //判断两篇文档是否相等
friend bool operator<(const WebPage & lhs, const WebPage & rhs); //对文档DocId进行排序
class WebPage {
public:
    WebPage(string &doc, Configuration *config, WordSegmentation &jieba);
    int getDocId(); //获取文档id
    string getTitle();    //获取文档标题
    string summary(const vector<string> &queryWords);
    map<string,int> &getWordsMap(); //文档词频统计map

private:
    void processDoc(const string &doc, Configuration &config, WordSegmentation &);  //对文档进行格式化处理
    void calcTopK(vector<string> &wordsVec, int k, set<string> &stopWordList);   //获取文档的topk词集


private:
    const static int TOPK_NUMBER = 20;
    int _docId; //文档id
    string _docTitle;   //文档标题
    string _docUrl; //文档url
    string _docContent; //文档内容
    string _docSummary; //文档摘要，自动生成，不固定
    vector<string> _topWords;   //词频最高的前20个词
    map<string,int> _wordsMap;  //保存每篇文档的所有词语和词频，不包含停用词

};

#endif