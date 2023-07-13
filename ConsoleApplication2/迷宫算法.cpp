//#include <iostream>
//#include <vector>
//#include <random>
//#include <algorithm>
//
//// ansi转义序列：红色文本
//const std::string red_color_code = "\033[1;31m";
//// ansi转义序列：重置文本样式
//const std::string reset_color_code = "\033[0m";
//
//void generatemaze(int width, int height, std::vector<std::vector<char>>& maze)
//{
//    // 初始化迷宫，全部设置为墙壁
//    maze.assign(height, std::vector<char>(width, '#'));
//
//    std::random_device rd;
//    std::mt19937 rng(rd());
//    std::uniform_int_distribution<int> randomwidth(1, (width - 1) / 2);
//    std::uniform_int_distribution<int> randomheight(1, (height - 1) / 2);
//
//    // 随机选择一个起始点
//    int startx = randomwidth(rng) * 2 - 1;
//    int starty = randomheight(rng) * 2 - 1;
//    maze[starty][startx] = ' ';
//
//    std::vector<std::pair<int, int>> directions = { {2, 0}, {-2, 0}, {0, 2}, {0, -2} };
//    std::shuffle(directions.begin(), directions.end(), rng);
//
//    std::vector<std::pair<int, int>> stack;
//    stack.push_back({ startx, starty });
//
//    while (!stack.empty())
//    {
//        auto current = stack.back();
//        stack.pop_back();
//        int x = current.first;
//        int y = current.second;
//
//        for (const auto& direction : directions)
//        {
//            int nx = x + direction.first;
//            int ny = y + direction.second;
//
//            if (nx >= 0 && nx < width && ny >= 0 && ny < height && maze[ny][nx] == '#')
//            {
//                maze[ny][nx] = ' ';
//                maze[y + direction.second / 2][x + direction.first / 2] = ' ';
//                stack.push_back({ nx, ny });
//            }
//        }
//
//        std::shuffle(directions.begin(), directions.end(), rng);
//    }
//
//    // 将迷宫的四周边界设置为墙壁
//    for (int i = 0; i < width; i++)
//    {
//        maze[0][i] = '#';
//        maze[height - 1][i] = '#';
//    }
//    for (int i = 0; i < height; i++)
//    {
//        maze[i][0] = '#';
//        maze[i][width - 1] = '#';
//    }
//
//    // 标记起点和终点
//    int startrow = starty;
//    int startcol = startx;
//    int endrow, endcol;
//    do {
//        endrow = randomheight(rng) * 2 - 1;
//        endcol = randomwidth(rng) * 2 - 1;
//    } while (endrow == startrow && endcol == startcol);
//
//    maze[startrow][startcol] = 'S'; // 起点标记为 's'
//    maze[endrow][endcol] = 'E'; // 终点标记为 'e'
//}
//
//void printmaze(const std::vector<std::vector<char>>& maze)
//{
//    for (const auto& row : maze)
//    {
//        for (char cell : row)
//        {
//            if (cell == 'S') {
//                std::cout << red_color_code << cell << reset_color_code;
//            }
//            else if (cell == 'E') {
//                std::cout << red_color_code << cell << reset_color_code;
//            }
//            else {
//                std::cout << cell;
//            }
//        }
//        std::cout << std::endl;
//    }
//}
//
//int main()
//{
//    int width = 20; // 迷宫的宽度
//    int height = 20; // 迷宫的高度
//
//    std::vector<std::vector<char>> maze;
//    generatemaze(width, height, maze);
//    printmaze(maze);
//
//    return 0;
//}
//
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include<string>
#include"画出迷宫.h"
#include"曼哈顿距离.h"
#include"打印地图.h"

struct Node 
{
    int row;
    int col;
    int g;
    int h;
    int f;
};
/*
row: 表示节点在迷宫中的行数。
col: 表示节点在迷宫中的列数。
g: 表示从起点到当前节点的实际路径长度（g值）。
h: 表示当前节点到终点的估计路径长度（h值），通常使用启发式函数（如曼哈顿距离）计算。
f: 表示节点的综合评估值（f值），通常是g值和h值的和，用于指导搜索算法选择下一步要探索的节点。
在A搜索算法中，
g值表示已经走过的路径长度，
h值表示预计剩余路径长度，
f值是g值和h值的综合评估，
用于选择下一个要探索的节点。
通过不断更新和比较这些值，A算法可以找到从起点到终点的最短路径。
*/
bool isValidCell(int row, int col, const std::vector<std::vector<char>>& maze)
{
    int height = maze.size();
    int width = maze[0].size();

    return (row >= 0 && row < height && col >= 0 && col < width && maze[row][col] != '#' && maze[row][col] != '$');
}
std::vector<std::pair<int, int>> 
getNeighbors(int row, int col, const std::vector<std::vector<char>>& maze)
    /*

    getNeighbors 的函数，用于获取给定坐标 (row, col) 在迷宫中的所有相邻节点。
    该函数接受三个参数：row，col 和 maze。row 和 col 表示要获取相邻节点的坐标，
    而 maze 是一个二维字符向量，表示迷宫的布局。
    函数的返回类型是 std::vector<std::pair<int, int>>，表示一个存储节点坐标的向量，
    每个节点坐标由两个整数表示。
    */
{
    std::vector<std::pair<int, int>> neighbors;
    std::vector<std::pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    for (const auto& direction : directions)
    {
        int newRow = row + direction.first;
        int newCol = col + direction.second;

        if (isValidCell(newRow, newCol, maze))
        {
            neighbors.push_back({ newRow, newCol });
        }
    }

    return neighbors;
}
std::vector<std::pair<int, int>> 
astar(const std::vector<std::vector<char>>& maze)
{
    int height = maze.size();
    int width = maze[0].size();

    std::vector<std::vector<Node>> grid(height, std::vector<Node>(width));
    /*
    grid 是一个二维向量，
    类型为 std::vector<std::vector<Node>>。
    它有 height 行和 width 列，并且每个元素都是一个 Node 对象。
    */
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    /*
    
    这行代码创建了一个名为 visited 的二维布尔向量，用于跟踪节点是否已被访问。
    visited 是一个二维向量，类型为 std::vector<std::vector<bool>>。
    它有 height 行和 width 列，并且每个元素都是一个布尔值。
     visited，可以以二维形式跟踪迷宫中的每个节点是否已被访问。
     每个节点在 visited 中的位置对应于迷宫中的行号和列号。通过访问 visited 的元素，
     可以获取节点是否已被访问的信息，以及对其进行修改和更新。
    通过提供 height 和 width，我们创建了一个具有指定行列数的二维布尔向量，并将所有元素初始化为 false。
    
    */

    // Initialize the grid
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            grid[row][col] = { row, col, INT_MAX, 0, INT_MAX };
            /*
            row 和 col 属性分别被设置为指定的行号 row 和列号 col。
             g 属性被设置为 INT_MAX，表示初始状态下节点的 g 值为无穷大。
            h 属性被设置为 0，表示初始状态下节点的 h 值为 0。
            f 属性被设置为 INT_MAX，表示初始状态下节点的 f 值为无穷大。
            */
        }
    }

    int startRow, startCol, endRow, endCol;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            if (maze[row][col] == 'S')
            {
                startRow = row;
                startCol = col;
            }
            else if (maze[row][col] == 'E')
            {
                endRow = row;
                endCol = col;
            }
        }
    }

    grid[startRow][startCol].g = 0;
    grid[startRow][startCol].h = manhattanDistance(startRow, startCol, endRow, endCol);
    grid[startRow][startCol].f = grid[startRow][startCol].g + grid[startRow][startCol].h;

    std::vector<std::pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    while (true)
    {
        // Find the node with the lowest f score
        int minF = INT_MAX;
        std::pair<int, int> current;

        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                if (!visited[row][col] && grid[row][col].f < minF)
                {
                    minF = grid[row][col].f;
                    current = { row, col };
                }
            }
        }

        if (current == std::make_pair(endRow, endCol))
        {
            break; // Reached the end point
        }

        visited[current.first][current.second] = true;

        // Explore the neighbors
        for (const auto& direction : directions)
        {
            int newRow = current.first + direction.first;
            int newCol = current.second + direction.second;

            if (isValidCell(newRow, newCol, maze) && !visited[newRow][newCol])
            {
                int newG = grid[current.first][current.second].g + 1;
                int newH = manhattanDistance(newRow, newCol, endRow, endCol);
                int newF = newG + newH;

                if (newF < grid[newRow][newCol].f)
                {
                    grid[newRow][newCol].g = newG;
                    grid[newRow][newCol].h = newH;
                    grid[newRow][newCol].f = newF;
                    grid[newRow][newCol].row = current.first;
                    grid[newRow][newCol].col = current.second;
                }
            }
        }
    }

    // Reconstruct the path
    std::vector<std::pair<int, int>> path;
    std::pair<int, int> current = { endRow, endCol };

    while (current != std::make_pair(startRow, startCol))
    {
        path.push_back(current);
        int row = current.first;
        int col = current.second;
        current = { grid[row][col].row, grid[row][col].col };
    }

    path.push_back({ startRow, startCol });
    std::reverse(path.begin(), path.end());
    return path;
}

int main()
{
    int width = 50; // 迷宫的宽度
    int height = 30; // 迷宫的高度

    std::vector<std::vector<char>> maze;
    /*
    这行代码声明了一个名为 maze 的二维字符向量。
    std::vector<std::vector<char>> 表示一个向量，
    其中每个元素都是一个向量，而每个内部向量中的元素都是字符类型
    */
    generatemaze(width, height, maze);
    printmaze(maze);

    std::vector<std::pair<int, int>> path = astar(maze);

    std::cout << "路径：" << std::endl;
    for (const auto& point : path)
    {
        maze[point.first][point.second] = '*';
    }

    printmaze(maze);

    return 0;
}
