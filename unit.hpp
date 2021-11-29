#ifndef unit_hpp
#define unit_hpp

#include "list.hpp"
#include "student.hpp"
#include <type_traits>

bool compare_students(DomesticStudent stu1, DomesticStudent stu2);
bool compare_students(InternationalStudent stu1, InternationalStudent stu2);
bool compare_students(Student stu1, Student stu2);

template <class ltype, class stype>
void demolish_list(ltype &list)
{
    while (list.head != NULL)
    {
        deleteNode<ltype, stype>(list, 0);
    }
}

template <class ltype, class stype>
bool assert(ltype list, vector<stype> vect)
{
    int counter = 0;
    Link<stype> *temp_link = list.head;

    // test if both empty
    if (GetSize<ltype, stype>(list) == 0 && vect.size() == 0)
    {
        return true;
    }

    // false if different size
    if (GetSize<ltype, stype>(list) != vect.size())
    {
        return false;
    }

    while (temp_link != NULL)
    {
        if (!compare_students(temp_link->student, vect[counter]))
        {
            return false;
        }
        temp_link = temp_link->link;
        counter++;
    }
    return true;
}

class DS_InsertTest
{
public:
    void on_end(DSLinkedList list, vector<DomesticStudent> vect)
    {
        cout << assert(list, vect);
    }
    void on_mode0(DSLinkedList &list, vector<DomesticStudent> &vect, DomesticStudent &stu)
    {
        list.AddNode(stu);
    }
    void on_mode1(DSLinkedList &list, vector<DomesticStudent> &vect, DomesticStudent &stu)
    {
        vect.push_back(stu);
    }
};


template <class test_type>
void dom_basic_test(string test_file)
{
    DSLinkedList domestic_students;
    vector<DomesticStudent> test_orders;

    ifstream insert_unit(test_file);
    string line;
    int stu_count = 0;
    int mode = 0;
    test_type test;

insert_unit_test:
    while (getline(insert_unit, line))
    {
        if (line == "END")
        {
            test.on_end(domestic_students, test_orders);
            demolish_list<DSLinkedList, DomesticStudent>(domestic_students);
            test_orders.clear();
            mode = 0;
            continue;
        }
        if (line == "SWITCH")
        {
            mode = 1;
            continue;
        }

        istringstream ss(line);
        string firstName, lastName, province, s_cgpa, s_researchScore;
        float cgpa;
        int researchScore;
        getline(ss, firstName, ',');
        getline(ss, lastName, ',');
        getline(ss, province, ',');
        getline(ss, s_cgpa, ',');
        cgpa = atof(s_cgpa.c_str());
        getline(ss, s_researchScore, ',');
        researchScore = atoi(s_researchScore.c_str());
        int temp_id = 20210000 + stu_count;
        DomesticStudent temp_student(firstName, lastName, cgpa, researchScore, temp_id, province);
        if (mode == 0)
        {
            test.on_mode0(domestic_students, test_orders, temp_student);
        }
        if (mode == 1)
        {
            test.on_mode1(domestic_students, test_orders, temp_student);
        }
    }
}

template<class type, class stype>
class SearchTest
{
public:
    void on_end(type list,vector<float> gpas, vector<int> appids, vector<string> names)
    {
        for (auto i : gpas)
        {
            cout<< "\n\nSearch with GPA = " << i << endl;
            SearchCGPA<type, stype>(list, i);
        }
        for (auto i : appids)
        {
            cout<< "\n Search with ID = " << i << endl;
            SearchID<type, stype>(list, i);
        }
        for (auto i : names)
        {
            cout<< "\n Search with name = " << i << endl;
            SearchName<type, stype>(list, i, false);
        }
    }
    void on_mode0(type &list, vector<stype> &vect, stype &stu)
    {
        list.AddNode(stu);
        vect.push_back(stu);
    }
};

template <class test_type, class ltype, class stype>
void dom_searching_test(string test_file)
{
    ltype domestic_students;
    vector<stype> test_orders;
    vector<float> gpa_criteria;
    vector<int> app_ids;
    vector<string> names;

    if (std::is_same<ltype, DSLinkedList>::value) { cout <<   "domestic student"; }

    ifstream insert_unit(test_file);
    string line;
    int stu_count = 0;
    int mode = 0;
    test_type test;

insert_unit_test:
    while (getline(insert_unit, line))
    {
        if (line == "END")
        {
            test.on_end(domestic_students, gpa_criteria, app_ids, names);
            demolish_list<ltype, stype>(domestic_students);
            test_orders.clear();
            mode = 0;
            continue;
        }
        if (line == "GPA")
        {
            mode = 1;
            continue;
        }
        if (line == "APPID")
        {
            mode = 2;
            continue;
        }
        if (line == "NAME")
        {
            mode = 3;
            continue;
        }

        istringstream ss(line);
        if (mode == 0)
        {
            string firstName, lastName, province, s_cgpa, s_researchScore;
            float cgpa;
            int researchScore;
            getline(ss, firstName, ',');
            getline(ss, lastName, ',');
            getline(ss, province, ',');
            getline(ss, s_cgpa, ',');
            cgpa = atof(s_cgpa.c_str());
            getline(ss, s_researchScore, ',');
            researchScore = atoi(s_researchScore.c_str());
            int temp_id = 20210000 + stu_count;
            stype temp_student(firstName, lastName, cgpa, researchScore, temp_id, province);
            test.on_mode0(domestic_students, test_orders, temp_student);
            stu_count++;
        }
        if (mode == 1)
        {
            float gpa = atof(line.c_str());
            gpa_criteria.push_back(gpa);
        }
        if (mode == 2)
        {
            int appid = atoi(line.c_str());
            app_ids.push_back(appid);
        }
        if (mode == 3)
        {
            string name = line;
            names.push_back(name);
        }
    }
}

#endif unit_hpp