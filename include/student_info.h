#ifndef __STUDENT_INFO_H__
#define __STUDENT_INFO_H__

#include <string>
#include <vector>
#include <iostream>

struct Student_info
{
    std::string name;
    double midterm, final;
    std::vector<double> homeworks;
};

bool compare(const Student_info &, const Student_info &);
std::istream &read(std::istream &, Student_info &);
std::istream &read_hw(std::istream &, std::vector<double> &);

#endif // __STUDENT_INFO_H__