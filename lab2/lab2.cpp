#include<iostream>
#include<math.h>
using namespace std;

class Box   //初始化类
{
    public:
    void line1(int x0, int y0, int x1, int y1);
    void printResult1();
    void line2(int x0, int y0, int x1, int y1);
    void printResult2();
    bool flag;
    // void *w = NULL;
    char (*u)[20];
    bool (*v)[20];
};

void Box::line1(int x0, int y0, int x1, int y1)  //灰度用char类型
{
    int dx = x1 - x0;//x偏移量
	int dy = y1 - y0;//y偏移量
	int ux = dx >0 ? 1 : -1;//x伸展方向
	int uy = dy >0 ? 1 : -1;//y伸展方向
	int dx2 = abs(dx * 2);//x偏移量乘2  （目的是出现整数）
	int dy2 = abs(dy * 2);//y偏移量乘2
	if (abs(dx) > abs(dy))//以x为增量方向计算
	{
		int e = -dx; //e = -0.5 * 2 * dx,定义初始值 （原来的e是-0.5）
		int x = x0;//起点x坐标
		int y = y0;//起点y坐标
		while (x!=x1+ux) //在x到达终点后结束循环
		{
            u[x][y] = 1;
			e = e + dy2;//（原来是 e = e + k）
			if (e > 0)//e大于0时表示要取右上的点（否则是右下的点） 
			{
				if (y!=y1)//如果未到终点则继续增加
				{
					y += uy;
				}
				e = e - dx2;// (原来是 e = e -1)
			}
			x += ux; //继续移动
		}
	}
	else
	{//以y为增量方向计算，其余与上面类似
		int e = -dy; 
		int x = x0;
		int y = y0;
		while (y!=y1+uy)
		{
            u[x][y] = 1;
			e = e + dx2;
			if (e > 0)
			{	
				if (x!=x1)
				{
					x += ux; 
				}
				e = e - dy2;
			}
			y += uy;
		}
	}
}

void Box::printResult1()  //灰度输出
{
    int i,j;
    for(i = 0; i < 20; i++){
        for(j = 0; j < 20; j++){
            printf("%d ",(int)u[j][19-i]); // 上下做一次对称，否则会颠倒
            // cout<<a[j][19-i];
			if(j == 19)printf("\n");
        }
    }
    printf("---------------------------------------\n");//分割线方便区分前后
}

void Box::line2(int x0, int y0, int x1, int y1)   //二值图像用bool类型
{
    int dx = x1 - x0;//x偏移量
	int dy = y1 - y0;//y偏移量
	int ux = dx >0 ? 1 : -1;//x伸展方向
	int uy = dy >0 ? 1 : -1;//y伸展方向
	int dx2 = abs(dx * 2);//x偏移量乘2  （目的是出现整数）
	int dy2 = abs(dy * 2);//y偏移量乘2
	if (abs(dx) > abs(dy))//以x为增量方向计算
	{
		int e = -dx; //e = -0.5 * 2 * dx,定义初始值 （原来的e是-0.5）
		int x = x0;//起点x坐标
		int y = y0;//起点y坐标
		while (x!=x1+ux) //在x到达终点后结束循环
		{
            v[x][y] = 1;
			e = e + dy2;//（原来是 e = e + k）
			if (e > 0)//e大于0时表示要取右上的点（否则是右下的点） 
			{
				if (y!=y1)//如果未到终点则继续增加
				{
					y += uy;
				}
				e = e - dx2;// (原来是 e = e -1)
			}
			x += ux; //继续移动
		}
	}
	else
	{//以y为增量方向计算，其余与上面类似
		int e = -dy; 
		int x = x0;
		int y = y0;
		while (y!=y1+uy)
		{
            v[x][y] = 1;
			e = e + dx2;
			if (e > 0)
			{	
				if (x!=x1)
				{
					x += ux; 
				}
				e = e - dy2;
			}
			y += uy;
		}
	}
}

void Box::printResult2()				//二值图像输出
{
    int i,j;
    for(i = 0; i < 20; i++){
        for(j = 0; j < 20; j++){
            printf("%d ",(int)v[j][19-i]); // 上下做一次对称，否则会颠倒
            // cout<<a[j][19-i];
			if(j == 19)printf("\n");
        }
    }
    printf("---------------------------------------\n");//分割线方便区分前后
}
int main(int argc, char const *argv[])
{
    Box DrawLine;
    int x;
    // void* y = NULL;
    cout<<"please input 0(灰度值) or 1(二值图像)"<<endl;
    cin>>x;
    while(x!=0 && x!=1){
        cout<<"Input Error! please try again!"<<endl;    //输入错误判断循环
        cout<<"please input 0(灰度值) or 1(二值图像)"<<endl;
        cin>>x;
    }
    if(x==0)
    {
        char a[20][20] = {0};  //定义char型初始数组
        DrawLine.u = &a[0];
        // DrawLine.w = (char (*)[20])&a[0];
        DrawLine.printResult1();		//以下为测试用例
        DrawLine.line1(2, 0, 2, 19);
        DrawLine.printResult1();
        DrawLine.line1(0, 2, 19, 2);
        DrawLine.printResult1();
        DrawLine.line1(19, 19, 0, 0);
        DrawLine.printResult1();
        DrawLine.line1(0, 3, 8, 19);
        DrawLine.printResult1();
        DrawLine.line1(0, 15, 5, 0);
        DrawLine.printResult1();
    }
    else
    {
        bool a[20][20] = {0};		//定义bool型初始数组
        DrawLine.v = &a[0];
        DrawLine.printResult2();		//以下为测试用例
        DrawLine.line2(2, 0, 2, 19);
        DrawLine.printResult2();
        DrawLine.line2(0, 2, 19, 2);
        DrawLine.printResult2();
        DrawLine.line2(19, 19, 0, 0);
        DrawLine.printResult2();
        DrawLine.line2(0, 3, 8, 19);
        DrawLine.printResult2();
        DrawLine.line2(0, 15, 5, 0);
        DrawLine.printResult2();
    }

    return 0;
}
