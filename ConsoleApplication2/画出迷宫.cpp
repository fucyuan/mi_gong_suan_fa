#include"画出迷宫.h"
void generatemaze(int width, int height, std::vector<std::vector<char>>& maze)//生成地图的代码
{
    // 初始化迷宫，全部设置为墙壁
    maze.assign(height, std::vector<char>(width, '#'));
    /*
    这行代码用于初始化迷宫的二维字符向量 maze。
    它使用 assign 函数将 maze 设置为具有指定高度和宽度的二维向量，并将每个元素初始化为字符 '#'，表示墙壁。

    assign 函数接受两个参数：要分配的元素数量和要分配的元素值。
    height 是迷宫的高度，指定了向量 maze 中内部向量的数量，即迷宫的行数。
    std::vector<char>(width, '#') 创建一个具有 width 个元素，并且每个元素都是字符 '#' 的向量，表示迷宫的一行。
    assign 函数将这些行向量分配给 maze，完成了迷宫的初始化。
    maze 成为一个具有 height 行和 width 列的二维字符向量，所有的元素都被初始化为 '#'，表示迷宫的墙壁。
    */

    std::random_device rd;/*
    在给定的代码中，std::random_device rd; 创建了一个名为 rd 的 std::random_device 对象。
    通过实例化这个对象，我们可以使用它来生成随机数种子，以便在后续的随机数生成中提供真正的随机性。*/
    std::mt19937 rng(rd());
    /*
    在给定的代码中，rd() 调用 std::random_device 对象 rd 的函数调用运算符，用于生成一个随机数种子。
    然后，该种子被传递给 std::mt19937 构造函数，以初始化 rng，即伪随机数生成器。*/
    std::uniform_int_distribution<int> randomwidth(1, (width - 1) / 2);
    /*
    创建了一个名为 randomwidth 的 std::uniform_int_distribution<int> 对象，
    用于生成指定范围内的均匀分布的整数随机数。*/
    std::uniform_int_distribution<int> randomheight(1, (height - 1) / 2);
    std::uniform_int_distribution<int> randomstartwidth(1, (width - 1) / 2);
    std::uniform_int_distribution<int> randomstartheight(1, (height - 1) / 2);
    std::uniform_int_distribution<int> randomendwidth(1, (width - 1) / 2);
    std::uniform_int_distribution<int> randomendheight(1, (height - 1) / 2);

    // 随机选择一个起始点
    int startx = randomstartwidth(rng) * 2 - 1;
    int starty = randomstartheight(rng) * 2 - 1;
    maze[starty][startx] = ' ';

    std::vector<std::pair<int, int>> // std::pair，我们可以方便地将两个相关的值（在这里是方向偏移量）打包成一个单元
        directions
        =
    {
        {2, 0},
        {-2, 0},
        {0, 2},
        {0, -2}
    };
    /*
    向右移动两个单位，水平方向偏移为 2，垂直方向偏移为 0。
        向左移动两个单位，水平方向偏移为 - 2，垂直方向偏移为 0。
        向下移动两个单位，水平方向偏移为 0，垂直方向偏移为 2。
        向上移动两个单位，水平方向偏移为 0，垂直方向偏移为 - 2。
        */
    std::shuffle(directions.begin(), directions.end(), rng);            //rd也可以
    /*std::shuffle 将 directions 向量中的元素进行随机排序，从而改变了元素的相对位置。
   在迷宫生成算法的每一步中，从 directions 向量中选择一个方向时，就能够以随机的顺序遍历并选择方向，
   增加了迷宫的随机性和变化性。  */

    std::vector<std::pair<int, int>> stack;
    /*
    堆栈是一种后进先出（LIFO）的数据结构，它遵循“先进后出”的原则。
    在迷宫生成算法中，stack 用于存储待处理的节点坐标。在算法的执行过程中，
    当访问一个节点后，将其压入堆栈，以便稍后再次处理。
    当算法从堆栈中弹出一个节点时，它将在下一步中处理该节点的相邻节点*/
    stack.push_back({ startx, starty });

    while (!stack.empty())//堆栈不为空
    {
        auto current = stack.back();//stack.back() 返回堆栈 stack 中的最后一个元素，即堆栈中最近添加的节点坐标。
        stack.pop_back();//通过调用 pop_back()，我们可以在迷宫生成算法的每一次循环迭代中移除已处理的节点坐标，以确保算法不会重复处理相同的节点。
        int x = current.first;
        int y = current.second;
        /*
        current 是一个 std::pair<int, int> 对象，表示迷宫中的一个节点坐标。
        first 成员表示节点的行号，
        second 成员表示节点的列号。
        */

        for (const auto& direction : directions)
            /*
            这行代码使用范围基于循环（range - based for loop）遍历了 directions 向量中的每个元素，
            并将每个元素赋值给 direction 变量。*/
        {
            int nx = x + direction.first;
            int ny = y + direction.second;

            if (nx >= 0 && nx < width && ny >= 0 && ny < height && maze[ny][nx] == '#')
            {
                maze[ny][nx] = ' ';
                maze[y + direction.second / 2][x + direction.first / 2] = ' ';
                stack.push_back({ nx, ny });
            }
        }

        std::shuffle(directions.begin(), directions.end(), rng);
    }

    // 将迷宫的四周边界设置为墙壁
    for (int i = 0; i < width; i++)
    {
        maze[0][i] = '$';
        maze[height - 1][i] = '$';
    }
    for (int i = 0; i < height; i++)
    {
        maze[i][0] = '$';
        maze[i][width - 1] = '$';
    }

    // 标记起点和终点
    int startrow, startcol, endrow, endcol;
    do {
        startrow = randomstartheight(rng) * 2 - 1;
        startcol = randomstartwidth(rng) * 2 - 1;
        endrow = randomendheight(rng) * 2 - 1;
        endcol = randomendwidth(rng) * 2 - 1;
    } while (startrow == endrow && startcol == endcol);

    maze[startrow][startcol] = 'S'; // 起点标记为 'S'
    maze[endrow][endcol] = 'E'; // 终点标记为 'E'
}
