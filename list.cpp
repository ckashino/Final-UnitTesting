#include "list.hpp"
#include <iostream>
#include <utility>

//  FUNCTION USES:
//  RemoveHead -> simply removes the head of the calling list and replaces it accordingly
//  RemoveTail -> simply removes the tail of the calling list and replaces it accordingly
//  merge_sort & merge -> additional sorting functions for a vector -> used when compiling 2 lists
//  set_tail -> sets the tail of the calling list to the last link in the list -> allows us to not worry about it during other functions (eg deleting)
//  Sort -> sorts a domestic or international list according to the interim, also sets the tail after
//  AddNode ->  calls the push_node_to_list template from the header to insert a link to the top of a list, also sorts and sets tail after
//  Print -> simply prints the information of all the students in a list, from top to bottom


void DSLinkedList::RemoveHead(){
    if(head == NULL){   //empty list
        return;
    }
    else{
        Link<DomesticStudent> * to_remove;  //item in list to remove is the head
        to_remove = head;   
        if(head == tail){   //only one element in list
            head = NULL;
            tail = NULL;
        }
        else{
            head = head->link;  //next element in list becomes the head
        }
        delete to_remove;   //delete head
    }

}
void DSLinkedList::RemoveTail(){
    if(tail == NULL){     //empty list
        return;
    }
    else{
        Link<DomesticStudent> * to_remove = tail;   //item in list to remove is the tail
        if(head == tail){       // only one element in list
            head = NULL;
            tail = NULL;
        }else{

            Link<DomesticStudent> * previous = head;      // previous before the tail, initialize to head
            while(previous->link != tail){                // loop through the list until the second last element
                previous = previous->link;                // this is the previous element to the tail
            }
            tail = previous;          //new tail is the previous
            tail->link = NULL;        //unlink old tail
        }
        delete to_remove;             //delete  old tail
    }

}

void compile_students(DSLinkedList ds_in, ISLinkedList is_in, vector<student_data>& stu_data) {

    
    Link<DomesticStudent>* ds_head = ds_in.head;
    Link<InternationalStudent>* is_head = is_in.head;
    

    while (ds_head != NULL) {
       
        student_data temp_student;

        temp_student.app_id = ds_head->student.get_appid();
        temp_student.CGPA = ds_head->student.get_cgpa();
        temp_student.first_name = ds_head->student.get_fname();
        temp_student.last_name = ds_head->student.get_lname();
        temp_student.home_location = ds_head->student.get_province();
        temp_student.research_score = ds_head->student.get_res_score();
        temp_student.orig_type = 0;   //orig type = 0 means domestic

        stu_data.push_back(temp_student);   //putting new student into list

        ds_head = ds_head->link;    //shouldn't this be the tail?

    }
    while (is_head != NULL) {

        student_data temp_student;

        temp_student.app_id = is_head->student.get_appid();
        temp_student.CGPA = is_head->student.get_cgpa();
        temp_student.first_name = is_head->student.get_fname();
        temp_student.last_name = is_head->student.get_lname();
        temp_student.home_location = is_head->student.get_country();
        temp_student.research_score = is_head->student.get_res_score();
        temp_student.orig_type = 1; //orig type = 1 means international

        stu_data.push_back(temp_student);   //putting new student into list

        is_head = is_head->link;    //shouldn't this be the tail?
                                    // head -> something -> something -> tail
    }


}

void merge_sort(vector<student_data>& in_vect) {
    if (in_vect.size() <= 1) {
        return;
    }

    int mid_point = in_vect.size() / 2;

    int offset = 0;

    if (mid_point * 2 != in_vect.size()) { offset = 1; }

    vector<student_data> left(in_vect.begin(), in_vect.end() - mid_point);
    vector<student_data> right(in_vect.begin() + mid_point + offset, in_vect.end());

    merge_sort(left);
    merge_sort(right);

    merge(left, right, in_vect);

}

void merge(vector<student_data>& left, vector<student_data>& right, vector<student_data>& results)
{
    int L_size = left.size();
    int R_size = right.size();
    int i = 0, j = 0, k = 0;
    while (j < L_size && k < R_size)
    {
        
        if (left[j].research_score > right[k].research_score) {
            results[i] = std::move(left[j]);
            j++;
        }
        else if (left[j].research_score < right[k].research_score) {
            results[i] = std::move(right[k]);
            k++;
        }
        else {
            if (left[j].CGPA > right[k].CGPA) {
                results[i] = std::move(left[j]);
                j++;
            }
            else if (left[j].CGPA < right[k].CGPA){
                results[i] = std::move(right[k]);
                k++;
            }
            else {
                if (left[j].orig_type < right[k].orig_type) {
                    results[i] = std::move(left[j]);
                    j++;
                }
                else if (left[j].orig_type > right[k].orig_type) {
                    results[i] = std::move(right[k]);
                    k++;
                }
                else {
                    string home_1 = left[j].home_location;
                    string home_2 = right[k].home_location;

                    to_lowercase(home_1);
                    to_lowercase(home_2);

                    if (home_1.compare(home_2) < 0) {
                        results[i] = std::move(left[j]);
                        j++;
                    }
                    else{
                        results[i] = std::move(right[k]);
                        k++;
                    }

                }

            }
        }



        i++;
    }
    while (j < L_size) {
        results[i] = std::move(left[j]);
        j++; i++;
    }
    while (k < R_size) {
        results[i] = std::move(right[k]);
        k++; i++;
    }
}

void ISLinkedList::RemoveTail(){
    if(tail == NULL){
        return;
    }
    else{
        Link<InternationalStudent> * to_remove = tail;
        if(head == tail){
            head = NULL;
            tail = NULL;
        }else{

            Link<InternationalStudent> * previous = head;
            while(previous->link != tail){
                previous = previous->link;
            }
            tail = previous;
            tail->link = NULL;
        }
        delete to_remove;
    }

}

void SLinkedList::RemoveTail(){
    if(tail == NULL){
        return;
    }
    else{
        Link<Student> * to_remove = tail;
        if(head == tail){
            head = NULL;
            tail = NULL;
        }else{

            Link<Student> * previous = head;
            while(previous->link != tail){
                previous = previous->link;
            }
            tail = previous;
            tail->link = NULL;
        }
        delete to_remove;
    }

}
void ISLinkedList::RemoveHead(){

    if(head == NULL){
        return;
    }
    else{
        Link<InternationalStudent> * to_remove;
        to_remove = head;
        if(head == tail){
            head = NULL;
            tail = NULL;
        }
        else{
            head = head->link;
        }
        delete to_remove;
    }
}
void SLinkedList::RemoveHead(){

    if(head == NULL){
        return;
    }
    else{
        Link<Student> * to_remove;
        to_remove = head;
        if(head == tail){
            head = NULL;
            tail = NULL;
        }
        else{
            head = head->link;
        }
        delete to_remove;
    }
}

DSLinkedList::DSLinkedList(){
    head = NULL;
    tail = NULL;
}

SLinkedList::SLinkedList(){
    head = NULL;
    tail = NULL;
}

void SLinkedList::Sort(){
    MergeSort(&(head));
    set_tail<SLinkedList, Student>(this);
}
void SLinkedList::AddNode(Student x){
    push_node_to_list(this, x);
    set_tail<SLinkedList, Student>(this);
}
void SLinkedList::print(){
    Link<Student> * temp = head;
    while(temp != NULL){
        cout << temp->student;
        temp = temp->link;
    }
}

void DSLinkedList::Sort(){
    MergeSort(&(head));
    set_tail<DSLinkedList, DomesticStudent>(this);
}
void DSLinkedList::print(){
    Link<DomesticStudent> * temp = head;
    while(temp != NULL){
        cout << temp->student;
        temp = temp->link;
    }
}

void DSLinkedList::AddNode(DomesticStudent x){
    push_node_to_list(this, x);
    Sort();
    set_tail<DSLinkedList, DomesticStudent>(this);
}

void ISLinkedList::AddNode(InternationalStudent x){
    push_node_to_list(this, x);
    Sort();
    set_tail<ISLinkedList, InternationalStudent>(this);
}

void ISLinkedList::print(){
    Link<InternationalStudent> * temp = head;
    while(temp != NULL){
        cout << temp->student;
        temp = temp->link;
    }
}

void ISLinkedList::Sort(){
    // ValidateT();
    MergeSort(&head);
    set_tail<ISLinkedList, InternationalStudent>(this);
    
}

ISLinkedList::ISLinkedList(){
    head = NULL;
    tail = NULL;
}
SLinkedList::SLinkedList(DSLinkedList ds_in, ISLinkedList is_in) {
    head = NULL;
    tail = NULL;
    MergeLists(ds_in, is_in);
}

void SLinkedList::MergeLists(DSLinkedList DList, ISLinkedList IList){
    vector<student_data> temp_students;
    compile_students(DList, IList, temp_students);
    merge_sort(temp_students);

    for (vector<student_data>::reverse_iterator i = temp_students.rbegin(); i != temp_students.rend(); ++i) {
        Student stu(i->first_name, i->last_name, i->CGPA, i->research_score, i->app_id);

        AddNode(stu);

    }
    set_tail<SLinkedList, Student>(this);

    

}