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
// ansi转义序列：红色文本
const std::string red_color_code = "\033[1;31m";
// ansi转义序列：重置文本样式
const std::string reset_color_code = "\033[0m";

struct Node {
    int row;
    int col;
    int g;
    int h;
    int f;
};

void generatemaze(int width, int height, std::vector<std::vector<char>>& maze)
{
    // 初始化迷宫，全部设置为墙壁
    maze.assign(height, std::vector<char>(width, '#'));

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> randomwidth(1, (width - 1) / 2);
    std::uniform_int_distribution<int> randomheight(1, (height - 1) / 2);
    std::uniform_int_distribution<int> randomstartwidth(1, (width - 1) / 2);
    std::uniform_int_distribution<int> randomstartheight(1, (height - 1) / 2);
    std::uniform_int_distribution<int> randomendwidth(1, (width - 1) / 2);
    std::uniform_int_distribution<int> randomendheight(1, (height - 1) / 2);

    // 随机选择一个起始点
    int startx = randomstartwidth(rng) * 2 - 1;
    int starty = randomstartheight(rng) * 2 - 1;
    maze[starty][startx] = ' ';

    std::vector<std::pair<int, int>> directions = { {2, 0}, {-2, 0}, {0, 2}, {0, -2} };
    std::shuffle(directions.begin(), directions.end(), rng);

    std::vector<std::pair<int, int>> stack;
    stack.push_back({ startx, starty });

    while (!stack.empty())
    {
        auto current = stack.back();
        stack.pop_back();
        int x = current.first;
        int y = current.second;

        for (const auto& direction : directions)
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
        maze[0][i] = '#';
        maze[height - 1][i] = '#';
    }
    for (int i = 0; i < height; i++)
    {
        maze[i][0] = '#';
        maze[i][width - 1] = '#';
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

int manhattanDistance(int row1, int col1, int row2, int col2)
{
    return std::abs(row1 - row2) + std::abs(col1 - col2);
}


void printmaze(const std::vector<std::vector<char>>& maze)
{
    // ANSI转义序列：绿色文本
    const std::string green_color_code = "\033[1;32m";
    const std::string wall_symbol = "\u25A0";
    for (const auto& row : maze)
    {
        for (char cell : row)
        {
            if (cell == 'S') {
                std::cout << red_color_code << cell << reset_color_code;
            }
            else if (cell == 'E') {
                std::cout << red_color_code << cell << reset_color_code;
            }
            else if (cell == '*') {
                std::cout << green_color_code << cell << reset_color_code;
            }
            else {
                std::cout << cell;
            }
        }
        std::cout << std::endl;
    }
}


bool isValidCell(int row, int col, const std::vector<std::vector<char>>& maze)
{
    int height = maze.size();
    int width = maze[0].size();

    return (row >= 0 && row < height && col >= 0 && col < width && maze[row][col] != '#');
}

std::vector<std::pair<int, int>> getNeighbors(int row, int col, const std::vector<std::vector<char>>& maze)
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

std::vector<std::pair<int, int>> astar(const std::vector<std::vector<char>>& maze)
{
    int height = maze.size();
    int width = maze[0].size();

    std::vector<std::vector<Node>> grid(height, std::vector<Node>(width));
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

    // Initialize the grid
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            grid[row][col] = { row, col, INT_MAX, 0, INT_MAX };
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
    int width = 20; // 迷宫的宽度
    int height = 20; // 迷宫的高度

    std::vector<std::vector<char>> maze;
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
