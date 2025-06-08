#include "u3a.h"
using namespace std;

int main(){
cleanscreen();
u3a *uni= new u3a();

char name1[] = "abc";
char name2[] = "def";
char name3[] = "hij";

//Adding and testing students
    u3a::student* student1 = uni ->insert_new_student(81,name1);
    u3a::student* student2 = uni ->insert_new_student(82,name2);
    u3a::student* student3 = uni ->insert_new_student(83,name3);
    if(student1->get_id()!=0 || student2->get_id()!=1 || student3->get_id()!=2) cerr<<"\nError in student id assigment\n";
    if(strcmp(student1->get_name(),name1)) cerr<<"Error in student name assigment\n";

//Adding and testing teachers
    u3a::teacher* teacher1 = uni->insert_new_teacher(name1);
    u3a::teacher* teacher2 = uni->insert_new_teacher(name2);
    u3a::teacher* teacher3 = uni->insert_new_teacher(name3);
    if(teacher1->get_id() != 0 || teacher2->get_id() != 1 || teacher3->get_id() != 2) cerr<<"\nError in teacher id assigment\n";
    if(strcmp(teacher1->get_name(),name1)) cerr<<"Error in teacher name assigment\n";

//Adding and testing courses
    u3a::course* course1 = uni->insert_new_course(name1,0,5);
    u3a::course* course2 = uni->insert_new_course(name1,0,5);
    u3a::course* course3 = uni->insert_new_course(name1,1,5);
    if(course1->get_id()!=0 || course2->get_id()!=1 || course3->get_id()!=2) cerr<<"\nError in course id assigment\n";
    if(strcmp(course1->get_name(),name1)) cerr<<"Error in course name assigment\n";

    //Now 3 students, teachers, and courses are added

//Testing Finder functons and node functions (used by other methods)
    if(uni->findStudById(0)!=uni->node_of(student1)) cerr<<"\nError in finding a student by id\n";
    if(uni->findStudById(1)!=uni->node_of(student2)) cerr<<"\nError in finding a student by id\n";
    if(uni->findTeacherById(1)!=uni->node_of(teacher2)) cerr<<"\nError in finding a teacher by id\n";
    if(uni->findTeacherById(2)!=uni->node_of(teacher3)) cerr<<"\nError in finding a teacher by id\n";
    if(uni->findCourseById(2)!=uni->node_of(course3)) cerr<<"\nError in finding a course by id\n";
    if(uni->findCourseById(0)!=uni->node_of(course1)) cerr<<"\nError in finding a course by id\n";

//Testing Enroll function
    uni->enroll_student(0, course1);
    uni->enroll_student(0, course2);
    uni->enroll_student(0, course3);
    uni->enroll_student(1, course1);

    //Now student1 should be attending 3 courses, and student 2 should be attending 1

    if(student1->get_courses()->get_course() != course3)             cerr<<"\nError in enrolling to a course (first course)\n";
    if(student1->get_courses()->get_next()->get_course() != course2)       cerr<<"\nError in enrolling to a course (second course)\n";
    if(student1->get_courses()->get_next()->get_next()->get_course() != course1) cerr<<"\nError in enrolling to a course (third course)\n";
    if(student1->get_courses()->get_next()->get_next()->get_next() != nullptr) cerr<<"Last course doesn't point to a nullptr (student1)\n";
    if(student2->get_courses()->get_course()!= course1) cerr<<"Error in enrolling to a course (student2)\n";
    if(student2->get_courses()->get_next()!=nullptr) cerr<<"Last course doesn't point to a nullptr (student2)";
    if(course1->get_student_count()!=2)                                     cerr<<"\nError in counting students attending the course";
    
//Edge-testing the enroll function

    //Enrolling into non-existent course
    std::cerr<<"An error should be now printed:";
    uni->enroll_student(0, nullptr); //Should print an error
    std::cerr<<"\n";

    //Testing the does_student_attend function
    if(uni->does_student_attend(uni->findStudById(0)->get_student(),course1)!=1) cerr<<"\nError in does_student_attend() function\n";

    //Enrolling a student to the same course twice
    cerr<<"An error should be now printed:";
    uni->enroll_student(0,course1);

    //Checking student counter
    if(course1->get_student_count()!=2)cerr<<"\nError in counting students attending the course";
    
    //Enrolling into a full course
    
    uni->insert_new_student(20,name1);
    uni->insert_new_teacher(name1);
    u3a::course* c3 = uni->insert_new_course(name1,3,1);
    
    uni->enroll_student(3,c3);
    cerr<<"\nAn error should be now printed:";
    uni->enroll_student(0,c3);

    //Check if edge-testing the enroll fuction changed enrollment situation (it shouldn't)
    if(student1->get_courses()->get_course() != course3)             cerr<<"\nError in enrolling to a course (first course) (post edge-testing)\n";
    if(student1->get_courses()->get_next()->get_course() != course2)       cerr<<"\nError in enrolling to a course (second course) (post edge-testing)\n";
    if(student1->get_courses()->get_next()->get_next()->get_course() != course1) cerr<<"\nError in enrolling to a course (third course) (post edge-testing)\n";
    if(student1->get_courses()->get_next()->get_next()->get_next() != nullptr) cerr<<"Last course doesn't point to a nullptr (student1) (post edge-testing)\n";


//Removing a student from a course section:

//Removing a student from a course (edge-testing)

    // Removing a non-existing student from a course
    cerr<<"\nAn error should be now printed:";
    uni->deroll_student(999,course1); //No such student

    //Removing a student from a non-existing course
    cerr<<"\nAn error should be now printed:"; 
    uni->deroll_student(0,nullptr); //No such course

    //Removing a student from a course he's not attending
    cerr<<"\nAn error should be now printed:";
    uni->deroll_student(2,course1); //Student is not attending the course

    //Nothing should change in the enrollment situation
    if(student1->get_courses()->get_course() != course3)             cerr<<"\nError in enrolling to a course (first course) (post removal edge-testing)\n";
    if(student1->get_courses()->get_next()->get_course() != course2)       cerr<<"\nError in enrolling to a course (second course) (post removal edge-testing)\n";
    if(student1->get_courses()->get_next()->get_next()->get_course() != course1) cerr<<"\nError in enrolling to a course (third course) (post removal edge-testing)\n";
    if(student1->get_courses()->get_next()->get_next()->get_next() != nullptr) cerr<<"Last course doesn't point to a nullptr (student1) (post removal edge-testing)\n";

//Removing every student from every course

    uni->deroll_student(0,course1);
    uni->deroll_student(0,course2);
    uni->deroll_student(0,course3);
    uni->deroll_student(1,course1); 

    if(student1->get_courses()!=nullptr) cerr<<"\nStudents 1 should not be a part of any courses\n";
    if(student2->get_courses()!=nullptr) cerr<<"\nStudents 2 should not be a part of any courses\n";
    if(student3->get_courses()!=nullptr) cerr<<"\nStudents 3 should not be a part of any courses\n";
    if(course1->get_studentPHead()!=nullptr) cerr<<"\nCourse 1 should not contain any students\n";
    if(course2->get_studentPHead()!=nullptr) cerr<<"\nCourse 2 should not contain any students\n";
    if(course3->get_studentPHead()!=nullptr) cerr<<"\nCourse 3 should not contain any students\n";

    //Removing the first student from a course
    uni->enroll_student(0,course1);
    uni->enroll_student(1,course1);
    uni->enroll_student(2,course1);

    uni->deroll_student(0,course1);

    uni->deroll_student(1,course1);
    uni->deroll_student(2,course1);

    //Removing a middle student from a course
    uni->enroll_student(0,course1);
    uni->enroll_student(1,course1);
    uni->enroll_student(2,course1);

    uni->deroll_student(1,course1);

    if(student1->get_courses()->get_next()!=nullptr) cerr<<"\nError in removing a student from a course (deleting a middle student)1";
    if(student2->get_courses()!=nullptr) cerr<<"\nError in removing a student from a course (deleting a middle student)2";
    if(student3->get_courses()->get_next()!=nullptr) cerr<<"\nError in removing a student from a course (deleting a middle student)3";
  
    uni->deroll_student(0,course1);
    uni->deroll_student(2,course1);
    
    if(student1->get_courses()!=nullptr) cerr<<"\nStudents 1 should not be a part of any courses\n";
    if(student2->get_courses()!=nullptr) cerr<<"\nStudents 2 should not be a part of any courses\n";
    if(student3->get_courses()!=nullptr) cerr<<"\nStudents 3 should not be a part of any courses\n";
    if(course1->get_studentPHead()!=nullptr) cerr<<"\nCourse 1 should not contain any students\n";
    if(course2->get_studentPHead()!=nullptr) cerr<<"\nCourse 2 should not contain any students\n";
    if(course3->get_studentPHead()!=nullptr) cerr<<"\nCourse 3 should not contain any students\n";

    uni->enroll_student(0,course1);
    uni->enroll_student(1,course1);
    uni->enroll_student(2,course1);

    //Removing the last student in the stack
    uni->deroll_student(2,course1);
      
    if(student1->get_courses()->get_next()!=nullptr) cerr<<"\nError in removing a student from a course (deleting a middle student)1";
    if(student2->get_courses()->get_next()!=nullptr) cerr<<"\nError in removing a student from a course (deleting a middle student)2";
    if(student3->get_courses()!=nullptr) cerr<<"\nError in removing a student from a course (deleting a middle student)3";
    if(course1->get_studentPHead()->get_student()!=student2) cerr<<"\nError in removing a course from a student's list (first course)\n";
    if(course2->get_studentPHead()!=nullptr) cerr<<"\nError in removing a course from a student's list (second course)\n";
    if(course3->get_studentPHead()!=nullptr) cerr<<"\nError in removing a course from a student's list (third course)\n";
    
    uni->deroll_student(1,course1);
    uni->deroll_student(0,course1);

    if(student1->get_courses()!=nullptr) cerr<<"\nStudents 1 should not be a part of any courses\n";
    if(student2->get_courses()!=nullptr) cerr<<"\nStudents 2 should not be a part of any courses\n";
    if(student3->get_courses()!=nullptr) cerr<<"\nStudents 3 should not be a part of any courses\n";
    if(course1->get_studentPHead()!=nullptr) cerr<<"\nCourse 1 should not contain any students\n";
    if(course2->get_studentPHead()!=nullptr) cerr<<"\nCourse 2 should not contain any students\n";
    if(course3->get_studentPHead()!=nullptr) cerr<<"\nCourse 3 should not contain any students\n";

// End of removing test section

//Testing add/remove/etc._lecturer
    //Edge test
    if(course1->get_lecturer()->get_next()!=nullptr) cerr<<"\nSomething went wrong with the course structure (line 181 of test file)";
    cerr<<"\nAn error should be now printed:";
    uni->u3a::add_lecturer(teacher1, course1);
    if(course1->get_lecturer()->get_next()!=nullptr) cerr<<"\nError, already existing lecturer should not be added\n";
    //Adding
    uni->u3a::add_lecturer(teacher2, course1);
    if(course1->get_lecturer()->get_next()->get_teacher()!=teacher2) cerr<<"\nError in add_lecturer()\n";
    //Removing non-conducting lecturer
    cerr<<"An error should be now printed:";
    uni->u3a::remove_lecturer(teacher3, course1);

    //Removing a lecturer
    uni->u3a::remove_lecturer(teacher2, course1);
    if(course1->get_lecturer()->get_next()!=nullptr) cerr<<"\nError in remove_lecturer()\n";
    if(course1->get_lecturer()->get_teacher()!=teacher1) cerr<<"\nError in remove_lecturer()\n";

//Testing removal from the stack (student)
    //Header removal
        uni->remove_from_pHead_student(uni->findStudById(3)->get_student());
        if(uni->get_pHead_student()->get_student()!=student3) cerr<<"Error in student stack removal (header)";
    //non-header removal
        uni->remove_from_pHead_student(uni->findStudById(1)->get_student());
        if(uni->get_pHead_student()->get_student()!=student3) cerr<<"Error in student stack removal (header changed)";
        if(uni->get_pHead_student()->get_next()->get_student()!=student1) cerr<<"Error in student stack removal";

//Testing removal from the stack (teacher)
    //Header removal
        uni->remove_from_pHead_teacher(uni->findTeacherById(3)->get_teacher());
        if(uni->get_pHead_teacher()->get_teacher()!=teacher3) cerr<<"Error in teacher stack removal (header)";
    //Non-header removal
        uni->remove_from_pHead_teacher(uni->findTeacherById(1)->get_teacher());
        if(uni->get_pHead_teacher()->get_teacher()!=teacher3) cerr<<"Error in teacher stack removal (header changed)";
        if(uni->get_pHead_teacher()->get_next()->get_teacher()!=teacher1) cerr<<"Error in teacher stack removal";

//Testing removal from the stack (course)
    //Header removal
        uni->remove_from_pHead_course(uni->findCourseById(3)->get_course());
        if(uni->get_pHead_course()->get_course()!=course3) cerr<<"Error in course stack removal (header)";
    //Non-header removal
        uni->remove_from_pHead_course(uni->findCourseById(1)->get_course());
        if(uni->get_pHead_course()->get_course()!=course3) cerr<<"Error in teacher stack removal (header changed)";
        if(uni->get_pHead_course()->get_next()->get_course()!=course1) cerr<<"Error in teacher stack removal";

//Testing append course conducted from teacher's structure
    //Teachers POV
        uni->append_conduct(teacher1,course1);
        if(teacher1->get_courses_conducted()->get_course()!=course1) cerr<<"Error in append_conduct (header)";
        uni->append_conduct(teacher1,course3);
        if(teacher1->get_courses_conducted()->get_course()!=course3) cerr<<"Error in append_conduct (non-header)";
        if(teacher1->get_courses_conducted()->get_next()->get_course()!=course1) cerr<<"Error in append_conduct (non-header)";

//Testing remove course conducted from teacher's structure
    uni->remove_conduct(teacher1,course3);
    if(teacher1->get_courses_conducted()->get_course()!=course1) cerr<<"Error in remove_conduct (header)";
    uni->remove_conduct(teacher1,course1);
    if(teacher1->get_courses_conducted()!=nullptr) cerr<<"Error in remove_conduct (last element)";
        //check differenet edge cases
    uni->append_conduct(teacher1,course1);
    uni->append_conduct(teacher1,course3);
    uni->remove_conduct(teacher1,course1);
    if(teacher1->get_courses_conducted()->get_course()!=course3) cerr<<"Error in edge case remove_conduct";
    uni->remove_conduct(teacher1,course3);
    if(teacher1->get_courses_conducted()!=nullptr) cerr<<"Error in edge case remove_conduct(last element)";
//Testing grouper funciton
    try{
        u3a::grouper* newgroup = new u3a::grouper(name1);
        uni->append_group(newgroup);
        if(newgroup->get_id() != 0) {throw u3a::unexpectedIdException(258);}

        u3a::grouper* newgroup1 = new u3a::grouper(name1);
        uni->append_group(newgroup1);
        if(newgroup1->get_id()!= 1) {throw u3a::unexpectedIdException(260);}

        u3a::grouper* newgroup2 = new u3a::grouper(name1);
        uni->append_group(newgroup2);
        if(newgroup2->get_id()!= 2) {throw u3a::unexpectedIdException(260);}

        u3a::grouper* newgroup3 = new u3a::grouper(name1);
        uni->append_group(newgroup3);
        if(newgroup3->get_id()!= 3) {throw u3a::unexpectedIdException(262);}

        if(newgroup!= uni->findGroupById(0))throw u3a::notFoundException(271);
        if(newgroup2!=uni->findGroupById(2)) throw u3a::notFoundException(272);
    }


    catch(u3a::unexpectedIdException& e){cerr<<"Unexpected Id Exception at "<<e.line<<"\n";}
    catch(u3a::notFoundException& e){cerr<<"findGroupByID didn't work properly at line"<<e.line<<"\n";}



std::cerr<<"\n\nEnd of tests\n\n";
}
