#include "list.hpp"
#include "student.hpp"

bool compare_students(DomesticStudent stu1, DomesticStudent stu2)
{
    if (
        stu1.get_cgpa() != stu2.get_cgpa() ||
        stu1.get_appid() != stu2.get_appid() ||
        stu1.get_fname() != stu2.get_fname() ||
        stu1.get_lname() != stu2.get_lname() ||
        stu1.get_orig_type() != stu2.get_orig_type() ||
        stu1.get_province() != stu2.get_province() ||
        stu1.get_res_score() != stu2.get_res_score())
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool compare_students(InternationalStudent stu1, InternationalStudent stu2)
{
    if (
        stu1.get_cgpa() != stu2.get_cgpa() ||
        stu1.get_appid() != stu2.get_appid() ||
        stu1.get_fname() != stu2.get_fname() ||
        stu1.get_lname() != stu2.get_lname() ||
        stu1.get_orig_type() != stu2.get_orig_type() ||
        stu1.get_country() != stu2.get_country() ||
        stu1.get_res_score() != stu2.get_res_score() ||
        (*stu1.get_toefl()) != *(stu2.get_toefl())
        )
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool compare_students(Student stu1, Student stu2)
{
    if (
        stu1.get_cgpa() != stu2.get_cgpa() ||
        stu1.get_appid() != stu2.get_appid() ||
        stu1.get_fname() != stu2.get_fname() ||
        stu1.get_lname() != stu2.get_lname() ||
        stu1.get_orig_type() != stu2.get_orig_type() ||
        stu1.get_res_score() != stu2.get_res_score())
    {
        return false;
    }
    else
    {
        return true;
    }
}