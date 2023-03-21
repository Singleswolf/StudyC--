#include "Student_info.h"
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
        //清除原先的内容
        hw.clear();

        //读取家庭作业成绩
        double x;
        std::cout << "Please enter homework:\n";
        while (in >> x)
            hw.push_back(x);
            
        //清除流以使输入下一个学生成绩
        in.clear();
    }
    
    return in;
}
