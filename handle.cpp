#include "handle.h"

#include <iostream>
#include <fstream>
#include <memory.h>
#include <dirent.h>
#include <vector>
#include <cstdlib>
//#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utility>
using namespace std;

vector<string> Handle::getDirsList(string dirpath)//获取input下的所有文件夹
{
    vector<string> allDir;

    DIR *dir = opendir(dirpath.c_str());
    if (dir == nullptr)
    {
        cout << "opendir error" << endl;
        return allDir;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR){//It's dir
            if(((std::string)entry->d_name).find_first_of("."))//这一行代码是为啥？
            {
                string p = dirpath + "/" + entry->d_name;
                //cout<< p<<endl;
                allDir.push_back(p);
            }
        }

    }
    closedir(dir);
    /**cout << "输出所有文件目录的路径：" << endl;
    for (size_t i = 0; i < allDir.size(); i++)
     {
       string filename = allDir.at(i);
       cout << filename << endl;
     }**/
    return allDir;
}

vector<string> Handle::getFilesList(string dirpath)//返回某一目录下的所有文件(包括txt文件)
{
    vector<string> allPath;

    DIR *dir = opendir(dirpath.c_str());
    if (dir == nullptr)
    {
        cout << "opendir error" << endl;
        return allPath;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR){//It's dir,一般不会
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            string dirNew = dirpath + "/" + entry->d_name;
            vector<string> tempPath = getFilesList(dirNew);//这里有个迭代
            allPath.insert(allPath.end(), tempPath.begin(), tempPath.end());

        }else {
            //cout << "name = " << entry->d_name << ", len = " << entry->d_reclen << ", entry->d_type = " << (int)entry->d_type << endl;
            string name = entry->d_name;
            string imgdir = dirpath +"/"+ name;
            //sprintf("%s",imgdir.c_str());
            allPath.push_back(imgdir);
        }

    }
    closedir(dir);
    //system("pause");

    /**检查文件路径
    cout << "Enter a directory: "<< dirpath << endl;
    cout << "输出所有文件的路径：" << endl;
    for (size_t i = 0; i < allPath.size(); i++)
     {
       string filename = allPath.at(i);
       cout << filename << endl;
     }
    cout<<endl;**/
    return allPath;
}

string Handle::inputPara(string dir,string path)//根据输入格式构造随机输入，输入在当前目录的input.txt里
{
    ofstream fout;
    string inputtxt_path=dir+"/input.txt";
    //cout<<"here:"<<inputtxt_path<<endl;

    fout.open(inputtxt_path);//在目录下创建一个标准输入文件
    if(fout) cout<< endl<<"Success to create"<<inputtxt_path<<endl<<endl;
    if (!fout.is_open())  cout << "Fail to create the file" << inputtxt_path <<endl;

    ifstream fin;
    fin.open(path,ios::in); //打开文件
    if (!fin.is_open())//文件不存在
    {
        cout << "Fail to read the file" << path <<endl;
        return "";//delete
    }

    else{//delete
    string buf;
    getline(fin,buf);//读取一行
    size_t pos = buf.find(" ");//分割

    // 若找不到内容则字符串搜索函数返回 npos
    while (pos != string::npos)
    {
        string temp = buf.substr(0, pos);
        if(temp=="char") fout<<'a' + rand() % 26<<" "; //随机生成一个字符
        else
        {
            size_t pos1 = temp.find("(");//分割
            size_t pos2=temp.find(",");
            size_t pos3=temp.find(")");
            string type=temp.substr(0, pos1);//获得类型
            int x=std::stoi(temp.substr(pos1+1,pos2-pos1-1));
            int y=std::stoi(temp.substr(pos2+1,pos3-pos2-1));

            //cout<< type << " "<< x << " "<<y<<endl;
            if(type=="int")
                fout<<(rand() % (y-x+1))+ x<<" ";
            else
            {
                string tmp="";
                int len=(rand() % (y-x+1))+ x;//随机长度
                for(int i=0; i<len; ++i)
                {
                    tmp+='a' + rand() % 26;//随机字符
                }
                fout<<tmp<<" ";
            }
        }
        //去掉已分割的字符串,在剩下的字符串中进行分割

        buf = buf.substr(pos + 1, buf.size());
        pos = buf.find(" ");
    }
    if(buf!="")//最后一组
    {
        if(buf=="char") {cout<<"haha"<<endl;}//fout<<(char)('a' + rand() % 26)<<" "; //随机生成一个字符
        else
        {
            size_t pos1 = buf.find("(");//分割
            size_t pos2=buf.find(",");
            size_t pos3=buf.find(")");
            string type=buf.substr(0, pos1);//获得类型
            //buf = buf.substr(pos1 + 1, buf.size()-1);//去掉")",变成x,y
            int x=std::stoi(buf.substr(pos1+1,pos2-pos1-1));
            int y=std::stoi(buf.substr(pos2+1,pos3-pos2-1));

            //cout<< type << " "<< x << " "<<y<<endl;
            if(type=="int")
                fout<<(rand() % (y-x+1))+ x<<" ";
            else
            {
                string tmp="";
                int len=(rand() % (y-x+1))+ x;//随机长度
                for(int i=0; i<len; ++i)
                {
                    tmp+='a' + rand() % 26;//随机字符
                }
                fout<<tmp<<" ";
            }
        }
    }

    /**经过实验得出，重定向的input文件中最后是否需要回车、是否多了空格没有影响**/
    fin.close();
    fout.close();


    return inputtxt_path;
    }//delete
}


string Handle::exec(string dir,string input, string cpp)//执行文件，将输出文件保存至目录下，同时返回输出文件路径
{
    size_t pos1=cpp.find("/input");
    string tmp=cpp.substr(0,pos1)+"/exec_out"+cpp.substr(pos1+6,cpp.size());
    cout<<"Now:"<<tmp <<endl;
    size_t pos2=tmp.find(".");
    string outPath = tmp.substr(0, pos2)+"_output.txt";
    string execFile= tmp.substr(0, pos2);//gcc生成的可执行文件

    string cmd1="g++ "+cpp+" -o "+execFile;
    string cmd2=execFile+" < "+input+" > "+outPath;

    cout<< cmd1<<endl <<cmd2<<endl<<endl;

    system((char*)cmd1.c_str());
    system((char*)cmd2.c_str());

    return outPath;

}

void Handle::Classify(string Dir, vector<string> outputs)
{
    size_t pos=Dir.find("/input");
    string equal=Dir.substr(0,pos)+"/output/equal.csv";
    string unequal=Dir.substr(0,pos)+"/output/unequal.csv";

    ofstream foutEqual,foutUnequal;
    foutEqual.open(equal, ios::app); // 打开模式可省略
    foutUnequal.open(unequal, ios::app); // 打开模式可省略
    if (!foutEqual.is_open())  cout << "Fail to read the file" << equal <<endl;
    if (!foutUnequal.is_open())  cout << "Fail to read the file" << unequal <<endl;

    for(size_t i=0; i<outputs.size()-1;++i)//读取outputs[i]和outputs[j]txt文件内容，判断是否相等，并将这一对加入响应的文件里
    {
        vector<string> ans1;

        size_t pos=outputs[i].find("_output");
        string cpp0 = outputs[i].substr(0, pos)+".cpp";
        size_t pos1=cpp0.find("/exec_out");
        string cpp1=cpp0.substr(0,pos1)+"/input"+cpp0.substr(pos1+9,cpp0.size());


        ifstream fin;
        fin.open(outputs[i],ios::in); //打开文件
        if (!fin.is_open())  cout << "Fail to read the file" << outputs[i] <<endl;
        string buf;
        while (getline(fin, buf)) ans1.push_back(buf);
        fin.close();

        for(size_t j=i+1; j<outputs.size();++j)
        {
            vector<string> ans2;
            pos=outputs[j].find("_output");
            cpp0 = outputs[j].substr(0, pos)+".cpp";
            size_t pos1=cpp0.find("/exec_out");
            string cpp2=cpp0.substr(0,pos1)+"/input"+cpp0.substr(pos1+9,cpp0.size());

            cout<<outputs[i]<<endl << outputs[j]<<endl;

            fin.open(outputs[j],ios::in); //打开文件
            if (!fin.is_open())  cout << "Fail to read the file" << outputs[j] <<endl;
            string buf;
            while (getline(fin, buf)){ ans2.push_back(buf);}
            fin.close();

            if(ans1.size()!=ans2.size())//加入unequal文件
            {
                //cout<< ans1.size()<< " "<< ans2.size()<<endl;
                foutUnequal << cpp1 << ',' << cpp2 <<  endl;
                pair<QString,QString> p(QString::fromStdString(cpp1),QString::fromStdString(cpp2));
                ansUnequal.push_back(p);

            }
            else
            {
                bool flag=true;
                for(size_t k=0; k<ans1.size(); ++k)
                {

                    cout << ans1[k]<<endl<<ans2[k]<<endl;

                    if(ans1[k]!=ans2[k])
                    {
                        flag=false;
                        break;
                    }
                }
                if(flag)
                {
                    foutEqual << cpp1 << ',' << cpp2 <<  endl;//加入equal文件
                    pair<QString,QString> p(QString::fromStdString(cpp1),QString::fromStdString(cpp2));
                    ansEqual.push_back(p);
                }
                else
                {
                    foutUnequal << cpp1 << ',' << cpp2 <<  endl;//加入unequal文件
                    pair<QString,QString> p(QString::fromStdString(cpp1),QString::fromStdString(cpp2));
                    ansUnequal.push_back(p);
                }
            }
        }
    }

    foutEqual.close();
    foutUnequal.close();
}

vector<vector<pair<QString,QString>>> Handle::handle(QString dir)//处理输入的目录，最终在目录中构成两个csv文件
{

    cout<<endl <<endl<<"*************************************************************************************"<<endl;
    cout<< "Clear..."<<endl;
    cout<<"*************************************************************************************"<<endl;

    //确定输出文件路径名
    //创建两个目录：output用于存放csv文件，exec_out用于存放程序输出文件
    //所以此时一共有三个目录:input、output、exec_out
    size_t pos1=dir.toStdString().find("/input");
    string outputDir=dir.toStdString().substr(0,pos1)+"/output";
    string execOutDir=dir.toStdString().substr(0,pos1)+"/exec_out";

    //清除上次执行的输出文件
    string rmdir1="rm -rf "+outputDir;
    string rmdir2="rm -rf "+execOutDir;
    system((char*)rmdir1.c_str());
    system((char*)rmdir2.c_str());

    //新建文件夹
    string mkdir1="mkdir "+outputDir;
    string mkdir2="mkdir "+execOutDir;
    system((char*)mkdir1.c_str());
    system((char*)mkdir2.c_str());

    cout<<endl <<endl<<"*************************************************************************************"<<endl;
    cout<< "Finish cleaning. Ready to go!"<<endl;
    cout<<"*************************************************************************************"<<endl;


    vector<string> dirs=getDirsList(dir.toStdString());//切分目录

    for(auto tmpDir:dirs)
    //for(size_t i=0; i<dirs.size(); ++i)
    {
        //string tmpDir=dirs[i];
        //cout<<" tmp Dir:" <<tmpDir<<endl;

        //在exec_out文件夹中再次创建当前目录
        size_t pos=tmpDir.find_last_of("/");
        string sonDir= execOutDir+tmpDir.substr(pos,tmpDir.size());
        string mkdir3="mkdir "+sonDir;
        system((char*)mkdir3.c_str());


        //获取目录下文件列表
        vector<string> files=getFilesList(tmpDir);

        //获取标准输入文件
        string inputPath;
        for(vector<string>::iterator it=files.begin();it!=files.end();it++)//找到txt文件并删除
        {
            if(it->find("stdin_format.txt")!=string::npos)
            {
                inputPath=*it;
                files.erase(it);//删除此文件
                break;
            }

        }

        //cout<< "input Path:"<<inputPath<<endl;

        //在目录下构造标准输入文件
        string input=inputPara(tmpDir,inputPath);

        //将构造输入文件从源文件夹中删除，防止执行
        for(vector<string>::iterator it=files.begin();it!=files.end();it++)//找到txt文件并删除
        {
            if(it->find("input.txt")!=string::npos)
            {
                files.erase(it);//删除此文件
                break;
            }

        }

        //将.DS_Store从源文件夹中删除，防止执行
        for(vector<string>::iterator it=files.begin();it!=files.end();it++)//找到txt文件并删除
        {
            if(it->find(".DS_Store")!=string::npos)
            {
                files.erase(it);//删除此文件
                break;
            }

        }

        //cout<< "input:"<<input<<endl;


        //依次执行文件并返回输出文件地址
        vector<string> outputFiles;
        for(size_t i=0; i<files.size(); ++i)
        {


            string o=exec(tmpDir,input, files[i]);
            outputFiles.push_back(o);
            //cout<<"output file:"<<o<<endl;
        }

        Classify(dir.toStdString(),outputFiles);//判断输出文件并分类至两个csv文件中
    }


    cout<<endl <<endl<<"*************************************************************************************"<<endl;
    cout<< "Finish!"<<endl;
    cout<<"Please check /output/equal.csv & /output/unequal.csv"<<endl;
    cout<<"*************************************************************************************"<<endl;


    vector<vector<pair<QString,QString>>> ans;
    ans.push_back(ansEqual);
    ans.push_back(ansUnequal);

    return ans;

}
