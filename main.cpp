#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream> //formatted string processing
#include <cstdlib> //atof and atoi
#include "student.hpp"
#include "list.hpp"
#include "unit.hpp"



int main()
{

    ifstream insert_unit("insert-test.txt");
    string line;
    int stu_count = 0;
    int mode = 0;

    
    
    dom_basic_test<DS_InsertTest>("insert-test.txt");   
    dom_searching_test<SearchTest<DSLinkedList, DomesticStudent>, DSLinkedList, DomesticStudent>("search-test.txt");

    return 0;
}

