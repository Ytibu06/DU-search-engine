#ifndef __PAGE_LIB_PREPROCESSOR_H__
#define __PAGE_LIB_PREPROCESSOR_H__ 

#include "Configuration.h"
#include "WordSegmentation.h"


/**
 * 网页库预处理类
 */

class PageLibPreprocessor{
public:
    PageLibPreprocessor(Configuration &conf);
    void doProcess();    //预处理

private:
    void readInfoFromFile();    //根据配置信息读取网页库和位置偏移库的内容
    void cutRedundantPages();   //对冗余的网页进行去重
    void buildInvertIndexTable();   //创建倒排索引表
    void storeOnDisk();  //将经过预处理之后的网页库、位置偏移库和倒排索引表写回到磁盘上
private:
    WordSegmentation _jieba;    // 分词对象
    vector <WebPage> _pageLib;  // 网页库容器的对象
    unordered_map<int, pair<int, int> > _offsetLib; //网页库对象
    unordered_map<string, vector<pair<int, double> > _invertIndexTable; //倒排索引表对象
};

#endif