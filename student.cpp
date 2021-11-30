//student.cpp to implement your classes
#include "student.hpp"
#include <cmath>

// get functions for the parent Student class
int Student::get_appid(){ return app_id; }
float Student::get_cgpa() const{ return CGPA; }
int Student::get_res_score() const{ return research_score; }
string Student::get_fname() const{ return first_name; }
string Student::get_lname() const{ return last_name; }

// set functions for the parent Student class
void Student::set_fname(string _fname){ first_name = _fname; }
void Student::set_lname(string _lname){ last_name = _lname; }
void Student::set_cgpa(float _cpga){ CGPA = _cpga; }
void Student::set_res_score(int _score){ research_score = _score; }
void Student::set_appid(int _id){ app_id = _id; }
void Student::set_orig_type(int x) { orig_type = x; }

// get and set functions for the extra domestic student paramenters
string DomesticStudent::get_province() const{ return province; }
void DomesticStudent::set_province(string _province){ province = _province; }

// as set function that assigns the values to the toefl and changes the total
void InternationalStudent::set_toefl(int _reading, int _listening, int _speaking, int _writing){
  toefl.reading = _reading;
  toefl.listening = _listening;
  toefl.speaking = _speaking;
  toefl.writing = _writing;
  toefl.total_score = _reading + _listening + _speaking + _writing;

}

// get function for the international student country
string InternationalStudent::get_country() const{ return country; }

// get function that returns a pointer to an array of the toefl values
int * InternationalStudent::get_toefl() 
{
	static int OutputArray [5];           
  OutputArray[0] = toefl.reading;
  OutputArray[1] = toefl.listening;
  OutputArray[2] = toefl.speaking;
  OutputArray[3] = toefl.writing;
  OutputArray[4] = toefl.total_score;

  	return OutputArray;
}

// a default constructor for the parent student class
Student::Student(){
  first_name = "none";
  last_name = "none";
  CGPA = -1;
  research_score = -1;
  app_id = 0;
}

// a constructor for the parent student that assigns the passed in values to a student object
Student::Student(string _fname, string _lname, float _cgpa, int _score, int _id) : first_name(_fname), last_name(_lname), CGPA((round((_cgpa * 10)) / 10)), research_score(_score), app_id(_id) {}

// a defualt constructor for the domestic student that inherits the 
// student constructor but also sets the province to a defualt value
DomesticStudent::DomesticStudent() : Student(){

  province = "none";
  orig_type = 0;
}

// a constructor for the domestic student that inherits the 
// student constructor but also sets the province to a passed in value
DomesticStudent::DomesticStudent(string _fname, string _lname, float _cgpa, int _score, int _id, string _province) : Student(_fname, _lname, _cgpa, _score, _id){

  province = _province;
  orig_type = 0;
}



bool DomesticStudent::valid_toefl(){ return true; }
InternationalStudent::InternationalStudent() : Student(){
	toefl.listening = 0;
	toefl.reading = 0;
	toefl.speaking = 0;
	toefl.writing = 0;
	toefl.total_score = 0;
	orig_type = 1;
}
// a constructor for the international student that inherits the 
// student constructor but also sets the province to a passed in value
InternationalStudent::InternationalStudent(string _fname, string _lname, float _cgpa, int _score, int _id, string _country, int t_r, int t_l, int t_s, int t_w) : Student(_fname, _lname, _cgpa, _score, _id){
  country = _country;
  toefl.reading = t_r;
  toefl.listening = t_l;
  toefl.speaking = t_s;
  toefl.writing = t_w;
  toefl.total_score = t_r + t_l + t_s + t_w;
  orig_type = 1;

}

// a function that checks if a toefl is valid according to the standards listed
bool InternationalStudent::valid_toefl(){ 
	if(toefl.total_score < 93 || toefl.reading < 20 || toefl.listening < 20 || toefl.speaking < 20 || toefl.writing < 20){
		return false;
	}
	return true;
}

int Student::get_orig_type() const{
	return orig_type;
}

int compareLocation(const Student &stu1, const Student &stu2){

	if(stu1.get_orig_type() == 0 && stu2.get_orig_type() == 1){
		return -1;
	}
	if(stu1.get_orig_type() == 1 && stu2.get_orig_type() == 0){
		return 1;
	}
	return 0;

}


//Function that compares the CGPA of two students
int compareCGPA(const Student &stu1, const Student &stu2){

	if (stu1.get_cgpa() > stu2.get_cgpa()) {  //returns  1  if stu1 CGPA >  stu2 CGPA
		return 1;
	}
	else if (stu1.get_cgpa() < stu2.get_cgpa()) { //returns -1  if stu1 CGPA <  stu2 CGPA
		return -1;
	}
	else {	//returns  0  if stu1 CGPA == stu2 CGPA
		return 0;
	}
}
//Function that compares Research Score of two students 
int compareResearchScore(const Student&stu1, const Student&stu2){

	if (stu1.get_res_score() > stu2.get_res_score()) {        //For efficiency: could use return stu1.get_res_score() - stu2.get_res_score()
		return 1;                                               //This code can be repeated for the compareCGPA function above
	}
	else if (stu1.get_res_score() < stu2.get_res_score()) {
		return -1;
	}
	else {
		return 0;
	}

}

void remove_space(string &s){
	int counter = 0;
	
	for(auto & c: s){
		if (c == ' '){
			s.erase(counter, 1);
		}

		counter += 1;
	}
}

void to_lowercase(string &s){
	for (auto & c: s) c = (char)tolower(c);
}

//Function that compares First Names of two students 
int compareFirstName(const Student&stu1, const Student&stu2){

    return stu1.get_fname().compare(stu2.get_fname());
    //return strcmp(stu1.get_fname(), stu2.get_fname());
}

int compareProvince(const DomesticStudent& stu1, const DomesticStudent& stu2){

	string temp_stu1 = stu1.province;
	to_lowercase(temp_stu1);
	string temp_stu2 = stu2.province;
	to_lowercase(temp_stu2);

    return temp_stu1.compare(temp_stu2);
}
int compareLocation(const DomesticStudent &stu1, const DomesticStudent &stu2){
	string temp_stu1 = stu1.province;
	to_lowercase(temp_stu1);
	string temp_stu2 = stu2.province;
	to_lowercase(temp_stu2);

    return temp_stu1.compare(temp_stu2);
}
int compareLocation(const InternationalStudent &stu1, const InternationalStudent &stu2){
	string temp_stu1 = stu1.country;
	to_lowercase(temp_stu1);
	string temp_stu2 = stu2.country;
	to_lowercase(temp_stu2);

    return temp_stu1.compare(temp_stu2);
}
int compareCountry(const InternationalStudent& stu1, const InternationalStudent& stu2){
    string temp_stu1 = stu1.country;
	to_lowercase(temp_stu1);
	string temp_stu2 = stu2.country;
	to_lowercase(temp_stu2);

    return temp_stu1.compare(temp_stu2);
}

//Function that compares Last Names of two students 
int compareLastName(const Student&stu1, const Student&stu2){
  
  return stu1.get_lname().compare(stu2.get_lname());
}

//Function that the << operator 
ostream& operator<<(ostream& outs, Student& stu)
{
	outs << std::fixed << std::showpoint;
    outs << std::setprecision(1);
	outs << "\n\nStudent: " << stu.get_fname() << " " << stu.get_lname() << "(" << stu.get_appid() << "). ";  //puts name and student # in outs stream
	outs << "CGPA: " << stu.get_cgpa();                     //puts CGPA in outs stream (float value)
	outs << ". Reasearch Score: " << stu.get_res_score();   //puts research score in outs stream (int)

  return outs;
}
//Function that overloads the << operator. This is for domestic students
ostream& operator<<(ostream& outs, DomesticStudent& stu)
{
	outs << std::fixed << std::showpoint;   //used for rounding to 1 decimal place
  outs << std::setprecision(1);           //used for rounding to 1 decimal place
	outs << "\n\nStudent: " << stu.get_fname() << " " << stu.get_lname() << "(" << stu.get_appid() << "). ";  //puts name and student # in outs stream
	outs << "CGPA: " << stu.get_cgpa();                     //puts CGPA in outs stream (float value)
	outs << ". Reasearch Score: " << stu.get_res_score();   //puts research score in outs stream (int)
	outs << ". Province: " << stu.get_province();           //puts province in outs stream

  return outs;
}

bool Student::valid_toefl() { return true; }

//Function that overloads the << operator. This is for international students
ostream& operator<<(ostream& outs, InternationalStudent& stu)
{
	outs << std::fixed << std::showpoint;
    outs << std::setprecision(1);
	outs << "\n\nStudent: " << stu.get_fname() << " " << stu.get_lname() << "(" << stu.get_appid() << "). ";
	outs << "CGPA: " << stu.get_cgpa(); 
	outs << ". Reasearch Score: " << stu.get_res_score();
	outs << ". Country: " << stu.get_country();
	outs << ". Toefl Total: " << *(stu.get_toefl() + 4);

  return outs;
}




