#include "grade.h"
#include <stdexcept>
#include <algorithm>

// 最终成绩 期中0.2 期末0.4 家庭作业0.4
double grade(double midterm, double final, double median)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * median;
}
double grade(double midterm, double final, const std::vector<double> &hw)
{
    if (hw.size() == 0)
        throw std::domain_error("student has done no homework");
    return grade(midterm, final, median(hw));
}

double grade(const Student_info &s)
{
    return grade(s.midterm, s.final, s.homeworks);
}

double median(std::vector<double> vec)
{
    typedef std::vector<double>::size_type vec_sz;

    if (vec.size() == 0)
        throw std::domain_error("median of a empty vector");

    std::sort(vec.begin(), vec.end());

    vec_sz mid = vec.size() / 2;
    return mid % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}

bool fgrade(const Student_info &s)
{
    return grade(s) < 60;
}

bool pgrade(const Student_info &s)
{
    return !fgrade(s);
}