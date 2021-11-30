#ifndef list_hpp
#define list_hpp
#include <cmath>
#include "student.hpp"
#include <iostream>
#include <vector>


template <class type>
struct Link // Basic Structure for the link in the linked lists, a template to allow use in all lists
{
    type student;
    Link<type> *link;
};



struct student_data // as struct to hold the students' info when merging lists
{
    string first_name;    //General student Information
    string last_name;
    float CGPA;
    int research_score;
    string home_location;
    int orig_type;
    int app_id;
};

void merge_sort(vector<student_data>& in_vect); // alt merge sort for vectors, used in the merged list 
void merge(vector<student_data>& left, vector<student_data>& right, vector<student_data>& results);


class DSLinkedList
{
private:
public:
    ~DSLinkedList();
    Link<DomesticStudent> *head, *tail;
    DSLinkedList();
    void Sort(); // Sorting based on interim project (research, cgpa, province)
    void AddNode(DomesticStudent x); // function that adds node to the list, automatically sorts
    void print();   // prints the entire list according to print function from interim
    void RemoveHead();  // deletes the head node of the list and replaces with its successor
    void RemoveTail();  // deletes the tail and replaces with the previous link
    template <class list_type, class type>
    friend void push_node_to_list(list_type list, type x);  // friend helper function to push a student to
};                                                          // list, use AddNode instead to add a student
class ISLinkedList
{

private:
public:
    ~ISLinkedList();
    Link<InternationalStudent> *head, *tail;
    ISLinkedList();
    void Sort();    // Sorting based on interim project (research, cgpa, province)
    void RemoveHead();  // same as DSLinkedList
    void RemoveTail();  // same as DSLinkedList
    void AddNode(InternationalStudent x);   // // function that adds node to the list, automatically sorts, wont add invalid toefl
    void print();   // same as DSLinkedList
    template <class list_type, class type>
    friend void push_node_to_list(list_type list, type x);  // same as DSLinkedList
};


class SLinkedList
{
    private:
public:
    ~SLinkedList();
    Link<Student> *head, *tail;
    SLinkedList();
    SLinkedList(DSLinkedList ds_in, ISLinkedList is_in);
    void Sort();    // Sorting based on interim project (research, cgpa, province)
    void RemoveHead();  // same as DSLinkedList
    void RemoveTail();  // same as DSLinkedList
    void AddNode(Student x);   // // function that adds node to the list, automatically sorts, wont add invalid toefl
    void print();   // same as DSLinkedList

    void MergeLists(DSLinkedList DList, ISLinkedList IList);
    template <class list_type, class type>
    friend void push_node_to_list(list_type list, type x);  // same as DSLinkedList

    
};

void compile_students(DSLinkedList ds_in, ISLinkedList is_in, vector<student_data> &stu_data);

template <class list_type, class link_type>
void set_tail(list_type *list) // properly sets the tail of a list by finding the last link
{
    if(list->head == NULL && list->tail == NULL){ return; }
    Link<link_type> *temp_link = list->head;
    if (temp_link->link == NULL)
    {
        list->tail = list->head;    // base case if the head is the tail
        return;
    }
    while (temp_link->link != NULL)
    {
        temp_link = temp_link->link;    // loops until it finds the tail link (node with no link)
    }
    list->tail = temp_link; // sets the tail link to the link found above
}

template <class list_type, class type>
void push_node_to_list(list_type list, type x) // adds a link by placeing it at the top of the list
{
    if (!(x.valid_toefl())) // if the student doesn't have a valid toefl, don't add it (Domestic always returns true)
    {
        return;
    }

    x.set_cgpa(round((x.get_cgpa() * 10)) / 10); // round the gpa now so the searching will work easier
    try
        {
            Link<type> *new_link = new Link<type>;  
            new_link->student = x;
            new_link->link = list->head;    // sets the new student as the head and points to the previous head
            list->head = new_link;
        }
        catch (const std::bad_alloc &)
        {
            exit(2);
        }
    
}


template <class type>
type *MergeSorted(type *link1, type *link2) // the main helper function of the merge sort, actually does the sorting (score -> cgpa -> location). Only for domestic and international lists
{
    type *result = NULL;
    if (link1 == NULL)
    {
        return link2;
    }
    else if (link2 == NULL)
    {
        return link1;
    }

        int research_compare = compareResearchScore(link1->student, link2->student);
        if (research_compare == 1)
        {
            result = link1;
            result->link = MergeSorted(link1->link, link2);
        }
        else if (research_compare == -1)
        {
            result = link2;
            result->link = MergeSorted(link1, link2->link);
        }
        else if (research_compare == 0)
        {
            int cgpa_compare = compareCGPA(link1->student, link2->student);
            if (cgpa_compare == 1)
            {
                result = link1;
                result->link = MergeSorted(link1->link, link2);
            }
            else if (cgpa_compare == -1)
            {
                result = link2;
                result->link = MergeSorted(link1, link2->link);
            }
            else if (cgpa_compare == 0)
            {
                int province_compare = compareLocation(link1->student, link2->student);
                if (province_compare < 0)
                {
                    result = link1;
                    result->link = MergeSorted(link1->link, link2);
                }
                else if (province_compare > 0)
                {
                    result = link2;
                    result->link = MergeSorted(link1, link2->link);
                }
                else{
                    result = link1;
                    result->link = MergeSorted(link1->link, link2);
                }
            }
        }
    return result;
}

template <class type>
void SplitList(type *root, type **front, type **back)
{
    type *ptr1;
    type *ptr2;
    ptr2 = root;
    ptr1 = root->link;
    while (ptr1 != NULL)
    {
        ptr1 = ptr1->link;
        if (ptr1 != NULL)
        {
            ptr2 = ptr2->link;
            ptr1 = ptr1->link;
        }
    }

    *front = root;
    *back = ptr2->link;
    ptr2->link = NULL;
}

template <class type>
void MergeSort(type **thead)    // the main merge sort function that recursively calls itself and the other helper functions
{
    type *head = *thead;
    type *ptr1;
    type *ptr2;
    if ((head == NULL) || (head->link == NULL))
    {
        return;
    }
    SplitList(head, &ptr1, &ptr2);
    MergeSort(&ptr1);
    MergeSort(&ptr2);

    *thead = MergeSorted(ptr1, ptr2);
}

template <class list_type, class link_type>
int GetSize(list_type list) // simple helper that returns the size of a list, used in deletion
{
    int counter = 0;
    Link<link_type> *temp = list.head;
    while (temp != NULL)
    {
        counter++;
        temp = temp->link;
    }

    return counter;
}

template <class list_type, class link_type>
void deleteNode(list_type &list, int position)  //  delete function that deletes based on index
{
    int size = 0;
    int counter = 1;
    size = GetSize<list_type, link_type>(list) - 1;
    if (position == 0)  // if the link to be deleted is 0 (ie the head) then call the remove head helper function
    {
        list.RemoveHead();
        return;
    }
    if (position == size)   //  if the position is the size of the list (ie the tail) then use the remove tail helper function
    {
        list.RemoveTail();
        return;
    }
    if (size > 1 && position != size)   // otherwise find the link to be deleted and appropriately set the nearby links
    {
        Link<link_type> *node_to_delete = list.head->link;
        Link<link_type> *previous = list.head;
        while (node_to_delete != NULL)
        {
            if (counter == position)
            {
                break;
            }
            previous = node_to_delete;
            node_to_delete = node_to_delete->link;
            counter++;
        }
        previous->link = node_to_delete->link;
        free(node_to_delete);
    }
}

template <class list_type, class link_type>
void SearchID(list_type list, int id)   // searches a given list for a given id and then prints out the information of that student
{
    int counter = 0;
    Link<link_type> *temp_link = list.head;
        cout << endl
         << "Matching Students: ";
    while (temp_link != NULL)
    {
        if (temp_link->student.get_appid() == id)
        {
            cout << temp_link->student;
            counter += 1;
        }
        temp_link = temp_link->link;
    }
    if (counter == 0)
    {
        cout << "\nNo matching students\n";
    }
}

template <class list_type, class link_type>
void SearchCGPA(list_type list, float cgpa) // searches a given list for a given cgpa and then prints out the information of that student
{
    int counter = 0;
    Link<link_type> *temp_link = list.head;
        cout << endl
         << "Matching Students: ";
    while (temp_link != NULL)
    {
        if (temp_link->student.get_cgpa() == cgpa)
        {
            cout << temp_link->student;
            counter += 1;
        }
        temp_link = temp_link->link;
    }
    if (counter == 0)
    {
        cout << "\nNo matching students\n";
    }
}
template <class list_type, class link_type>
void FilterCGPA(list_type list, float cgpa) // searches a given list for a given cgpa and then prints out the information of that student
{
    int counter = 0;
    Link<link_type> *temp_link = list.head;
        cout << endl
         << "Matching Students: ";
    while (temp_link != NULL)
    {
        if (temp_link->student.get_cgpa() >= cgpa)
        {
            cout << temp_link->student;
            counter += 1;
        }
        temp_link = temp_link->link;
    }
    if (counter == 0)
    {
        cout << "\nNo matching students\n";
    }
}
template <class list_type, class link_type>
void SearchScore(list_type list, float score)   // searches a given list for a given research score and then prints out the information of that student
{
    int counter = 0;
    Link<link_type> *temp_link = list.head;
        cout << endl
         << "Matching Students: ";
    while (temp_link != NULL)
    {
        if (temp_link->student.get_res_score() == score)
        {
            cout << temp_link->student;
            counter += 1;
        }
        temp_link = temp_link->link;
    }
    if (counter == 0)
    {
        cout << "\nNo matching students\n";
    }
}
template <class list_type, class link_type>
void FilterScore(list_type list, float score)   // searches a given list for a given research score and then prints out the information of that student
{
    int counter = 0;
    Link<link_type> *temp_link = list.head;
        cout << endl
         << "Matching Students: ";
    while (temp_link != NULL)
    {
        if (temp_link->student.get_res_score() >= score)
        {
            cout << temp_link->student;
            counter += 1;
        }
        temp_link = temp_link->link;
    }
    if (counter == 0)
    {
        cout << "\nNo matching students\n";
    }
}
template <class list_type, class link_type>
void SearchName(list_type &list, string name, bool remove)  // searches a given list for a given name and then prints out the information of that student. Also deletes if remove is true. 
{                                                           // case and space insensitive
    int counter = 0;
    int index = 0;

    vector<int> to_remove;

    string lower_name = name;
    to_lowercase(lower_name);
    remove_space(lower_name);

    cout << endl
         << "Matching Students: ";

    Link<link_type> *temp_link = list.head;
    while (temp_link != NULL)
    {
        string stu_name = (temp_link->student.get_fname() + temp_link->student.get_lname());
        to_lowercase(stu_name);
        remove_space(stu_name);

        if (lower_name == stu_name)
        {
            cout << temp_link->student;

            to_remove.push_back(index);

            counter++;
        }
        index++;
        temp_link = temp_link->link;
    }
    if (counter == 0)
    {
        cout << "\nNo matching students\n";
    }
    if (remove)
    {
        for (auto x : to_remove)
        {
            deleteNode<list_type, link_type>(list, x);
        }
    }
}

template <class list_type>
void RemoveHeadTail(list_type &list){
    list.RemoveHead();
    list.RemoveTail();
}

#endif