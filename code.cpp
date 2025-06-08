#include "u3a.h"


    //INITIATORS AND DECONSTRUCTORS --------------------------------------------
u3a::u3a(){
    pHead_student=nullptr;
    pHead_course=nullptr;
    pHead_teacher=nullptr;
    pHead_grouper=nullptr;
    pHead_classroom=nullptr;
    pHead_datalog = new datalog("System start");
}

u3a::student::student(int id, int age, char* name){

    this->completed_pHead = nullptr;
    this->id_student = id;
    this->age = age;

    this->courses = nullptr;

    this->name = new char[strlen(name)+1]; 
    strcpy(this->name,name);
}
u3a::student::~student(){delete[] this->name;}
u3a::teacher::teacher(int id, char* teacher_name){

    this->completed = nullptr;
    this->id_teacher = id;
    this->courses_conducted_pHead = nullptr;
    this->teacher_name = new char[strlen(teacher_name)+1];
    strcpy(this->teacher_name,teacher_name);}
u3a::teacher::~teacher(){delete[] this->teacher_name;}

u3a::course::course(int id, char* name, teacher* lecturer,int capacity){
    this->status = 0;
    this->capacity = capacity;
    this->id_course = id;
    this->student_list = nullptr;
    this->lecturer = new node_t(lecturer);
    this->course_name = new char[strlen(name)+1]; 
    strcpy(this->course_name,name);   
    this->student_count = 0;    
}
u3a::course::~course(){delete[] course_name;}

u3a::node_s::node_s(u3a::student* student){this->student = student;this->next = nullptr;}
u3a::node_s::~node_s(){}


//               GETTERS--------------------------------------------------------------
//student
int u3a::student::get_id(){return this->id_student;}
int u3a::student::get_age(){return this->age;}
char* u3a::student::get_name(){return this->name;}
u3a::node_s* u3a::get_pHead_student(){return this->pHead_student;}
u3a::node_c* u3a::student::get_courses(){return this->courses;}
//teacher
int u3a::teacher::get_id(){return this->id_teacher;}
char* u3a::teacher::get_name(){return this->teacher_name;}
u3a::node_t* u3a::get_pHead_teacher(){return this->pHead_teacher;}
//course
int u3a::course::get_capacity(){return this->capacity;}
int u3a::course::get_student_count(){return student_count;}
void u3a::course::set_student_count(int count){this->student_count = count;}
int u3a::course::get_id(){return this->id_course;}
char* u3a::course::get_name(){return this->course_name;}
u3a::node_s* u3a::course::get_studentPHead(){return this->student_list;}
u3a::node_t* u3a::course::get_lecturer(){return this->lecturer;}
u3a::node_c* u3a::get_pHead_course(){return this->pHead_course;}
//node_s
u3a::node_s* u3a::node_s::get_next(){return this->next;}
u3a::student* u3a::node_s::get_student(){return this->student;}


//Setters -------------------------------------------
void u3a::set_next(u3a::student* Student, u3a::student* target){
    node_of(Student)->set_next(node_of(target));
}

void u3a::set_next(u3a::student* Student, u3a::node_s* target){
    node_of(Student)->set_next(target);
}


void u3a::student::set_courses(node_c* link){this->courses = link;}

void u3a::set_pHead_student(u3a::student* Student){this->pHead_student = node_of(Student);}
void u3a::set_pHead_teacher(u3a::teacher* Teacher){this->pHead_teacher = node_of(Teacher);}
void u3a::set_pHead_course(u3a::course* Course)   {this->pHead_course = node_of(Course);}

//node_s
u3a::node_s* u3a::node_of(u3a::student* Student){

    node_s* currptr = pHead_student;

    while(currptr!=nullptr){
        if(currptr->get_student() == Student){return currptr;}
        currptr = currptr->get_next();
    }
    std::cerr<<"No such student cell found";
    return nullptr;
}
int u3a::node_s::get_id(){return this->student->get_id();}
void u3a::node_s::set_next(u3a::node_s* next){this->next = next;}
void u3a::node_s::set_student(u3a::student* Student){this->student = Student;}

    //Adders -------------------------------------------

void u3a::add_pHeadStudent(node_s* Student){
    Student->set_next(pHead_student);
    pHead_student = Student;
}
void u3a::add_pHeadStudent(student* Student){
    node_s* creation = new node_s(Student);
    creation->set_next(pHead_student);
    pHead_student = creation;
}
void u3a::add_pHeadTeacher(node_t* Teacher){
    Teacher->set_next(pHead_teacher);
    pHead_teacher = Teacher;
}
void u3a::add_pHeadTeacher(teacher* Teacher){
    node_t* creation = new node_t(Teacher);
    creation->set_next(pHead_teacher);
    pHead_teacher = creation;
}
void u3a::add_pHeadCourse(node_c* Course){
    Course->set_next(pHead_course);
    pHead_course = Course;
}
void u3a::add_pHeadCourse(course* Course){
    node_c* creation = new node_c(Course);
    creation->set_next(pHead_course);
    pHead_course = creation;
}

//New_ functions

u3a::student* u3a::new_student(int id, int age, char* name){
    u3a* uni = this;
    student* creation = new u3a::student(id, age, name);

    uni->add_pHeadStudent(creation);
    return creation;
}
u3a::teacher* u3a::new_teacher(int id, char* teacher_name){
    u3a* uni = this;
    teacher* creation = new u3a::teacher(id, teacher_name);
    uni->add_pHeadTeacher(creation);
    return creation;
}
u3a::course* u3a::new_course(int id, char* name, teacher* lecturer, int capacity){
    u3a* uni = this;
    course* creation = new u3a::course(id,name,lecturer,capacity);
    uni->add_pHeadCourse(creation);
    return creation;
}

//Insert functions
u3a::student* u3a::insert_new_student(int age, char* name){
    bool permit = 1;
    u3a::node_s* currptr;
    int potential_id = 0;
    while(true){
        currptr = pHead_student; 
        permit = 1;

        while(currptr!=nullptr){
            if(currptr->get_id()==potential_id){permit = 0;}
            currptr = currptr->get_next();
        }

        if(permit==1)
        {u3a::student* creation = new_student(potential_id, age, name); 
        log(combine_strings("Inserted a new student(id:",potential_id,")"));
        return creation;}
    
        potential_id++;
        
    }
}
u3a::teacher* u3a::insert_new_teacher(char* name){
    bool permit = 1;
    u3a::node_t* currptr;
    int potential_id = 0;

    while(true){
        currptr = pHead_teacher; 
        permit = 1;

        while(currptr!=nullptr){
            if(currptr->get_teacher()->get_id()==potential_id){permit = 0;}
            currptr = currptr->get_next();
        }

        if(permit==1){u3a::teacher* creation = new_teacher(potential_id, name); 
        log(combine_strings("Inserted a new teacher(id:",potential_id,")"));
        return creation;}
        potential_id++;
    }
}
u3a::course* u3a::insert_new_course(char* name, int lecturer_id, int capacity){
    bool permit = 1;
    u3a::node_c* currptr;
    int potential_id = 0;

    while(true){
        currptr = pHead_course; 
        permit = 1;

        while(currptr!=nullptr){
            if(currptr->get_course()->get_id()==potential_id){permit = 0;}
            currptr = currptr->get_next();
        }

        if(permit==1){u3a::course* creation = new_course(potential_id, name, findTeacherById(lecturer_id)->get_teacher(), capacity); 
        log(combine_strings("Inserted a new course(id:",potential_id,")"));
        return creation;}
        potential_id++;
    }
}

    //Finders -------------------------------------------

u3a::node_s* u3a::findStudById(int id){
    u3a* uni = this;
    u3a::node_s* currptr = uni->pHead_student;
    
    while(currptr!=nullptr){
        if(currptr->get_id() == id){return currptr;}
        currptr = currptr->get_next();
    }
    return nullptr;
}
u3a::node_c* u3a::findCourseById(int id){
    u3a* uni = this;
    u3a::node_c* currptr = uni->pHead_course;
 
    while(currptr!=nullptr){
        if(currptr->get_course()->get_id() == id){return currptr;}
        currptr = currptr->get_next();
    }
    return nullptr;
}
u3a::node_t* u3a::findTeacherById(int id){
    u3a* uni = this;
    u3a::node_t* currptr = uni->pHead_teacher;
 
    while(currptr!=nullptr){
        if(currptr->get_id() == id){return currptr;}
        currptr = currptr->get_next();
    }
    return nullptr;
}
int u3a::course_in_course_stack_check(u3a::course* Course){
    int response = 0;
    u3a::node_c* currptr = this->get_pHead_course();
    while(currptr!=nullptr){
        if(currptr->get_course()==Course)response = 1;
        currptr= currptr->get_next();
    }
    return response;
}

// Student operations

void u3a::append_student(u3a::course* Course, u3a::student* Student){
    node_s* creation = new node_s(Student);

        
    if(Course->get_studentPHead()==nullptr){
        creation->set_next(nullptr);
        Course->set_studentPHead(creation);
        return;
    }
    creation->set_next(Course->get_studentPHead());
    Course->set_studentPHead(creation);
    return;
}

void u3a::append_course(u3a::student* Student, u3a::course* Course){
    node_c* creation = new node_c(Course);
    creation->set_next(nullptr);

    if(Student->get_courses()==nullptr){
        Student->set_courses(creation);
        return;
    }

    creation->set_next(Student->get_courses());
    Student->set_courses(creation);
    return;
}

void u3a::enroll_student(int id, u3a::course *Course){

    u3a* uni = this;        
    student* Student = uni->findStudById(id)->get_student();

 //Error edge-testing

    if(Course==nullptr){std::cerr<<"Non-existient course\n"; return;}
    if(uni->findStudById(id)==nullptr){std::cerr<<"No such student\n"; return;}
    if(Course->get_capacity()<=Course->get_student_count()){std::cerr<<"Course full\n"; return;}
    if(does_student_attend(Student,Course)){std::cerr<<"Student's already attending the course(enrollment)\n";return;}

    append_student(Course, Student);  //Editing course->student_list
    append_course(Student,Course);   //EDITING STUDENT->COURSES LIST (Newest node added as the studentPhead)

 //Change course capacity status
    Course->set_student_count(Course->get_student_count() + 1);

    char* logging = combine_strings("Enrolled student(id:",id,") into a course(id:");
    log(combine_strings(logging,Course->get_id(),")"));

    return;
}

    //Removal methods

void u3a::pop_student_from_course_list(u3a::student* Student, u3a::course* Course){
    //Error handling
        if(Student==nullptr){std::cerr<<"Error, no such student";  return;}
        if(Course==nullptr){std::cerr<<"No such course";    return;}
        if(Course->get_studentPHead()==nullptr){std::cerr<<"Student list empty - second check"; return;}


    //Deleting a student from course->student_list
        
        node_s* currptr = Course->get_studentPHead();
        node_s* prevptr = nullptr;

        //if first (working)
            if(currptr->get_student()==Student){
                Course->set_studentPHead(currptr->get_next());
                delete currptr;
                return;
            }
        
        //if not 

            while(currptr!=nullptr){
                if(currptr->get_student()==Student){
                    prevptr->set_next(currptr->get_next());
                    delete currptr;
                    return;
                }
                prevptr=currptr;
                currptr= currptr->get_next();
            }
}

void u3a::pop_course_from_student_list(u3a::course* Course, u3a::student* Student){


    if(Student==nullptr){std::cerr<<"Error, no such student";  return;}
    if(Course==nullptr){std::cerr<<"No such course";    return;}
    if(Student->get_courses()==nullptr){std::cerr<<"Course list empty"; return;}

    node_c* currptr = Student->get_courses();
    node_c* prevptr = currptr;

    //If student first in the stack
    if(Student->get_courses()->get_course()==Course){
        prevptr = Student->get_courses();
        Student->set_courses(Student->get_courses()->get_next());
        delete prevptr;
        return;
    }
    
    //If not 
    while(currptr!=nullptr){
        if(currptr->get_course() == Course){
            if(prevptr==nullptr){
                Student->set_courses(currptr->get_next());
            }
            else{
                prevptr->set_next(currptr->get_next());
            }
            delete currptr;
            return;
        }
        prevptr= currptr;
        currptr = currptr->get_next();
    }
}


void u3a::deroll_student(int id, u3a::course* Course){

    u3a* uni = this;

    u3a::node_s* Studentn = uni->findStudById(id);
    //Error checks
        if(Studentn==nullptr){std::cerr<<"Error, no such student";  return;}
        if(Course==nullptr){std::cerr<<"No such course";    return;}
        if(does_student_attend(Studentn->get_student(), Course)==0){std::cerr<<"Student is not attending the course\n"; return;}

    //Deleting a course from student->courses(that are taken by the student)
        pop_student_from_course_list(Studentn->get_student(),Course);
    //Deleting a student from course->studentlist
        pop_course_from_student_list(Course,Studentn->get_student());
    // Update Course's student count
        Course->set_student_count(Course->get_student_count() - 1);
        log(combine_strings(combine_strings("Removed a student(id:",Studentn->get_student()->get_id(),") from a course(id:"),Course->get_id(),")"));
    return;
}


    //printers -------------------------------------------
void u3a::student::print_student(){std::cerr<<"\nSTUDENT INFO:\nId: "<<id_student<<"\nAge: "<<this->age<<"\nName: "<<this->name<<"\n\n";}
void u3a::teacher::print_teacher(){std::cerr<<"\nTEACHER INFO:\nId: "<<this->id_teacher<<"\nName: "<<this->teacher_name<<"\n\n";}
void u3a::course::print_course(){
    std::cerr<<"\nCOURSE INFO:"; 
    if(this->status==1){std::cerr<<" This course has finished!";}
    std::cerr<<"\nId: "<<this->id_course;
    std::cerr<<"\nName: "<<this->course_name;
    
    node_t* currptr = lecturer;
    while(currptr!=nullptr){
        std::cerr<<"\nLecturer:"<<(currptr->get_teacher())->get_name();
        std::cerr<<" ("<<(currptr->get_teacher())->u3a::teacher::get_id()<<")";
        currptr= currptr->get_next();
    }
    std::cerr<<"\n";
    std::cerr<<"Capacity: "<<this->get_student_count()<<"/"<<this->get_capacity()<<"\n\n";}

void u3a::node_s::print_student(){
    std::cerr<<"\nSTUDENT INFO:\nId: "<<student->get_id()<<"\nAge: "<<student->get_age()<<"\nName: "<<student->get_name()<<"\n\n";}
void u3a::course::print_student_list(){ this->get_studentPHead()->print_all();}

void u3a::course::set_studentPHead(u3a::node_s* node){this->student_list = node;}
void u3a::course::set_studentPHead_next(u3a::node_s* node){this->student_list->set_next(node);}


//          Node_t core fuctions

void u3a::node_t::print_all(){
    node_t* node = this;
    while(node!=nullptr){
        node->get_teacher()->print_teacher();
        std::cerr<<"\n";
        node = node->get_next();
    }
}
u3a::node_t* u3a::node_of(u3a::teacher* Teacher){

    u3a::node_t* currptr = pHead_teacher;

    while(currptr!=nullptr){
        if(currptr->get_teacher() == Teacher){return currptr;}
        currptr = currptr->get_next();
    }
    std::cerr<<"No such teacher cell found";
    return nullptr;
}
u3a::node_t::node_t(u3a::teacher* Teacher){
    this->teacher = Teacher;
    this->next = nullptr;
}
u3a::node_t::~node_t(){}
u3a::node_t* u3a::node_t::get_next(){
    return this->next;
}
u3a::teacher* u3a::node_t::get_teacher(){
    return this->teacher;
}
void u3a::node_t::print_teacher(){
    this->teacher->print_teacher();
}
void u3a::node_t::set_next(u3a::node_t* node){
    this->next = node;
}
void u3a::node_t::set_teacher(u3a::teacher* Teacher){
    this->teacher = Teacher;    
}
int u3a::node_t::get_id(){
    return this->teacher->get_id();
}

/// Node_c core functions



u3a::node_c::node_c(u3a::course* Course){
    this->course = Course;
    this->next = nullptr;
}

u3a::node_c::~node_c(){}

u3a::node_c* u3a::node_c::get_next(){
    return this->next;
}

u3a::course* u3a::node_c::get_course(){
    return this->course;
}

void u3a::node_c::print_course(){
    this->course->print_course();
}

void u3a::node_c::set_next(node_c* node){
    this->next = node;
}

void u3a::node_c::set_course(u3a::course* Course){this->course = Course;}

int u3a::node_c::get_id(){return this->course->get_id();}

u3a::node_c* u3a::node_of(u3a::course* Course){

    u3a::node_c* currptr = pHead_course;

    while(currptr!=nullptr){
        if(currptr->get_course() == Course){return currptr;}
        currptr = currptr->get_next();
    }
    std::cerr<<"No such course cell found";
    return nullptr;
}

// Node_s core function

void u3a::node_s::print_all(){
    node_s* node = this;
    while(node!=nullptr){
        node->get_student()->print_student();
        std::cerr<<"\n";
        node = node->get_next();
    }
}




void u3a::set_next(u3a::teacher* Teacher, u3a::teacher* target){
    node_of(Teacher)->set_next(node_of(target));
}

void u3a::set_next(u3a::teacher* Teacher, u3a::node_t* target){
    node_of(Teacher)->set_next(target);
}

int ask_int() {
    int temp;
    while (true) {
        std::cin >> temp;
        if (std::cin.fail()) { //if cin fails
            std::cin.clear();  //clears remaininig buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cerr << "Invalid input. Please enter an integer:\n->";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return temp;
        }
    }
}

char* ask_str() {
    std::string input;
    std::getline(std::cin, input);
    char* name = new char[input.size() + 1];
    strcpy(name, input.c_str());
    return name;
}

void sys_break() {
    #if defined(_WIN32) || defined(_WIN64)  // Windows
        system("pause");
    #elif defined(__linux__) || defined(__unix__)  // Linux/Unix
        system(R"(bash -c 'read -s -n 1 -p "Press any key to continue..."')");
    #elif defined(__APPLE__) || defined(__MACH__)  // macOS
        system("read -n 1 -s -r -p \"Press any key to continue...\" ");
    #else
        std::cerr << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    #endif
    cleanscreen();
}

void cleanscreen() {
    #if defined(_WIN32) || defined(_WIN64)  // windows
        system("cls");
    #elif defined(__linux__) || defined(__unix__)  // linux and some unix variants
        system("clear");
    #elif defined(__APPLE__) || defined(__MACH__)  // macOS (<3)
        system("clear");
    #else
        std::cerr << "\n\n\n";
    #endif
}


void u3a::set_next(u3a::course* Course, u3a::course* target){
    node_of(Course)->set_next(node_of(target));
}

void u3a::set_next(u3a::course* Course, u3a::node_c* target){
    node_of(Course)->set_next(target);
}



void u3a::node_c::print_all(){
    node_c* node = this;
    while(node!=nullptr){
        node->get_course()->print_course();
        std::cerr<<"\n";
        node = node->get_next();
    }
}

int u3a::does_student_attend(u3a::student* Student, u3a::course* Course){

    int result1=0;
    node_s* currptr = Course->get_studentPHead();
    //is student in course list?
    while(currptr!=nullptr){

        if(currptr->get_student()==Student){
            result1=1;
        }
        currptr=currptr->get_next();
    }

    //is the course in the student's course list
    int result2=0;
    node_c* currptr1 = Student->get_courses();

    while(currptr1!=nullptr){
        if(currptr1->get_course()==Course){
            result2=1;
        }
        currptr1=currptr1->get_next();
    }

    return result2;
}


void u3a::course::print_all_lecturers(){

    node_t* currptr = this->get_lecturer();

    while(currptr!=nullptr){
        currptr->print_teacher();
        currptr=currptr->get_next();
    }
    return;
}


void u3a::add_lecturer(u3a::teacher* lecturer, u3a::course* Course){

    node_t* currptr = Course->get_lecturer();
    //Check for already existing lecturer
    while(currptr!=nullptr){
        if(currptr->get_teacher()==lecturer){
            std::cout<<"This teacher is already conducting this course\n";
            return;
        }
        currptr=currptr->get_next();
    }
    //Add the lecturer

    currptr = Course->get_lecturer();

    while(currptr->get_next()!=nullptr){
        currptr=currptr->get_next();}

    currptr->set_next(new node_t(lecturer));
    //Add the course to the lecturer's list \/
    u3a::append_conduct(lecturer, Course);
                                                                      
}


void u3a::remove_lecturer(u3a::teacher* lecturer, u3a::course* Course){

    //check if exist
    node_t* currptr = Course->get_lecturer();
    bool check = 0;

    while(currptr!=nullptr){
        if(currptr->get_teacher()==lecturer){
            check = 1;
            currptr=nullptr;
            break;
        }
    currptr=currptr->get_next();
    }
    if(check==0){
        std::cerr<<"No such lecturer\n";
        return;
    }

    currptr = Course->get_lecturer();
    //Delete header
    if(currptr->get_teacher()==lecturer){
        Course->set_lecturer(currptr->get_next());
        return;
    }
    
    //Delete non-header
    while(currptr->get_next()!=nullptr){
        if(currptr->get_next()->get_teacher()==lecturer){
            currptr->set_next(currptr->get_next()->get_next());
            currptr=currptr->get_next();
            delete currptr;
            return;
        }
    currptr= currptr->get_next();
    }
    //Remove the course from teacher's list
    u3a::remove_conduct(lecturer,Course);
}

void u3a::course::set_lecturer(u3a::node_t* node){
    this->lecturer = node; return;
}


void u3a::remove_from_pHead_student(u3a::student* Student){
    //check if is in the stack
    if(Student==nullptr){std::cerr<<"Null student"; return;}
    bool check=0;
    node_s* currptr = this->pHead_student;
    
    while(currptr!=nullptr){
        if(currptr->get_student()==Student){
            check = 1;
        }
        currptr= currptr->get_next();
    }
    
    if(check==0){std::cerr<<"\nNo student found in the stack\n"; return;}
    currptr = this->pHead_student;
        //delete section
    //if header
    if(currptr->get_student() == Student){
        node_s* marker = this->pHead_student;
        this->pHead_student = this->pHead_student->get_next();
        delete marker;
        return;
    }
    
    //if not
    while(currptr!=nullptr){

        if(currptr->get_next()->get_student()==Student){
            node_s* marker = currptr->get_next();
            currptr->set_next(currptr->get_next()->get_next());
            delete marker;
            return;
        }

        currptr=currptr->get_next();
    }
}


void u3a::remove_from_pHead_teacher(u3a::teacher* Teacher){
   //check if is in the stack
   if(Teacher==nullptr){std::cerr<<"Null teacher"; return;}
   bool check=0;
   node_t* currptr = this->pHead_teacher;
   while(currptr!=nullptr){
       if(currptr->get_teacher()==Teacher){
           check = 1;
       }
       currptr= currptr->get_next();
   }
   if(check==0){std::cerr<<"\nNo teacher found in the stack\n"; return;}
   currptr = this->pHead_teacher;
       //delete section
   //if header
   if(currptr->get_teacher() == Teacher){
       node_t* marker = this->pHead_teacher;
       this->pHead_teacher = this->pHead_teacher->get_next();
       delete marker;
       return;
   }
   //if not
   
   while(currptr!=nullptr){
       if(currptr->get_next()->get_teacher()==Teacher){
           node_t* marker = currptr->get_next();
           currptr->set_next(currptr->get_next()->get_next());
           delete marker;
           return;
       }
    
    currptr=currptr->get_next();   
   }
}


void u3a::remove_from_pHead_course(u3a::course* Course){
   //check if is in the stack
   if(Course==nullptr){std::cerr<<"Null course"; return;}
   bool check=0;
   node_c* currptr = this->pHead_course;
   while(currptr!=nullptr){
       if(currptr->get_course()==Course){
           check = 1;
       }
       currptr= currptr->get_next();
   }
   if(check==0){std::cerr<<"\nNo course found in the stack\n"; return;}
   currptr = this->pHead_course;
       //delete section
   //if header
   if(currptr->get_course() == Course){
       node_c* marker = this->pHead_course;
       this->pHead_course = this->pHead_course->get_next();
       delete marker;
       return;
   }
   
   //if not
   while(currptr!=nullptr){
       if(currptr->get_next()->get_course()==Course){
           node_c* marker = currptr->get_next();
           currptr->set_next(currptr->get_next()->get_next());
           delete marker;
           return;
       }
    currptr= currptr->get_next();
    }

}



u3a::node_c* u3a::teacher::get_courses_conducted()
    {return this->courses_conducted_pHead;}


void u3a::teacher::set_courses_conducted(u3a::node_c* Course){this->courses_conducted_pHead = Course;}

//Note to myself: these 2 only work from teacher's POV, exactly the way i intended
void u3a::append_conduct(u3a::teacher* Teacher, u3a::course* Course){

    u3a::node_c* creation = new u3a::node_c(Course);

    if(Teacher->get_courses_conducted()==nullptr){ //if empty
        Teacher->set_courses_conducted(creation);
    }
    else{ //if not empty
        creation->set_next(Teacher->get_courses_conducted());
        Teacher->set_courses_conducted(creation);
    }
}

void u3a::remove_conduct(u3a::teacher* Teacher, u3a::course* Course){
    //check if exist
    node_c* currptr = Teacher->get_courses_conducted();
    bool check=0;
    while(currptr!=nullptr){

        if(currptr->get_course() == Course){
            check = 1;
            break;
        }
        currptr= currptr->get_next();
    }
    if(!check){std::cout<<"No course conducted by this teacher"; return;}

    //remove...
    node_c* marker;
    //if header
    if(Teacher->get_courses_conducted()->get_course()==Course){
        marker = Teacher->get_courses_conducted();
        Teacher->set_courses_conducted(Teacher->get_courses_conducted()->get_next());
        delete marker;
        return;
    }
    //if not
    currptr = Teacher->get_courses_conducted();
    while(currptr!=nullptr){
        if(currptr->get_next()->get_course()==Course){
            marker = currptr->get_next();
            currptr->set_next(currptr->get_next()->get_next());
            delete marker;
            return;
        }
    }
}


int u3a::does_teacher_conduct(u3a::teacher* Teacher, u3a::course* Course){

    node_t* currptr = Course->get_lecturer();
    while(currptr!=nullptr){
        if(currptr->get_teacher()==Teacher){return 1;}
        currptr=currptr->get_next();
    }
    return 0;
}


u3a::grouper::grouper(char* name){
    this->name = new char[strlen(name)+1]; 
    strcpy(this->name,name);
    this->next = nullptr;
    this->id=0;
    this->pHead=nullptr;
}

u3a::grouper::~grouper(){
    delete[] name;
}

bool u3a::in_stack(u3a::node_c* pHead, u3a::course* Course){

    node_c* currptr = pHead;
    while(currptr!=nullptr){
        if(currptr->get_course() == Course){return 1;}
        currptr = currptr->get_next();
    }
    return 0;
}

void u3a::remove_from_group(u3a::grouper* Grouper, u3a::course* Course){
    if(in_stack(Grouper->get_pHead(), Course)==0){std::cerr<<"No such course in the group\n";return;}
    
    node_c* currptr = Grouper->get_pHead();
    node_c* prevptr = currptr;
    if(currptr->get_course()==Course){
        Grouper->set_pHead(nullptr);
        delete currptr;
        return;
    }

    while(currptr!=nullptr){
        if(currptr->get_course() == Course){
            prevptr->set_next(currptr->get_next());
            delete currptr;
            return;
        }
        prevptr = currptr;
        currptr = currptr->get_next();
    }
}

void u3a::add_to_group(grouper* Grouper, course* Course){
    if(in_stack(Grouper->get_pHead(), Course)== 1){std::cerr<<"Course already in the group"; return;}
    node_c* currptr = Grouper->get_pHead();
    node_c* creation = new node_c(Course);

    if(currptr==nullptr){
        Grouper->set_pHead(creation);
    }

    while(currptr!=nullptr){
        if(currptr->get_next()==nullptr){
            currptr->set_next(creation);
            return;
        }
        currptr=currptr->get_next();
    }

}

char* u3a::grouper::get_name(){
    return this->name;
}

u3a::node_c* u3a::grouper::get_pHead(){return this->pHead;}

void u3a::grouper::set_pHead(node_c* node){this->pHead = node;}

void u3a::grouper::print_name(){std::cerr<<this->name;}

void u3a::grouper::set_next(grouper* Grouper){this->next = Grouper;}

u3a::grouper* u3a::grouper::get_next(){return this->next;}

u3a::grouper* u3a::get_pHead_grouper(){return this->pHead_grouper;}

void u3a::set_pHead_grouper(grouper* Grouper){
    this->pHead_grouper = Grouper;
}

int u3a::grouper::get_id(){return this->id;}

void u3a::grouper::set_id(int id){this->id = id;}

u3a::unexpectedIdException::unexpectedIdException(int line){
    this->line = line;
}

u3a::notFoundException::notFoundException(int line){
    this->line = line;
}

u3a::somethingWentWrong::somethingWentWrong(char* message){
    this->message = new char[strlen(message)+1];
    this->message = message;
}

u3a::AlreadyAddedException::AlreadyAddedException(){}



void u3a::append_group(u3a::grouper* newgroup){

    newgroup->set_id(lowest_nontaken_id_grouper());

    if(pHead_grouper==nullptr)
    {
        set_pHead_grouper(newgroup);
        return;
    }

    grouper* currptr = pHead_grouper;
    grouper* prevptr= currptr;
    
    while(currptr!=nullptr){
        prevptr = currptr;
        currptr = currptr->get_next();
    }
    
    if(currptr==nullptr){
        prevptr->set_next(newgroup);
        return;
    }

}

int u3a::lowest_nontaken_id_grouper(){
    int potential_id = 0;
    bool pass = 0;

    if(this->pHead_grouper==nullptr){return 0;}

    while(pass!=1){
        pass = 1;
        u3a::grouper* currptr = this->pHead_grouper;
        while(currptr!=nullptr){
            if(potential_id==currptr->get_id()){pass=0; potential_id=potential_id+1;}
            currptr=currptr->get_next();
        }
    }
    return potential_id;

}

u3a::grouper* u3a::findGroupById(int id){

    grouper* find = pHead_grouper;
    while(find!=nullptr){
        if(find->get_id() == id){
            return find;
        }
    find = find->get_next();
    }
    return nullptr; //not found
}


void u3a::course::set_status(int status){
    this->status = status;
}

int u3a::course::get_status(){
    return status;
}

u3a::course* u3a::classroom::get(int i){
    return this->free[i];
}

void u3a::classroom::set(int i, course* newvalue){
    this->free[i] = newvalue;
}

void u3a::classroom::set_next(classroom* cr){ this->next = cr;}

u3a::classroom* u3a::classroom::get_next(){return this->next;}

u3a::classroom::classroom(int id2){
for(int i=0;i!=240;i++){
    this->free[i] = nullptr; 
}
this->id = id2;
this->next = nullptr;
}

u3a::classroom::~classroom(){}


int u3a::check_if_free(u3a::classroom* cr, int index, int duration){ //1 if free
    for(int i=0;i!=duration;i++){
        if(i+index>=240){return 1;}
        if(cr->get(i+index)!=nullptr){return 0;}
    }
    return 1;
}

void u3a::take_up(u3a::classroom* cr, int index, int duration, course* c){
    for(int i=0;i!=duration;i++){
        if(i+index>=240){return;}
        cr->set(i+index, c);
    }
    log(combine_strings(combine_strings("Reserved time in a classroom (",cr->get_id(),") for a course ("),c->get_id(),")"));
}

int u3a::classroom::get_id(){
    return this->id;
}

int u3a::lowest_nontaken_id_classroom(){
    int potential_id = 0;
    bool pass = 0;

    if(this->pHead_classroom==nullptr){return 0;}

    while(pass!=1){
        pass = 1;
        u3a::classroom* currptr = this->pHead_classroom;
        while(currptr!=nullptr){
            if(potential_id==currptr->get_id()){pass=0; potential_id=potential_id+1;}
            currptr=currptr->get_next();
        }
    }
    return potential_id;

}

int u3a::check_if_cr_exist(int number){

    u3a::classroom* currptr = get_pHead_classroom();
    while(currptr!=nullptr){
        if(currptr->get_id()==number) return 1;
        currptr=currptr->get_next();
    }
    return 0;
}

u3a::classroom* u3a::findCrById(int number){

    u3a::classroom* currptr = get_pHead_classroom();
    while(currptr!=nullptr){
        if(currptr->get_id()==number) return currptr;
        currptr=currptr->get_next();
    }
    return nullptr;

}


void u3a::append_classroom(){

    classroom* ptr = this->pHead_classroom;
    
    classroom* creation = new classroom(lowest_nontaken_id_classroom());
    log(combine_strings("Created a classroom (id:",creation->get_id(),")"));
    if(ptr==nullptr){
        this->pHead_classroom = creation;
        return;
    }

    while(ptr!=nullptr){
        if(ptr->get_next()==nullptr){
            ptr->set_next(creation);
            return;
        }
        ptr=ptr->get_next();
    }
    
}

void u3a::set_pHead_classroom(u3a::classroom* cr){
    this->pHead_classroom = cr;
}
u3a::unexpectedTimeException::unexpectedTimeException(int parameter){this->i = parameter;}

u3a::classroom* u3a::get_pHead_classroom(){return this->pHead_classroom;}


u3a::node_c* u3a::student::get_completed(){
    return this->completed_pHead;
}

void u3a::student::set_completed(u3a::node_c* newc){
    this->completed_pHead = newc;
}

void u3a::complete(u3a::student* stud, u3a::course* c){
    node_c* creation = new node_c(c);
    c->set_status(1);
    node_c* currptr;

    if(stud->get_completed()==nullptr){
        stud->set_completed(creation);
    }
    else{
        currptr = stud->get_completed();
        while(currptr!=nullptr){
            if(currptr->get_next()==nullptr){
                currptr->set_next(creation);
                break;
            }
        currptr=currptr->get_next();
        }
    }
    
    //delete course from students courses

    node_c* prevptr = stud->get_courses();
    currptr=prevptr;

    if(currptr->get_course()==c){
        stud->set_courses(currptr->get_next());
        return;
    }

    while(currptr!=nullptr){
        if(currptr->get_course()==c){
            prevptr->set_next(currptr->get_next());
            delete currptr;
            return;
        }
        prevptr=currptr;
        currptr=currptr->get_next();
    }
    
}

u3a::node_c* u3a::teacher::get_completed(){return this->completed;}

void u3a::teacher::set_completed(u3a::node_c* comp){this->completed = comp;}

void u3a::complete(u3a::teacher* tea, u3a::course* c){

    node_c* creation = new node_c(c);
    c->set_status(1);


    if(tea->get_completed()==nullptr){
        tea->set_completed(creation);
    }
    else{
        node_c* currptr = tea->get_completed();
        while(true){
            if(currptr->get_next()==nullptr){
                currptr->set_next(creation);
                break;
            }
        }
    }

    node_c* marker;
    if(tea->get_courses_conducted()->get_course()==c){
        marker = tea->get_courses_conducted();
        tea->set_courses_conducted(tea->get_courses_conducted()->get_next());
        delete marker;
        return;
    }
    else{
        node_c* cp1 = tea->get_courses_conducted(); 
        node_c* pp1 = cp1;

        while(true){

            if(cp1==nullptr){
                pp1->set_next(cp1->get_next());
                delete cp1;
                return;
            }

            pp1=cp1;
            cp1=cp1->get_next();
        }
    }
}
u3a::datalog* u3a::get_pHead_datalog(){
    return this->pHead_datalog;
}

u3a::datalog::datalog(const char* info){
    this->next = nullptr;
    this->message = new char[strlen(info)+1];
    strcpy(this->message, info);
}
u3a::datalog::~datalog(){
    delete this->message;
}

char* u3a::datalog::get_message(){
    return this->message;
}

u3a::datalog* u3a::datalog::get_next(){
    return this->next;
}
void u3a::datalog::set_next(datalog* dt){
    this->next = dt;
}



char* combine_strings(const char* str1, int num, const char* str2) {
    if (!str1) str1 = "";
    if (!str2) str2 = "";
    
    int len=snprintf(nullptr,0,"%s %d %s",str1,num,str2);
    if(len<0) return nullptr;
    char* buffer = new char[len+1];
    snprintf(buffer,len+1,"%s %d %s",str1,num,str2);
    return buffer;
}


void u3a::log(const char* info){
    datalog* cp = this->get_pHead_datalog();
    while(true){
      if(cp->get_next()==nullptr){
        cp->set_next(new datalog(info));
        return;
      }
      cp=cp->get_next();
    }
}

//take_up