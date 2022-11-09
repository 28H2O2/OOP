添加了Coord抽象类并且用多态的方法派生出Coord_mono与Coord_gray类去实现
Canvas类组合Coord类
View类继承Canvas类
设置point类将color方法放在point里面 并且Canvas类组合point类

处理坐标系的时候使用以下代码
    const int y_pos = (flag_coord == world_coord ? height - y : y); //两种坐标系

使用多态与三目运算符避免if else 或者switch case