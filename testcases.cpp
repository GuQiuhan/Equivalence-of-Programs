#include <limits.h>
#include "handle.h"
#include "mainwindow.h"
#include "manual.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std;
#include "gtest/gtest.h"
#include "mainwindow.h"
#include "start.h"

#include <limits.h>
#include <time.h>

//使用gtest框架进行单元测试
//namespace {
//    测试handle()函数输入空字符串
//    TEST(HandleTest, Empty)
//    {
//        vector<vector<pair<QString,QString>>> tmp={{},{}};
//        EXPECT_EQ(tmp,Handle().handle(nullptr));
//    }



//    //测试输入不包含指定文件
//    TEST(InputParaTest, WrongDir)
//    {

//        EXPECT_EQ("",Handle().inputPara("/Users/pro/Desktop/test1","/Users/pro/Desktop/test1/stdin_format.txt"));
//    }

//    //测试输入包含指定文件
//    TEST(InputParaTest, RightDir)
//    {

//        EXPECT_NE("",Handle().inputPara("/Users/pro/Desktop/test2","/Users/pro/Desktop/test2/stdin_format.txt"));
//    }

//    //测试while循环每一次都可以循环到
//    TEST(InputParaTest, RightType)
//    {
//        ifstream fin;
//        fin.open(Handle().inputPara("/Users/pro/Desktop/test2","/Users/pro/Desktop/test2/stdin_format.txt"));
//        string s;
//        getline(fin,s);
//        int cnt=0;
//        size_t pos = s.find(" ");//分割
//        while (pos != string::npos)
//        {
//            s = s.substr(pos+1, s.size());
//            pos = s.find(" ");//分割
//            cnt++;
//        }
//        if(s!="") cnt++;
//        EXPECT_EQ(3,cnt);
//    }

//        TEST(InputParaTest, RightType2)
//        {
//            ifstream fin;
//            fin.open(Handle().inputPara("/Users/pro/Desktop/test2","/Users/pro/Desktop/test2/stdin_format.txt"));
//            string s;
//            getline(fin,s);
//            int cnt=0;
//            size_t pos = s.find(" ");

//            string test=s.substr(0,pos);
//            EXPECT_LT("a", test);
//            EXPECT_GT(test, "z");
//            s = s.substr(pos+1, s.size());
//            pos = s.find(" ");
//            test=s.substr(0,pos);
//            EXPECT_EQ(1,atoi(test.c_str()));
//            s = s.substr(pos+1, s.size());
//            pos = s.find(" ");
//            test=s.substr(0,pos);
//            EXPECT_EQ(2,test.size());
//          }
//}

//使用gtest框架进行集成测试
class QuickTest : public testing::Test {
 protected:
  // Remember that SetUp() is run immediately before a test starts.
  // This is a good place to record the start time.
  void SetUp() override { start_time_ = time(nullptr); }

  // TearDown() is invoked immediately after a test finishes.  Here we
  // check if the test was too slow.
  void TearDown() override {
    // Gets the time when the test finishes
    const time_t end_time = time(nullptr);

    // Asserts that the test took no more than ~5 seconds.
    EXPECT_TRUE(end_time - start_time_ <= 5) << "The test took too long.";
  }

  // The UTC time (in seconds) when the test starts
  time_t start_time_;
};


// We derive a fixture named IntegerFunctionTest from the QuickTest
// fixture.  All tests using this fixture will be automatically
// required to be quick.
class IntegerFunctionTest : public QuickTest {
  // We don't need any more logic than already in the QuickTest fixture.
  // Therefore the body is empty.
};

//测试handle()函数输入空字符串
TEST(HandleTest, Empty)
{
    vector<vector<pair<QString,QString>>> tmp={{},{}};
    EXPECT_EQ(tmp,Handle().handle(nullptr));
}

//测试输入不包含指定文件
TEST(InputParaTest, WrongDir)
{

    EXPECT_EQ("",Handle().inputPara("/Users/pro/Desktop/test1","/Users/pro/Desktop/test1/stdin_format.txt"));
}

//测试输入包含指定文件
TEST(InputParaTest, RightDir)
{

    EXPECT_NE("",Handle().inputPara("/Users/pro/Desktop/test2","/Users/pro/Desktop/test2/stdin_format.txt"));
}

//测试while循环每一次都可以循环到
TEST(InputParaTest, RightType)
{
    ifstream fin;
    fin.open(Handle().inputPara("/Users/pro/Desktop/test2","/Users/pro/Desktop/test2/stdin_format.txt"));
    string s;
    getline(fin,s);
    int cnt=0;
    size_t pos = s.find(" ");//分割
    while (pos != string::npos)
    {
        s = s.substr(pos+1, s.size());
        pos = s.find(" ");//分割
        cnt++;
    }
    if(s!="") cnt++;
    EXPECT_EQ(3,cnt);
}

//测试while循环每一次都可以循环到
TEST(InputParaTest, RightType2)
{

    ifstream fin;
    fin.open(Handle().inputPara("/Users/pro/Desktop/test2","/Users/pro/Desktop/test2/stdin_format.txt"));
    string s;
    getline(fin,s);
    int cnt=0;
    size_t pos = s.find(" ");

    string test=s.substr(0,pos);
    EXPECT_LT("a", test);
    EXPECT_GT(test, "z");
    s = s.substr(pos+1, s.size());
    pos = s.find(" ");
    test=s.substr(0,pos);
    EXPECT_EQ(1,atoi(test.c_str()));
    s = s.substr(pos+1, s.size());
    pos = s.find(" ");
    test=s.substr(0,pos);
    EXPECT_EQ(2,test.size());

}



