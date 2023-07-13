#include"打印地图.h"
const std::string red_color_code = "\033[1;31m";
// ansi转义序列：重置文本样式
const std::string reset_color_code = "\033[0m";
void printmaze(const std::vector<std::vector<char>>& maze)//打印地图
{
    // ANSI转义序列：绿色文本
    const std::string green_color_code = "\033[1;32m";
    const std::string wall_symbol = "\u25A0";
    for (const auto& row : maze)
        /*
        maze 是一个二维字符向量，表示迷宫的布局。每个元素都是一个字符，表示迷宫中的一个单元格。
        通过使用范围基于循环，for (const auto& row : maze) 遍历了 maze 中的每一行，
        并将每一行的元素赋值给名为 row 的变量。
         row 是一个自动推断类型的常量引用，用于在循环的每次迭代中表示当前遍历到的行。
        */
    {
        for (char cell : row)
        {
            if (cell == 'S')
            {
                std::cout << red_color_code << cell << reset_color_code;
            }
            else if (cell == 'E') {
                std::cout << red_color_code << cell << reset_color_code;
            }
            else if (cell == '*') {
                std::cout << green_color_code << cell << reset_color_code;
            }
            else
            {
                std::cout << cell;
            }
        }
        std::cout << std::endl;
    }
}

