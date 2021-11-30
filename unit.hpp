#ifndef unit_hpp
#define unit_hpp

#include "list.hpp"
#include "student.hpp"
#include <type_traits>

void call_all();


Student compile_regular(string line, int count);
DomesticStudent compile_domestic(string line, int count);
InternationalStudent compile_international(string line, int count);
bool compare_students(DomesticStudent stu1, DomesticStudent stu2);
bool compare_students(InternationalStudent stu1, InternationalStudent stu2);
bool compare_students(Student stu1, Student stu2);

template <class ltype, class stype>
void demolish_list(ltype &list)
{
    while (list.head != NULL)
    {
        list.RemoveTail();
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

template <class ltype, class stype>
class InsertTest
{
public:
    void on_end(ltype list, vector<stype> vect)
    {
        cout << "-------------------------------------";
        if(assert(list, vect)){
            cout << "\nInsert Test Pass\n";
        }else{
            cout << "\nInsert Test Fail\n";
        }
        cout << "-------------------------------------" << endl;
    }
    void on_mode0(ltype &list, vector<stype> &vect, stype stu)
    {
        list.AddNode(stu);
    }
    void on_mode1(ltype &list, vector<stype> &vect, stype stu)
    {
        vect.push_back(stu);
    }
};

void dom_insert_test(string test_file)
{
    DSLinkedList domestic_students;
    vector<DomesticStudent> test_orders;

    ifstream insert_unit(test_file);
    string line;
    int stu_count = 0;
    int mode = 0;
    InsertTest<DSLinkedList, DomesticStudent> test;

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

        if (mode == 0)
        {
            test.on_mode0(domestic_students, test_orders, compile_domestic(line, stu_count));
        }
        if (mode == 1)
        {
            test.on_mode1(domestic_students, test_orders, compile_domestic(line, stu_count));
        }
    }
}
void int_insert_test(string test_file)
{
    ISLinkedList domestic_students;
    vector<InternationalStudent> test_orders;

    ifstream insert_unit(test_file);
    string line;
    int stu_count = 0;
    int mode = 0;
    InsertTest<ISLinkedList, InternationalStudent> test;

    while (getline(insert_unit, line))
    {
        if (line == "END")
        {
            test.on_end(domestic_students, test_orders);
            demolish_list<ISLinkedList, InternationalStudent>(domestic_students);
            test_orders.clear();
            mode = 0;
            continue;
        }
        if (line == "SWITCH")
        {
            mode = 1;
            continue;
        }

        if (mode == 0)
        {
            test.on_mode0(domestic_students, test_orders, compile_international(line, stu_count));
        }
        if (mode == 1)
        {
            test.on_mode1(domestic_students, test_orders, compile_international(line, stu_count));
        }
    }
}

template <class type, class stype>
class SearchTest
{
public:
    void on_end(type list, vector<float> gpas, vector<int> appids, vector<string> names, vector<int> scores)
    {
        cout << "-------------------------------------";
        cout << "\nList to search: \n";
        list.print();
        for (auto i : gpas)
        {
            cout << "\n\nSearch with GPA = " << i << endl;
            SearchCGPA<type, stype>(list, i);
        }
        cout << endl;
        for (auto i : appids)
        {
            cout << "\n Search with ID = " << i << endl;
            SearchID<type, stype>(list, i);
        }
        cout << endl;
        for (auto i : names)
        {
            cout << "\n Search with name = " << i << endl;
            SearchName<type, stype>(list, i, false);
        }
        cout << endl;
        for (auto i : scores)
        {
            cout << "\n Search with score = " << i << endl;
            SearchScore<type, stype>(list, i);
        }
        cout << "-------------------------------------"<<endl;
    }
    void on_mode0(type &list, vector<stype> &vect, stype stu)
    {
        list.AddNode(stu);
        vect.push_back(stu);
    }
};

DomesticStudent make_student(string firstName, string lastName, float cgpa, int researchScore, int temp_id, string province)
{
    DomesticStudent stu(firstName, lastName, cgpa, researchScore, temp_id, province);
    return stu;
}
Student make_student(string firstName, string lastName, float cgpa, int researchScore, int temp_id)
{
    Student stu(firstName, lastName, cgpa, researchScore, temp_id);
    return stu;
}
InternationalStudent make_student(string firstName, string lastName, float cgpa, int researchScore, int temp_id, string country, int r, int l, int s, int w)
{
    InternationalStudent stu(firstName, lastName, cgpa, researchScore, temp_id, country, r, l, s, w);
    return stu;
}

void dom_searching_test(string test_file)
{
    DSLinkedList domestic_students;
    vector<DomesticStudent> test_orders;
    vector<float> gpa_criteria;
    vector<int> app_ids;
    vector<string> names;
    vector<int> scores;

    int stu_type;

    ifstream insert_unit(test_file);
    string line;
    int stu_count = 0;
    int mode = 0;
    SearchTest<DSLinkedList, DomesticStudent> test;

    while (getline(insert_unit, line))
    {
        if (line == "END")
        {
            test.on_end(domestic_students, gpa_criteria, app_ids, names, scores);
            demolish_list<DSLinkedList, DomesticStudent>(domestic_students);
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
        if (line == "SCORE")
        {
            mode = 4;
            continue;
        }

        istringstream ss(line);
        if (mode == 0)
        {

            test.on_mode0(domestic_students, test_orders, compile_domestic(line, stu_count));

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
        if (mode == 4)
        {
            int score = atoi(line.c_str());
            scores.push_back(score);
        }
    }
}

template <class type, class stype>
class DeleteTest
{
public:
    void on_end(type &list, vector<stype> vect, vector<string> names)
    {
        cout << "-------------------------------------";
        for (auto i : names)
        {
            cout << "\n\nDeleting name = " << i << endl;
            SearchName<type, stype>(list, i, true);
        }
        if (assert(list, vect))
        {
            cout << "\n\nDelete Success\n";
        }else { cout << "\n\nDelete Fail\n"; }
        cout << endl;
        cout << "-------------------------------------" << endl;
    }
    void on_mode0(type &list, vector<stype> &vect, stype stu)
    {
        list.AddNode(stu);
    }
    void on_mode1(type &list, vector<stype> &vect, stype stu)
    {
        vect.push_back(stu);
    }
};


void dom_deleting_test(string test_file)
{
    DSLinkedList domestic_students;
    vector<DomesticStudent> test_orders;
    vector<string> names;

    int stu_type;

    ifstream insert_unit(test_file);
    string line;
    int stu_count = 0;
    int mode = 0;
    DeleteTest<DSLinkedList, DomesticStudent> test;

    while (getline(insert_unit, line))
    {
        if (line == "END")
        {
            test.on_end(domestic_students, test_orders, names);
            demolish_list<DSLinkedList, DomesticStudent>(domestic_students);
            test_orders.clear();
            names.clear();
            mode = 0;
            continue;
        }
        if (line == "SWITCH")
        {
            mode = 1;
            continue;
        }
        if (line == "DELETE")
        {
            mode = 2;
            continue;
        }
        if (mode == 1 || mode == 0)
        {

            if (mode == 0)
            {
                test.on_mode0(domestic_students, test_orders, compile_domestic(line, stu_count));
            }
            if (mode == 1)
            {
                test.on_mode1(domestic_students, test_orders, compile_domestic(line, stu_count));
            }
        }
        if (mode == 2)
        {
            string name = line;
            names.push_back(line);
        }
    }
}

template <class type, class stype>
class HTDeleteTest
{
public:
    void on_end(type &list, vector<stype> vect)
    {
        cout << "-------------------------------------";
        RemoveHeadTail(list);

        if (assert(list, vect))
        {
            cout << "\n\nHead and Tail delete Success\n";
        }
        else
        {
            cout << "\n\nHead and Tail delete Fail\n";
        }
        cout << "-------------------------------------" << endl;
    }
    void on_mode0(type &list, vector<stype> &vect, stype stu)
    {
        list.AddNode(stu);
    }
    void on_mode1(type &list, vector<stype> &vect, stype stu)
    {
        vect.push_back(stu);
    }
};


void dom_htdelete_test(string test_file)
{
    DSLinkedList domestic_students;
    vector<DomesticStudent> test_orders;
    int stu_type;

    ifstream insert_unit(test_file);
    string line;
    int stu_count = 0;
    int mode = 0;
    HTDeleteTest<DSLinkedList, DomesticStudent> test;

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
        if (mode == 1 || mode == 0)
        {
            if (mode == 0)
            {
                test.on_mode0(domestic_students, test_orders, compile_domestic(line, stu_count));
            }
            if (mode == 1)
            {
                test.on_mode1(domestic_students, test_orders, compile_domestic(line, stu_count));
            }
        }
    }
}


void int_deleting_test(string test_file)
{
    ISLinkedList domestic_students;
    vector<InternationalStudent> test_orders;
    vector<string> names;

    int stu_type;

    ifstream insert_unit(test_file);
    string line;
    int stu_count = 0;
    int mode = 0;
    DeleteTest<ISLinkedList, InternationalStudent> test;

    while (getline(insert_unit, line))
    {
        if (line == "END")
        {
            test.on_end(domestic_students, test_orders, names);
            demolish_list<ISLinkedList, InternationalStudent>(domestic_students);
            test_orders.clear();
            names.clear();
            mode = 0;
            continue;
        }
        if (line == "SWITCH")
        {
            mode = 1;
            continue;
        }
        if (line == "DELETE")
        {
            mode = 2;
            continue;
        }
        if (mode == 1 || mode == 0)
        {

            if (mode == 0)
            {
                test.on_mode0(domestic_students, test_orders, compile_international(line, stu_count));
            }
            if (mode == 1)
            {
                test.on_mode1(domestic_students, test_orders, compile_international(line, stu_count));
            }
        }
        if (mode == 2)
        {
            string name = line;
            names.push_back(line);
        }
    }
}


void int_htdeleting_test(string test_file)
{
    ISLinkedList domestic_students;
    vector<InternationalStudent> test_orders;
    ifstream insert_unit(test_file);
    string line;
    int stu_count = 0;
    int mode = 0;
    HTDeleteTest<ISLinkedList, InternationalStudent> test;

    while (getline(insert_unit, line))
    {
        if (line == "END")
        {
            test.on_end(domestic_students, test_orders);
            demolish_list<ISLinkedList, InternationalStudent>(domestic_students);
            test_orders.clear();
            mode = 0;
            continue;
        }
        if (line == "SWITCH")
        {
            mode = 1;
            continue;
        }
        if (mode == 1 || mode == 0)
        {

            if (mode == 0)
            {
                test.on_mode0(domestic_students, test_orders, compile_international(line, stu_count));
            }
            if (mode == 1)
            {
                test.on_mode1(domestic_students, test_orders, compile_international(line, stu_count));
            }
        }
    }
}

void int_searching_test(string test_file)
{
    ISLinkedList domestic_students;
    vector<InternationalStudent> test_orders;
    vector<float> gpa_criteria;
    vector<int> app_ids;
    vector<string> names;
    vector<int> scores;

    int stu_type;

    ifstream insert_unit(test_file);
    string line;
    int stu_count = 0;
    int mode = 0;
    SearchTest<ISLinkedList, InternationalStudent> test;

    while (getline(insert_unit, line))
    {
        if (line == "END")
        {
            test.on_end(domestic_students, gpa_criteria, app_ids, names, scores);
            demolish_list<ISLinkedList, InternationalStudent>(domestic_students);
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
        if (line == "SCORE")
        {
            mode = 4;
            continue;
        }

        if (mode == 0)
        {

            test.on_mode0(domestic_students, test_orders, compile_international(line, stu_count));
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
        if (mode == 4)
        {
            int score = atoi(line.c_str());
            scores.push_back(score);
        }
    }
}

class MergeTest
{
public:
    void on_end(DSLinkedList &list1, ISLinkedList &list2, vector<Student> &vect)
    {
        cout << "-------------------------------------";
        SLinkedList list(list1, list2);
        if (assert(list, vect))
        {
            cout << "\nMerge Success\n";
        }
        else
        {
            cout << "\n\nMerge Fail\n";
        }
        cout << "-------------------------------------" << endl;
    }
    void on_mode0(DSLinkedList &list1, ISLinkedList &list2, vector<Student> &vect, DomesticStudent stu1)
    {
        list1.AddNode(stu1);
    }
    void on_mode1(DSLinkedList &list1, ISLinkedList &list2, vector<Student> &vect, InternationalStudent stu1)
    {
        list2.AddNode(stu1);
    }
    void on_mode2(DSLinkedList &list1, ISLinkedList &list2, vector<Student> &vect, Student stu1)
    {
        vect.push_back(stu1);
    }
};


void merging_test(string test_file)
{
    DSLinkedList domestic_students;
    ISLinkedList int_students;
    vector<Student> test_orders;
    vector<float> gpa_criteria;
    vector<int> app_ids;
    vector<string> names;
    vector<int> scores;

    int stu_type;

    ifstream insert_unit(test_file);
    string line;
    int stu_count = 0;
    int mode = 0;
    MergeTest test;

    while (getline(insert_unit, line))
    {
        if (line == "TOINT")
        {
            break;
        }

        test.on_mode0(domestic_students, int_students, test_orders, compile_domestic(line, stu_count));
    }
    while (getline(insert_unit, line))
    {
        if (line == "SWITCH")
        {
            break;
        }

        test.on_mode1(domestic_students, int_students, test_orders, compile_international(line, stu_count));
    }
    while (getline(insert_unit, line))
    {
        if (line == "END")
        {
            break;
        }

        test.on_mode2(domestic_students, int_students, test_orders, compile_regular(line, stu_count));
    }
    test.on_end(domestic_students, int_students, test_orders);
}

class MergedSortTest
{
public:
    void on_end(DSLinkedList &list1, ISLinkedList &list2,vector<float> gpas, vector<int> scores)
    {
        cout << "-------------------------------------";
        SLinkedList list(list1, list2);
        cout << endl;
        cout << "List to filter:";
        list.print();
        cout << endl;

        for(auto i : gpas){
            cout << "\nfiltering with gpa >= " << i;
            FilterCGPA<SLinkedList, Student>(list, i);
        }
        cout << endl;
        for(auto i : scores){
            cout << "\nfiltering with score >= " << i;
            FilterScore<SLinkedList, Student>(list, i);
        }
        cout << endl;
        cout << "-------------------------------------" << endl;
    }
    void on_mode0(DSLinkedList &list1, ISLinkedList &list2, vector<Student> &vect, DomesticStudent stu1)
    {
        list1.AddNode(stu1);
    }
    void on_mode1(DSLinkedList &list1, ISLinkedList &list2, vector<Student> &vect, InternationalStudent stu1)
    {
        list2.AddNode(stu1);
    }
};

void merging_sort_test(string test_file)
{
    DSLinkedList domestic_students;
    ISLinkedList int_students;
    vector<Student> test_orders;
    vector<float> gpa_criteria;
    vector<int> scores;

    int stu_type;

    ifstream insert_unit(test_file);
    string line;
    int stu_count = 0;
    int mode = 0;
    MergedSortTest test;

    while (getline(insert_unit, line))
    {
        if (line == "TOINT")
        {
            break;
        }

        test.on_mode0(domestic_students, int_students, test_orders, compile_domestic(line, stu_count));
    }
    while (getline(insert_unit, line))
    {
        if (line == "GPA")
        {
            break;
        }

        test.on_mode1(domestic_students, int_students, test_orders, compile_international(line, stu_count));
    }
    while (getline(insert_unit, line))
    {
        if (line == "SCORE")
        {
            break;
        }
        gpa_criteria.push_back(atof(line.c_str()));
    }
    while (getline(insert_unit, line))
    {
        if (line == "END")
        {
            break;
        }
        scores.push_back(atof(line.c_str()));
    }
    test.on_end(domestic_students, int_students, gpa_criteria, scores);
}
DomesticStudent compile_domestic(string line, int count)
{
    istringstream ss(line);
    string firstName, lastName, province, s_cgpa, s_researchScore;
    float cgpa;
    int researchScore;
    int r, l, s, w;
    getline(ss, firstName, ',');
    getline(ss, lastName, ',');
    getline(ss, province, ',');
    getline(ss, s_cgpa, ',');
    cgpa = atof(s_cgpa.c_str());
    getline(ss, s_researchScore, ',');
    researchScore = atoi(s_researchScore.c_str());
    int temp_id = 20210000 + count;

    return make_student(firstName, lastName, cgpa, researchScore, temp_id, province);
}
InternationalStudent compile_international(string line, int count)
{
    istringstream ss(line);
    string firstName, lastName, province, s_cgpa, s_researchScore, country, s_r, s_l, s_s, s_w;
    float cgpa;
    int researchScore;
    int r, l, s, w;
    getline(ss, firstName, ',');
    getline(ss, lastName, ',');
    getline(ss, country, ',');
    getline(ss, s_cgpa, ',');
    cgpa = atof(s_cgpa.c_str());
    getline(ss, s_researchScore, ',');
    researchScore = atoi(s_researchScore.c_str());
    getline(ss, s_r, ',');
    r = atoi(s_r.c_str());

    getline(ss, s_l, ',');
    l = atoi(s_l.c_str());

    getline(ss, s_s, ',');
    s = atoi(s_s.c_str());

    getline(ss, s_w, ',');
    w = atoi(s_w.c_str());
    int temp_id = 20210000 + count;

    return make_student(firstName, lastName, cgpa, researchScore, temp_id, country, r, l, s, w);
}
Student compile_regular(string line, int count)
{
    istringstream ss(line);
    string firstName, lastName, province, s_cgpa, s_researchScore;
    float cgpa;
    int researchScore;
    int r, l, s, w;
    getline(ss, firstName, ',');
    getline(ss, lastName, ',');
    getline(ss, s_cgpa, ',');
    cgpa = atof(s_cgpa.c_str());
    getline(ss, s_researchScore, ',');
    researchScore = atoi(s_researchScore.c_str());

    int temp_id = 20210000 + count;

    return make_student(firstName, lastName, cgpa, researchScore, temp_id);
}
void call_all_tests(){

    cout<<"\nInsertion Testing Domestic\n";
    cout<<"1. Normal Case 2. Duplicate students 3. large amount of students 4. Illegal Names" << endl;
    dom_insert_test("testingfiles/domestic_insert_test.txt");  
    cout<<"\n\nInsertion Testing International\n";
    cout<<"1. Normal Case 2. Duplicate students 3. large amount of students 4. Illegal Names 5. No valid toefls" << endl;
    int_insert_test("testingfiles/international_insert_test.txt");
    dom_searching_test("testingfiles/domestic_search_test.txt");
    int_searching_test("testingfiles/international_search_test.txt");

    cout << "\nDeleting Tests Both\n";
    cout<<"1. Regular 2. Empty List 3. Empyting a list\n";
    dom_deleting_test("testingfiles/domestic_delete_test.txt");
    int_deleting_test("testingfiles/international_delete_test.txt");

    cout<<"\nHead and tail delete both";
    cout<<"1. regular 2. empty list 3. 1 item list 4. 2 item list\n";
    dom_htdelete_test("testingfiles/domestic_htdelete_test.txt");
    int_htdeleting_test("testingfiles/international_htdelete_test.txt");

    cout<<"Merging Test\n";
    cout <<"1. regular 2. empty 3. empty international 4. empty domestic";
    merging_test("testingfiles/merge_test.txt");
    merging_test("testingfiles/merge_test2.txt");
    merging_test("testingfiles/merge_test3.txt");
    merging_test("testingfiles/merge_test4.txt");
    merging_sort_test("testingfiles/merged_filtering_test.txt");

}
#endif