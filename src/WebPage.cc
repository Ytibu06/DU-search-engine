#include "WebPage.h"
#include "Configuration.h"
#include "SplitTool.h"
#include "DirScanner.h"

#include "../include/tinyxml/tinyxml2.h"
#include "../include/simhash/Simhasher.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using std::string;
using std::cerr;
using std::ifstream;
using std::regex_replace;
using std::regex;
using std::cout;

WebPage::WebPage(string &doc, Configuration &config, SplitToolCppJieba &jieba)
:_doc(doc)
{
    processDoc(doc,config, jieba);  //将每篇文档转换为webPage的成员变量
    set<string> stopWordList = config.getStopWordList();//获取停用词
    //calcTopK(vector<string> &wordsVec, 20, stopWordList)
}
// 获取文档id
int WebPage::getDocId() const
{
    return _docId;
}

string WebPage::getTitle() const
{
    return _docTitle;
}

string WebPage::getUrl() const
{
    return _docUrl;
}

// 获取文档
string WebPage::getDoc() const
{
    return _docContent;
}

// 文档词频统计map
map<string, int> &WebPage::getWordsMap()
{
    return _wordsMap;
}     

// string _doc;//整篇文章，包括xml
//     int _docId; //文档id
//     string _docTitle;   //文档标题
//     string _docUrl; //文档url
//     string _docContent; //文档内容
//     string _docSummary; //文档摘要，自动生成，不固定
//     vector<string> _topWords;   //词频最高的前20个词
//     map<string,int> _wordsMap;  //保存每篇文档的所有词语和词频，不包含停用词


// 对文档进行格式化处理
void WebPage::processDoc(const string &doc, Configuration &config, SplitToolCppJieba &jieba)
{
    tinyxml2::XMLDocument docObj;
    docObj.Parse(doc.c_str());
    tinyxml2::XMLElement *item = docObj.FirstChildElement("item");
    if(item){

        regex pattern(R"(<!\[CDATA\[(.*?)\]\]>)"); //正则

        //剔除标题乱格式
        _docTitle = regex_replace(item->FirstChildElement("title")->GetText(), pattern, "");
        _docUrl = item->FirstChildElement("link")->GetText();   //link转url
        _docContent = item->FirstChildElement("description")->GetText();    //获取描述作为上下文
        _docId  = std::hash<std::string>{}(_docTitle);

        vector<string> result = jieba.cut(_docContent);
        // Process each word in result if needed
        // for example: update word frequency map
        for(const auto &word : result) {
            // 增加词频统计
            _wordsMap[word]++;
        }
    }

}
 
// 获取文档的topk词集
void WebPage::calcTopK(vector<string> &wordsVec, int k, set<string> &stopWordList)
{

}
     

bool operator==(const WebPage &lhs, const WebPage &rhs) // 判断两篇文档是否相等
{
    simhash::Simhasher simhash("../include/simhash/dict/jieba.dict.utf8","../include/simhash/dict/hmm_model.utf8", 
        "../include/simhash/dict/idf.utf8","../include/simhash/dict/stop_words.utf8");
    string lhsContent = lhs.getDoc(), rhsContent = rhs.getDoc();//获取文档内容
    size_t topN = 5;
    uint64_t lhsBin = 0, rhsBin = 0; //指纹
    vector<std::pair<string,double> > lhs_keywords, rhs_keywords; //生成-- 单词 : 权重
    simhash.extract(lhsContent, lhs_keywords, topN);
    simhash.extract(rhsContent, rhs_keywords, topN);
    simhash.make(lhsContent, topN, lhsBin);    //将指纹的值赋值给 u64
    simhash.make(rhsContent, topN, rhsBin);

    //cout << simhash.isEqual(u64_bin1, u64_bin2) << "\n";
    cout << "海明距离为默认3: " << simhash.isEqual(lhsBin, rhsBin) << "\n";
    cout << "海明距离为5: " << simhash.isEqual(lhsBin, rhsBin, 5) << "\n";

    return simhash.isEqual(lhsBin, rhsBin);

}
bool operator<(const WebPage &lhs, const WebPage &rhs)  // 对文档DocId进行排序
{
    return lhs._docId < rhs._docId;
}