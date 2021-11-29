//header file student.hpp to declare your classes
#ifndef student_hpp
#define student_hpp

using namespace std; //use namespace std
#include <string> //you will have to use string in C++
#include <ostream>
#include <iomanip>

void to_lowercase(string &s);
void remove_space(string &s);

class Student {
  protected:
    string first_name;    //General student Information
    string last_name;
    float CGPA;
    int research_score;
    string home_location;
    int orig_type = -1;
    int app_id = 20210000;
  public:

    Student(); //constructors
    Student(string _fname, string _lname, float _cpga, int _score, int _id);

    int get_orig_type() const;
    string get_fname() const;   //get functions
    string get_lname() const; 
    

    float get_cgpa() const;
    int get_res_score() const;
    int get_appid();    
    bool valid_toefl();

    void set_orig_type(int x);
    void set_fname(string _fname);  //set functions
    void set_lname(string _lname);
    void set_cgpa(float _cpga);
    void set_res_score(int _score);
    void set_appid(int _id);

    //comparison functions
    //Takes two student objects as arguments and returns:
    //             -1 if 1st value is less than 2nd
    //              0 if 1st value and 2nd are equal
    //              1 if 1st value is more than second
    friend int compareCGPA(const Student&stu1, const Student&stu2); //Compares CGPA of two students         
    friend int compareResearchScore(const Student&stu1, const Student&stu2);//Compares Research Score of two students   
    friend int compareFirstName(const Student&stu1, const Student&stu2);//Compares First Names of two students   
    friend int compareLastName(const Student&stu1, const Student&stu2);//Compares Last Names of two students
    friend int compareLocation(const Student &stu1, const Student &stu2);
    friend ostream& operator <<(ostream& outs, Student& stu);   

};

class DomesticStudent : public Student {
  protected:
    string province;
  public:
    // DomesticStudent(string _fname, string _lname, float _cpga, int _score, int _id, string _province);
    DomesticStudent();
    DomesticStudent(string _fname, string _lname, float _cgpa, int _score, int _id, string _province);

    string get_province() const;
    bool valid_toefl();
    friend int compareProvince(const DomesticStudent &stu1, const DomesticStudent &stu2);
    friend int compareLocation(const DomesticStudent &stu1, const DomesticStudent &stu2);
    void set_province(string _province);
    friend ostream& operator <<(ostream& outs, DomesticStudent& stu);
};



class InternationalStudent : public Student {
  protected:
    class ToeflScore {
      public: 
        int reading, listening, speaking, writing, total_score; 
      };

    ToeflScore toefl;
    string country;
  public:
    string get_country() const;
	bool valid_toefl(); 
    InternationalStudent();
    InternationalStudent(string _fname, string _lname, float _cgpa, int _score, int _id, string _country, int t_r, int t_l, int t_s, int t_w);
    void set_toefl(int _reading, int _listening, int _speaking, int _writing);
    friend ostream& operator <<(ostream& outs, InternationalStudent& stu);
    friend int compareCountry(const InternationalStudent &stu1, const InternationalStudent &stu2);
    friend int compareLocation(const InternationalStudent &stu1, const InternationalStudent &stu2);
    int* get_toefl();
};


#endif
