/*
 * @Author: H2O2 
 * @Date: 2022-04-09 19:31:25 
 * @Last Modified by: H2O2
 * @Last Modified time: 2022-04-09 20:09:36
 */
#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

class Bit
{
public:
    vector<vector<unsigned char> > dot_canvas;
    int height, width, true_width;
    void bit_change(const int, const int);
    void line_bit(int x0, int y0, int x1, int y1);
    void print_bit();
};


int main()
{
    Bit X;
    X.height = 50;
    X.true_width = 50;
    X.width = X.true_width/8+1;
    X.dot_canvas.resize(X.height);
    for(int i = 0; i < X.height; i++)
        X.dot_canvas[i].resize(X.width);

    X.line_bit(4, 6, 22, 16);
    X.print_bit();
}

void Bit::line_bit(int x0, int y0, int x1, int y1)
{
    const int dx = x1 - x0;//x偏移量
	const int dy = y1 - y0;//y偏移量
	const int ux = dx >0 ? 1 : -1;//x伸展方向
	const int uy = dy >0 ? 1 : -1;//y伸展方向
	const int dx2 = abs(dx * 2);//x偏移量乘2  （目的是出现整数）
	const int dy2 = abs(dy * 2);//y偏移量乘2
    if (abs(dx) > abs(dy))    //以x为增量方向计算
    {
        int e = -dx;         // e = -0.5 * 2 * dx,定义初始值 （原来的e是-0.5）
        int x = x0;          //起点x坐标
        int y = y0;          //起点y坐标
        while (x != x1 + ux) //在x到达终点后结束循环
        {
            
            bit_change(x, y);
            // FIXME    // dot_canvas[height+1-y][x] = 1;
            e = e + dy2; //（原来是 e = e + k）
            if (e > 0)   // e大于0时表示要取右上的点（否则是右下的点）
            {
                if (y != y1) //如果未到终点则继续增加
                {
                    y += uy;
                }
                e = e - dx2; // (原来是 e = e -1)
            }
            x += ux; //继续移动
        }
    }
}

void Bit::bit_change(const int x, const int y)       //两种存储方式的转化
{
    const int x_pos = (x - 1) / 8;                  // canvas中的真实位置
    const int y_pos = height - y;                   // canvas中的真实位置
    const int right = (x - 1) % 8;                  // 右移的位数
    const int left = 8 - right;                     // 左移的位数
    dot_canvas[y_pos][x_pos] = 
        dot_canvas[y_pos][x_pos] | (unsigned char)pow(2, left-1);

}





void Bit::print_bit()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width - 1; j++)
        {
            for (int k = 7; k >= 0; k--)
            {
                if (((unsigned char)pow(2, k) & dot_canvas[i][j]) == 0) // 输出
                    cout << "o";
                else
                    cout << ".";
            }
        }
        for (int k = 7; k >= width * 8 - true_width; k--)
        {
            if (((unsigned char)pow(2, k) & dot_canvas[i][width - 1]) == 0) // 输出
                cout << "o";
            else
                cout << ".";
        }
        cout << endl;
    }
}



