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
#include <cstdint>

using std::cerr;
using std::cout;
using std::ifstream;
using std::regex;
using std::regex_replace;
using std::string;

WebPage::WebPage(string &doc, Configuration &config, SplitToolCppJieba &jieba)
: _doc(doc)
{
    //处理文档，每个文档转换成一个网页对象
    processDoc(doc, config, jieba);
    setSimHash();

}
// 获取文档id
int WebPage::getDocId() const
{
    return _docId;
}

// 获取文档
string WebPage::getDoc() const
{
    return _docContent;
}

string WebPage::getTitle() const
{
    return _docTitle;
}

string WebPage::getUrl() const
{
    return _docUrl;
}
uint64_t WebPage::getSimHash() const
{
    return _simHash;
}

// 文档词频统计map
map<string, int> &WebPage::getWordsMap()
{
    return _wordsMap;
}


// 对文档进行格式化处理，并生成一个文档对象，文章内容交给topK生成词频和topK
void WebPage::processDoc(const string &docString, Configuration &config, SplitToolCppJieba &jieba)
{
    set<string> stopWordList = config.getStopWordList();

    tinyxml2::XMLDocument docMention;
    docMention.Parse(docString.c_str());
    if (docMention.ErrorID())
    {
        cerr << "WebPage::processDoc: Parse" << docString << " error" << "\n";
    }

    tinyxml2::XMLElement *doc = docMention.FirstChildElement("doc");
    if (doc)
    {
        _docId = std::stoi(doc->FirstChildElement("docid")->GetText());
        _docUrl = doc->FirstChildElement("url")->GetText();
        _docTitle = doc->FirstChildElement("title")->GetText();
        _docContent = doc->FirstChildElement("content")->GetText();

        vector<string> vec = jieba.cut(_docContent + _docTitle);

        calcTopK(vec, 20, stopWordList); // topK统计词频，并统计topK个词

    }
}

//获取所有词频和topK
void WebPage::calcTopK(vector<string> &wordsVec, int k, set<string> &stopWordList)
{

    for (auto &word : wordsVec)
    {
        if (!stopWordList.count(word) && getByteNum_Utf8(word[0]) == 3)
        {
            // 这是一个中文词，继续处理
            if (_wordsMap.find(word) != _wordsMap.end())
            {
                ++_wordsMap[word];
            }
            else
            {
                _wordsMap[word] = 1;
            }
        }
    }

    int count = 0;
    for (auto &elem : _wordsMap)
    {
        if (count >= k)
            break;
        _topWords.push_back(elem.first);
        ++count;
    }
}

//simhash值计算
void WebPage::setSimHash()
{
    simhash::Simhasher simhash("../include/simhash/dict/jieba.dict.utf8", "../include/simhash/dict/hmm_model.utf8",
                               "../include/simhash/dict/idf.utf8", "../include/simhash/dict/stop_words.utf8");
    string lhsContent = _docContent + _docTitle;
    size_t topN = 5;
    uint64_t lhsBin = 0;                              // 指纹
    vector<std::pair<string, double>> lhs_keywords, rhs_keywords; // 生成-- 单词 : 权重
    simhash.extract(lhsContent, lhs_keywords, topN);
    simhash.make(lhsContent, topN, lhsBin); // 将指纹的值赋值给 u64

    _simHash = lhsBin;
}

//首字节判断
size_t WebPage::getByteNum_Utf8(const char byte)
{
    int byteNum = 0;
    for (size_t i = 0; i < 6; ++i)
    {
        if (byte & (1 << (7 - i)))
            ++byteNum;
        else
            break;
    }
    return byteNum == 0 ? 1 : byteNum;
}

// 判断两篇文档是否相等
bool operator==(const WebPage &lhs, const WebPage &rhs) 
{
    return simhash::Simhasher::isEqual(lhs.getSimHash(), rhs.getSimHash());
}

// 对文档DocId进行排序
bool operator<(const WebPage &lhs, const WebPage &rhs) 
{
    return lhs._docId < rhs._docId;
}