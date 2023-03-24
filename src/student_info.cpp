#include "Student_info.h"
#include "grade.h"
#include <algorithm>
bool compare(const Student_info &x, const Student_info &y)
{
    return x.name < y.name;
}

std::istream &read(std::istream &is, Student_info &s)
{
    std::cout << "Please enter name midterm final:\n";
    is >> s.name >> s.midterm >> s.final;

    read_hw(is, s.homeworks);
    return is;
}

std::istream &read_hw(std::istream &in, std::vector<double> &hw)
{
    if (in)
    {
        // 清除原先的内容
        hw.clear();

        // 读取家庭作业成绩
        double x;
        std::cout << "Please enter homework:\n";
        while (in >> x)
            hw.push_back(x);

        // 清除流以使输入下一个学生成绩
        in.clear();
    }

    return in;
}

std::vector<Student_info> extra_fails(std::vector<Student_info> &students)
{
    /* std::vector<Student_info>::iterator iter = students.begin();
    std::vector<Student_info> fails;
    while (iter != students.end())
    {
        if (fgrade(*iter))
        {
            fails.push_back(*iter);
            iter = students.erase(iter); // 删除不及格学生
        }
        else
        {
            ++iter;
        }
    } */

    /* std::vector<Student_info> fails;
    // remove_copy_if “remove”(剔除)符合pgrade条件元素，只copy不符合元素
    std::remove_copy_if(students.begin(), students.end(), std::back_inserter(fails), pgrade);
    // remove_if 移除符合条件的元素，后续符合的元素移动替换移除元素位置空间
    students.erase(std::remove_if(students.begin(), students.end(), fgrade), students.end()); */

    //stable_partition 对容器分组，第一组为符合条件，第二组为不符合条件，返回的迭代器指向第二组头元素
    std::vector<Student_info>::iterator iter = std::stable_partition(students.begin(), students.end(), pgrade);
    std::vector<Student_info> fails(iter, students.end());
    students.erase(iter, students.end());
    return fails;
}