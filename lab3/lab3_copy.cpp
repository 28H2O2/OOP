#include<iostream>
#include<fstream>
#include<cstring>
#include<vector>
using namespace std;

class vec   
{           //需要用到vector的一个类
    private:    
        vector<string>vec_a1;   //define vector1
        vector<string>vec_a2;   //define vector2
        vector<string>vec_b;    //define vector3
    public:
        void identify_def(char* p);
        void identify_void(char* p, ofstream* out);
        void identify_if(char* p, int* q);
};


int main()          // main function
{
    vec V;      //类初始化
    int identify(char* p);
    void Open_file(string p, ofstream* out);
    string identify_inc(char* p);
    string filename;
    char s[100];        //用于读入文件中每行文字
    ifstream infile("testcase1.txt", ios::in|ios::binary); // 用二进制方法打开文件
    if(!infile){ // 打开失败
        cout<< "error opening source file."<<endl;
        return 0;
    }
    ofstream outfile;       //  输出txt文件
    outfile.open("out.txt");
    int flag1 = 0;//判断ifdef
    while(infile.getline(s, 100))
    {
        if (flag1 == 1)
        {
            flag1 = 0;  // 归零
            continue;
        }
        int flag = identify(s);// 判断该行的功能
        control(s, identify_inc(s), )
        switch (flag)
        {
        case 1:
            filename = identify_inc(s);
            Open_file(filename, &outfile);
            break;
        case 2:
            V.identify_def(s);
            break;
        case 3:
            V.identify_if(s, &flag1);
            break;
        case 4:
            break;
        default:
            V.identify_void(s, &outfile);
            break;
        }
    }

    infile.close();
    return 0;
}

void vec::identify_def(char* p)      // #define
{
    char* p1 = strstr(p, " ")+1;// 第一个空格后的开头
    char* p2 = strstr(p1, " ");// 第二个空格
    if(p2 != NULL)     // define替换
    {
        char* p3 = p2 + 1;  // 第二个空格后的开头
        char p_res1[100]={0};// 新建字符数组
        memcpy(p_res1, p1, p2-p1);  // copy the name 
        string x1 = string(p_res1);
        vec_a1.push_back(x1);       // 向vector里添加元素
        string x2 = p3;           // 将指针转化为字符串string       
	    x2 = x2.substr(0, x2.length() - 1); //删掉x2的最后一个字节
        vec_a2.push_back(x2);       // 向vector里添加元素  
        string test = "xyzw";     
    }
    else        // 如果仅仅是define
    {
        string str1 = p1;   // 将指针转化为字符串string
        vec_b.push_back(str1);// 向vector里添加元素
    }

}

void vec::identify_void(char* p, ofstream* out)     // 空行的操作
{
    void copy_str(string s, string early, string now, ofstream* out);//声明替换函数
    string p_str = p;
    for(int i=0;i<vec_a1.size();i++) // 查找是否有define定义
    {
        if(p_str.find(vec_a1[i])!=-1)
        {
            copy_str(p_str, vec_a1[i], vec_a2[i], out);
            break;
        }
        if(i == vec_a1.size()-1)
             *out<<p;
    }
}


void vec::identify_if(char* p, int* q)// #ifdef & #endif
{
    *q = 1;//先是flag等于1(跳过)
    char* p1 = strstr(p, " ")+1;
    string str = p1;
    for(int i=0;i<vec_b.size();i++) // 查找是否有define定义
    {
        if(vec_b[i] == str)
        {
            *q = 0;
            break;
        }
    }
}
void copy_str(string s, string early, string now, ofstream* out)    // 查找并替换字符串
{
    int pos = s.find(early);// 查找指定的串

    while (pos != -1)
    {
        s.replace(pos,early.length(),now);// 用新的串替换掉指定的串
        pos = s.find(early);// 继续查找指定的串，直到所有的都找到为止
    }
    *out<<s;
}

int identify(char* p)   // 识别这一行的关键字 
{
    if(strstr(p, "#include"))
        return 1;
    if(strstr(p, "#define"))
        return 2;
    if(strstr(p, "#ifdef"))
        return 3;
    if(strstr(p, "#endif"))
        return 4;
    return 0;
}

void Open_file(string p, ofstream* out)        // 打开文件// 打印内容 //关闭文件
{
    ifstream openfile(p, ios::in|ios::binary);
    if(!openfile)   // 打开失败
    { 
        cout<< "error opening source file."<<endl;
    }
    else
    {
        char x[100];
        while(openfile.getline(x, 100))
        {
            *out<<x;
        }
        openfile.close();
    }
}

string identify_inc(char* p)  // #include 
{
    char *p_begin = strstr(p, "\"")+strlen("\"");  // find the filename
    char *p_end = strstr(p_begin, "\"");
    char p_res[100]={0};
    memcpy(p_res, p_begin, p_end-p_begin);  // copy the filename  
    string x = string(p_res);
    return x;

}

void control(char* p, string name, )
{
    if(strstr(p, "#include"))
        Open_file(name, &outfile);
    if(strstr(p, "#define"))
        V.identify_def(s);
    if(strstr(p, "#ifdef"))
        V.identify_if(s, &flag1);
    if(strstr(p, "#endif"))
        return ;
    V.identify_void(s, &outfile);
}
    
    //把打开文件&switch的步骤封装起来~~