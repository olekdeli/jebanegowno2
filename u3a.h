#pragma once
#include <iostream>
#include <cstring>
#include <limits>
#include <fstream> 

class u3a //University of third age = u3a
{
public:

    u3a();

class course; 
class student;
class teacher;
class node_s;
class node_t;
class node_c;
class grouper;
class classroom;
// Forward Declarations

node_s* node_of(student* Student);
node_t* node_of(teacher* Teacher);
node_c* node_of(course* Course);

void add_pHeadStudent(node_s* Student);
void add_pHeadStudent(student* Student); 

void add_pHeadTeacher(teacher* Teacher);
void add_pHeadTeacher(node_t* Teacher);

void add_pHeadCourse(node_c* Course);
void add_pHeadCourse(course* Course);
// Sets given object as a pHead_... and sets previous pHead->next as the given object

student* new_student(int id, int age, char* name);
course* new_course(int id, char* name, teacher* lecturer, int capacity);
teacher* new_teacher(int id, char* teacher_name);
// Creates a new_... with given parameters. 
// Automatically adds new object to the pHead lists
// Returns pointer to the new object.

node_c* findCourseById(int id);
// Returns a pointer to the course of the given id 
// If 2 same Id's found will give the oldest one

node_t* findTeacherById(int id);
// Returns a pointer to the teacher of the given id 
// If 2 same Id's found will give the oldest one

node_s* findStudById(int id);
// Returns a pointer to the student cell of the given id 
// If 2 same Id's found will give the oldest one


student* insert_new_student(int age, char* name);
teacher* insert_new_teacher(char* name);
course* insert_new_course(char* name, int lecturer_id,int capacity);
//"Insert_new_..." functions does the same things as "new_..." functions, but the id of an object
//is automatically assigned according to the "Smallest non-taken id" rule.
//Returns pointer to the newly constructed object

int course_in_course_stack_check(course* Course);
//Returns 1 if course "course" is in the stack of courses

int does_student_attend(student* Student, course* Course);
void pop_student_from_course_list(student* Student,course* Course);
void pop_course_from_student_list(course* Course, student* Student);

void append_student(course* Course, student* Student);

void enroll_student(int id, course* Course);
//Adds a student to a course list
void deroll_student(int id, course* Course);
//Removes a student from a course list
void append_course(student* Student, course* Course);

void add_lecturer(teacher* lecturer, course* Course);
void remove_lecturer(teacher* lecturer, course* Course);
void complete(student* stud, course* c);
void complete(teacher* tea, course* c);
//Derolls a student (only from stud pov) but appends the course to the completed
        

    class student{
    public:
        student(int id, int age, char* name);
        //Constructor of a student object
        ~student();
        //Deconstructor of a student object
        int get_id();
        //Returns id of the student object
        int get_age();
        //Returns age of the student object
        char* get_name();
        //Returns name of the student object
        void print_student();
        //Prints student info
        node_c* get_courses();
        //Returns courses pHead
        void set_courses(node_c* link);
        //Sets "courses" value

        node_c* get_completed();
        void set_completed(node_c* newc);

    private:
        node_c* completed_pHead;
        node_c* courses;
        int id_student;
        int age;
        char* name; 

        friend class course;
    };


    class teacher{
    public:
        teacher(int id, char* teacher_name);
        ~teacher();
        int get_id();
        char* get_name();
        void print_teacher();
        node_c* get_courses_conducted();
        //Returns pHead to the first node_t of the courses conducted
        void set_courses_conducted(node_c* Course);
        node_c* get_completed();
        void set_completed(node_c* comp);
    private:
        node_c* completed;
        int id_teacher;
        char* teacher_name;
        node_c* courses_conducted_pHead;
        friend class course;
    };


    class course{
    public:
        course(int id, char* name, teacher* lecturer, int capacity);
        ~course();
        int get_id();
        //Returns id
        char* get_name();
        //Returns name
        node_s* get_studentPHead();
        //Returns pointer head of the student list
        void set_studentPHead(node_s* node);
        void set_studentPHead_next(node_s* node);
        node_t* get_lecturer();
        void set_lecturer(node_t* node);
        //Returns pointer to a teacher conducting the course
        void print_course();
        int get_capacity();

        int get_student_count();
        void set_student_count(int count);

        void print_all_lecturers();
        int get_status();
        void set_status(int status);
        void print_student_list();
    private:
        int status;
        int id_course;
        char* course_name;
        node_s* student_list;
        node_t* lecturer;
        int capacity;
        int student_count;
    };

    node_s* get_pHead_student();
    node_t* get_pHead_teacher();
    node_c* get_pHead_course();
    //Returns pointer to the corresponding pHead 

    void set_pHead_student(student* Student);
    void set_pHead_teacher(teacher* Teacher);
    void set_pHead_course(course* Course);
    //Sets the corresponding pHead to the given pointer

    void remove_from_pHead_student(student* Student);
    void remove_from_pHead_teacher(teacher* Teacher);
    void remove_from_pHead_course(course* Course);


    class node_s{
        public:
            node_s(student* Student);
            ~node_s();
            node_s* get_next();
            student* get_student();
            void print_student();
            void set_next(node_s* next);
            void set_student(student* Student);
            int get_id();
            void print_all();
        private:
            student* Student;
            node_s* next;
    };

    void set_next(u3a::student* Student, u3a::student* target);
    void set_next(u3a::student* Student, u3a::node_s* target);

    class node_t{
        public:
            node_t(teacher* Teacher);
            ~node_t();
            node_t* get_next();
            teacher* get_teacher();
            void print_all();
            void print_teacher();
            void set_next(node_t* node);
            void set_teacher(teacher* Teacher);
            int get_id();
        private:
            teacher* Teacher;
            node_t* next;
    };
    void set_next(u3a::teacher* Teacher, u3a::teacher* target);
    void set_next(u3a::teacher* Teacher, u3a::node_t* target);

    class node_c{
        public:
            node_c(course* Course);
            ~node_c();
            node_c* get_next();
            course* get_course();
            void print_all();
            void print_course();
            void set_next(node_c* node);
            void set_course(course* Course);
            int get_id();
        private:
            course* Course;
            node_c* next;
    };

    class grouper{
        public:
                grouper(char* name);
                ~grouper();
                u3a::node_c* get_pHead();
                void set_pHead(node_c* node);
                void print_name();
                void set_next(grouper* Grouper);
                u3a::grouper* get_next();
                char* get_name();
                int get_id();
                void set_id(int id);
            private:
                char* name;
                node_c* pHead;
                grouper* next;
                int id;
        };
    int lowest_nontaken_id_grouper();
    void remove_from_group(grouper* Grouper, course* Course);
    void add_to_group(grouper* Grouper, course* Course);
    grouper* get_pHead_grouper();
    void set_pHead_grouper(grouper* Grouper);
    bool in_stack(node_c* pHead, course* Course);
    void append_group(grouper* group);

    class unexpectedIdException{
        public: unexpectedIdException(int line);
        int line;
    };

    class AlreadyAddedException{
        public: AlreadyAddedException();
    };
    class notFoundException{
        public: notFoundException(int line);
        int line;
    };

    class somethingWentWrong{
        public: somethingWentWrong(char* message);
        char* message;
    };
    class unexpectedTimeException{
        public: unexpectedTimeException(int parameter);
        int i;
    };
    
    void set_next(u3a::course* Course, u3a::course* target);
    void set_next(u3a::course* Course, u3a::node_c* target);
    
    void append_conduct(teacher* Teacher, course* Course);
    void remove_conduct(teacher* Teacher, course* Course);
    int does_teacher_conduct(teacher* Teacher, course* Course);
    grouper* findGroupById(int id);

    class classroom{
        public:
            classroom(int id2);
            ~classroom();
            void set(int i, course* newvalue);
            course* get(int i);
            void set_next(classroom* cr);
            classroom* get_next();
            int get_id();
        private:
            int id;
            classroom* next;
            course* free[240]; //From 8:00 to 20:00 every 15 min

    };
    void append_classroom();
    int check_if_free(u3a::classroom* cr, int index, int duration); //(in quadrants)
    void take_up(u3a::classroom* cr, int index, int duration, u3a::course* c);
    int lowest_nontaken_id_classroom();
    int check_if_cr_exist(int number);
    u3a::classroom* findCrById(int number);
    void set_pHead_classroom(classroom* cr);

    class datalog{
        public:
            datalog(const char* info);
            ~datalog();
            char* get_message();
            datalog* get_next();
            void set_next(datalog* dt);
        private:
            datalog* next;
            char* message;
    };
    void log(const char* info);

    u3a::datalog* get_pHead_datalog();

    void find_and_delete(u3a::course* Course);

    u3a::classroom* get_pHead_classroom();
    private:

    datalog* pHead_datalog;
    node_s* pHead_student;
    node_t* pHead_teacher;
    node_c* pHead_course;
    grouper* pHead_grouper;
    classroom* pHead_classroom;
};


char* combine_strings(const char* str1, int num, const char* str2);
int ask_int();
char* ask_str();
void cleanscreen();
void remove_from_group(u3a::grouper* Grouper, u3a::course* Course);
int operating_system();
void sys_break();

void export_to_file();
