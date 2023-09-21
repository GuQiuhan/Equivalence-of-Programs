#ifndef HANDLE_H
#define HANDLE_H
#include<QString>
#include <vector>
#include <string>


using namespace std;




class Handle
{
private:
    QString dir;
    vector<pair<QString,QString>> ansEqual;//存储结果,可直接访问
    vector<pair<QString,QString>> ansUnequal;


//    vector<string> getFilesList(string dir);//读取目录列表
//    vector<string> getDirsList(string dirpath);//读取某一目录下的文件
//    string inputPara(string dir,string path);//构造随机输入
//    string exec(string dir,string input, string cpp);

//    void Classify(string Dir, vector<string> outputs);

public:
    vector<vector<pair<QString,QString>>> handle(QString dir);//返回两个列表，ans[0]是等价，ans[1]是不等价


    vector<string> getFilesList(string dir);//读取目录列表
    vector<string> getDirsList(string dirpath);//读取某一目录下的文件
    string inputPara(string dir,string path);//构造随机输入
    string exec(string dir,string input, string cpp);

    void Classify(string Dir, vector<string> outputs);



};


#endif // HANDLE_H
