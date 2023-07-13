#include"��ӡ��ͼ.h"
const std::string red_color_code = "\033[1;31m";
// ansiת�����У������ı���ʽ
const std::string reset_color_code = "\033[0m";
void printmaze(const std::vector<std::vector<char>>& maze)//��ӡ��ͼ
{
    // ANSIת�����У���ɫ�ı�
    const std::string green_color_code = "\033[1;32m";
    const std::string wall_symbol = "\u25A0";
    for (const auto& row : maze)
        /*
        maze ��һ����ά�ַ���������ʾ�Թ��Ĳ��֡�ÿ��Ԫ�ض���һ���ַ�����ʾ�Թ��е�һ����Ԫ��
        ͨ��ʹ�÷�Χ����ѭ����for (const auto& row : maze) ������ maze �е�ÿһ�У�
        ����ÿһ�е�Ԫ�ظ�ֵ����Ϊ row �ı�����
         row ��һ���Զ��ƶ����͵ĳ������ã�������ѭ����ÿ�ε����б�ʾ��ǰ���������С�
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

