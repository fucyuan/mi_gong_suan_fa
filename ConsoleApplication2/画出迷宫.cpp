#include"�����Թ�.h"
void generatemaze(int width, int height, std::vector<std::vector<char>>& maze)//���ɵ�ͼ�Ĵ���
{
    // ��ʼ���Թ���ȫ������Ϊǽ��
    maze.assign(height, std::vector<char>(width, '#'));
    /*
    ���д������ڳ�ʼ���Թ��Ķ�ά�ַ����� maze��
    ��ʹ�� assign ������ maze ����Ϊ����ָ���߶ȺͿ�ȵĶ�ά����������ÿ��Ԫ�س�ʼ��Ϊ�ַ� '#'����ʾǽ�ڡ�

    assign ������������������Ҫ�����Ԫ��������Ҫ�����Ԫ��ֵ��
    height ���Թ��ĸ߶ȣ�ָ�������� maze ���ڲ����������������Թ���������
    std::vector<char>(width, '#') ����һ������ width ��Ԫ�أ�����ÿ��Ԫ�ض����ַ� '#' ����������ʾ�Թ���һ�С�
    assign ��������Щ����������� maze��������Թ��ĳ�ʼ����
    maze ��Ϊһ������ height �к� width �еĶ�ά�ַ����������е�Ԫ�ض�����ʼ��Ϊ '#'����ʾ�Թ���ǽ�ڡ�
    */

    std::random_device rd;/*
    �ڸ����Ĵ����У�std::random_device rd; ������һ����Ϊ rd �� std::random_device ����
    ͨ��ʵ��������������ǿ���ʹ������������������ӣ��Ա��ں�����������������ṩ����������ԡ�*/
    std::mt19937 rng(rd());
    /*
    �ڸ����Ĵ����У�rd() ���� std::random_device ���� rd �ĺ����������������������һ����������ӡ�
    Ȼ�󣬸����ӱ����ݸ� std::mt19937 ���캯�����Գ�ʼ�� rng����α�������������*/
    std::uniform_int_distribution<int> randomwidth(1, (width - 1) / 2);
    /*
    ������һ����Ϊ randomwidth �� std::uniform_int_distribution<int> ����
    ��������ָ����Χ�ڵľ��ȷֲ��������������*/
    std::uniform_int_distribution<int> randomheight(1, (height - 1) / 2);
    std::uniform_int_distribution<int> randomstartwidth(1, (width - 1) / 2);
    std::uniform_int_distribution<int> randomstartheight(1, (height - 1) / 2);
    std::uniform_int_distribution<int> randomendwidth(1, (width - 1) / 2);
    std::uniform_int_distribution<int> randomendheight(1, (height - 1) / 2);

    // ���ѡ��һ����ʼ��
    int startx = randomstartwidth(rng) * 2 - 1;
    int starty = randomstartheight(rng) * 2 - 1;
    maze[starty][startx] = ' ';

    std::vector<std::pair<int, int>> // std::pair�����ǿ��Է���ؽ�������ص�ֵ���������Ƿ���ƫ�����������һ����Ԫ
        directions
        =
    {
        {2, 0},
        {-2, 0},
        {0, 2},
        {0, -2}
    };
    /*
    �����ƶ�������λ��ˮƽ����ƫ��Ϊ 2����ֱ����ƫ��Ϊ 0��
        �����ƶ�������λ��ˮƽ����ƫ��Ϊ - 2����ֱ����ƫ��Ϊ 0��
        �����ƶ�������λ��ˮƽ����ƫ��Ϊ 0����ֱ����ƫ��Ϊ 2��
        �����ƶ�������λ��ˮƽ����ƫ��Ϊ 0����ֱ����ƫ��Ϊ - 2��
        */
    std::shuffle(directions.begin(), directions.end(), rng);            //rdҲ����
    /*std::shuffle �� directions �����е�Ԫ�ؽ���������򣬴Ӷ��ı���Ԫ�ص����λ�á�
   ���Թ������㷨��ÿһ���У��� directions ������ѡ��һ������ʱ�����ܹ��������˳�������ѡ����
   �������Թ�������Ժͱ仯�ԡ�  */

    std::vector<std::pair<int, int>> stack;
    /*
    ��ջ��һ�ֺ���ȳ���LIFO�������ݽṹ������ѭ���Ƚ��������ԭ��
    ���Թ������㷨�У�stack ���ڴ洢������Ľڵ����ꡣ���㷨��ִ�й����У�
    ������һ���ڵ�󣬽���ѹ���ջ���Ա��Ժ��ٴδ���
    ���㷨�Ӷ�ջ�е���һ���ڵ�ʱ����������һ���д���ýڵ�����ڽڵ�*/
    stack.push_back({ startx, starty });

    while (!stack.empty())//��ջ��Ϊ��
    {
        auto current = stack.back();//stack.back() ���ض�ջ stack �е����һ��Ԫ�أ�����ջ�������ӵĽڵ����ꡣ
        stack.pop_back();//ͨ������ pop_back()�����ǿ������Թ������㷨��ÿһ��ѭ���������Ƴ��Ѵ���Ľڵ����꣬��ȷ���㷨�����ظ�������ͬ�Ľڵ㡣
        int x = current.first;
        int y = current.second;
        /*
        current ��һ�� std::pair<int, int> ���󣬱�ʾ�Թ��е�һ���ڵ����ꡣ
        first ��Ա��ʾ�ڵ���кţ�
        second ��Ա��ʾ�ڵ���кš�
        */

        for (const auto& direction : directions)
            /*
            ���д���ʹ�÷�Χ����ѭ����range - based for loop�������� directions �����е�ÿ��Ԫ�أ�
            ����ÿ��Ԫ�ظ�ֵ�� direction ������*/
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

    // ���Թ������ܱ߽�����Ϊǽ��
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

    // ��������յ�
    int startrow, startcol, endrow, endcol;
    do {
        startrow = randomstartheight(rng) * 2 - 1;
        startcol = randomstartwidth(rng) * 2 - 1;
        endrow = randomendheight(rng) * 2 - 1;
        endcol = randomendwidth(rng) * 2 - 1;
    } while (startrow == endrow && startcol == endcol);

    maze[startrow][startcol] = 'S'; // �����Ϊ 'S'
    maze[endrow][endcol] = 'E'; // �յ���Ϊ 'E'
}
