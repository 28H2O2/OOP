#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;

class vec
{ //需要用到vector的一个类
private:
    vector<string> vec_a1; // define vector1
    vector<string> vec_a2; // define vector2
    vector<string> vec_b;  // define2 vector
public:
    void identify_def(char *p);                 // function declaration
    void identify_void(char *p, ofstream *out); // function declaration
    void identify_if(char *p, int *q);          // function declaration
    void vector_clear();                        // clear vector
};

int main() // main function
{
    vec V; // class declaration
    int identify(char *p);                          // function declaration
    void Open_file(string p, ofstream * out);       // function declaration
    string identify_inc(char *p);                   // function declaration
    string filename;                                // filename declartion
    const string name1 = "testcase1.txt";           // input filename
    const string name2 = "testcase2.txt";           // input filename
    char s1[100], s2[100];                          //用于读入文件中每行文字
    ifstream infile1(name1, ios::in | ios::binary); // 用二进制方法打开文件1
    if (!infile1)
    { // open failed
        cout << "error opening source file." << endl;
        return 0;
    }
    ifstream infile2(name2, ios::in | ios::binary); // 用二进制方法打开文件2
    if (!infile2)
    { // open failed
        cout << "error opening source file." << endl;
        return 0;
    }

    ofstream outfile1, outfile2; //  输出txt文件
    outfile1.open("out1.txt");
    outfile2.open("out2.txt");
    
    int flag1 = 0;                   //flag判断ifdef
    while (infile1.getline(s1, 100)) // run
    {
        if (flag1 == 1)
        {
            flag1 = 0; // 归零
            continue;   //直接跳过
        }
        switch (identify(s1)) // 判断该行的功能
        {
        case 1:
            filename = identify_inc(s1);
            Open_file(filename, &outfile1);
            break;
        case 2:
            V.identify_def(s1);
            break;
        case 3:
            V.identify_if(s1, &flag1);
            break;
        case 4:
            break;
        default:
            V.identify_void(s1, &outfile1);
            break;
        }
    }
    V.vector_clear(); // clear vector
    infile1.close();  // close file1

    int flag2 = 0;                   //flag判断ifdef
    while (infile2.getline(s2, 100)) // run
    {
        if (flag2 == 1)
        {
            flag2 = 0; // 归零
            continue;
        }
        switch (identify(s2)) // 判断该行的功能
        {
        case 1:
            filename = identify_inc(s2);
            Open_file(filename, &outfile2);
            break;
        case 2:
            V.identify_def(s2);
            break;
        case 3:
            V.identify_if(s2, &flag2);
            break;
        case 4:
            break;
        default:
            V.identify_void(s2, &outfile2);
            break;
        }
    }
    V.vector_clear(); // clear vector
    infile2.close();  // close file2
    return 0;   //finish
}


void vec::vector_clear()//clear vector!
{
    vec_a1.clear();
    vec_a2.clear();
    vec_b.clear();
}

void vec::identify_def(char *p) // #define
{
    char *p1 = strstr(p, " ") + 1; // 第一个空格后的开头
    char *p2 = strstr(p1, " ");    // 第二个空格
    if (p2 != NULL)                // define替换
    {
        char *p3 = p2 + 1;           // 第二个空格后的开头
        char p_res1[100] = {0};      // 新建字符数组
        memcpy(p_res1, p1, p2 - p1); // copy the name
        string x1 = string(p_res1); //转化为string
        vec_a1.push_back(x1);               // 向vector里添加元素
        string x2 = p3;                     // 将指针转化为字符串string
        x2 = x2.substr(0, x2.length() - 1); //删掉x2的最后一个字节(最后一个字节是回车)
        vec_a2.push_back(x2);               // 向vector里添加元素
    }
    else // 如果仅仅是define
    {
        string str1 = p1;      // 将指针转化为字符串string
        vec_b.push_back(str1); // 向vector里添加元素
    }
}

void vec::identify_void(char *p, ofstream *out) // 空行的操作
{
    void copy_str(string * s, string early, string now); //声明替换函数
    string p_str = p;//转化为string
    for (int i = 0; i < vec_a1.size(); i++) // 查找是否有define定义
    {
        if (p_str.find(vec_a1[i]) != -1)    //如果有define
        {
            copy_str(&p_str, vec_a1[i], vec_a2[i]);//替换的函数
        }
        if (i == vec_a1.size() - 1)//最后一次循环输出
            *out << p_str;
    }
}

void vec::identify_if(char *p, int *q) // #ifdef & #endif
{
    *q = 1; //先是flag等于1(跳过)
    char *p1 = strstr(p, " ") + 1;//找到ifdef后面的字符串
    string str = p1;//转换为string
    for (int i = 0; i < vec_b.size(); i++) // 查找是否有define定义
    {
        if (vec_b[i] == str)//如果有相同则不跳过下一行
        {
            *q = 0;
            break;
        }
    }
}

void copy_str(string *s, string early, string now) // 查找并替换字符串
{
    int pos = (*s).find(early); // 查找指定的串

    while (pos != -1)
    {
        (*s).replace(pos, early.length(), now); // 用新的串替换掉指定的串
        pos = (*s).find(early);                 // 继续查找指定的串，直到所有的都找到为止
    }
}

int identify(char *p) // 识别这一行的关键字
{
    if (strstr(p, "#include"))
        return 1;
    if (strstr(p, "#define"))
        return 2;
    if (strstr(p, "#ifdef"))
        return 3;
    if (strstr(p, "#endif"))
        return 4;
    return 0;
}

void Open_file(string p, ofstream *out) // 打开文件// 打印内容 //关闭文件
{
    ifstream openfile(p, ios::in | ios::binary);
    if (!openfile) // 打开失败
    {
        cout << "error opening source file." << endl;
        return;
    }
    else
    {
        char x[100];
        while (openfile.getline(x, 100))
        {
            *out << x << endl;
        }
        openfile.close();
    }
}

string identify_inc(char *p) // #include
{
    char *p_begin = strstr(p, "\"") + strlen("\""); // find the filename
    char *p_end = strstr(p_begin, "\"");
    char p_res[100] = {0};
    memcpy(p_res, p_begin, p_end - p_begin); // copy the filename
    string x = string(p_res);   //转换为string
    return x;
}

//把打开文件&switch的步骤封装起来?(failed)