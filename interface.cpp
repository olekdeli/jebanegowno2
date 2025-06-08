#include "u3a.h"

int main(){

    u3a *uni= new u3a();

int choice1;
int choice2;

    while(true){ //PROGRAM LOOP

    cleanscreen();
std::cerr<<"University of the Third Age interface\nBy: Aleksander Jedrzejowski 336970\n\nChoose:\n";
std::cerr<<"1.Add a new (student/teacher/course)\n2.(Enroll/Deroll) a student into/from a course\n3.Check (student/teacher/course) list\n4.Check student's courses\n5.Print details about a (student/teacher/course)\n";
std::cerr<<"6.Delete a (student/teacher/course)\n7.Connect courses as the same subject/group, but differenet instance of the group\n";
std::cerr<<"8.(Add/Remove) a lecturer (to/from) a course\n";
std::cerr<<"9.Print student list of a course\n";
std::cerr<<"10.Add a timetable and a classroom to an instance of a course\n";
std::cerr<<"11.Mark a course as finished\n"; 
std::cerr<<"12.Check history of a (student/teacher/course)\n"; 
//std::cerr<<"97.Save current database into txt file (in development)\n98.Import data from the txt file (in development)\n";
std::cerr<<"0./Exit the programme\n";

std::cerr<<"\n->";

choice1 = ask_int();
switch(choice1){
case 0:{cleanscreen(); std::cerr<<"Thank you\n\n\n"; return 1;} //Working 
case 1:{
    std::cerr<<"Add a...\n1.Student\n2.Teacher\n3.Course\n0.Return\n->";
    choice2 = ask_int();
    
    if(choice2==0){break;}
    if(choice2==1){ //A student
        std::cerr<<"Input student's age\n->"; 
        int age =ask_int();
        if(age<=6 || age>99){
            std::cerr<<"Invalid age\n";
        }
        else
        {
            std::cerr<<"Input student's name\n->";
            uni->insert_new_student(age,ask_str());
        }
    }
    if(choice2==2){ //A teacher
        
        std::cerr<<"Input teacher's name\n->";
        char* name = ask_str();
        uni->insert_new_teacher(name);
    }


    if(choice2==3){ //A course
        std::cerr<<"Input course's name\n->";
        char* name = ask_str();
        std::cerr<<"Input lecturer's id\n->";
        int id_l = ask_int();

        std::cerr<<"Input course capacity\n->";
        int capacity = ask_int();
        if(capacity<1){std::cerr<<"Invalid age\n"; sys_break(); break;}

        if(uni->findTeacherById(id_l)==nullptr){
            std::cerr<<"No such lecturer with the given id... Aborting\n\n\n";
            sys_break();
        break;
        }
        else{
        uni->append_conduct(uni->findTeacherById(id_l)->get_teacher(),uni->insert_new_course(name, id_l, capacity));
        } 
    }
    sys_break();
    break;
}            

case 2:{
    std::cerr<<"\nPick:\n1.Enroll\n2.Deroll\n0./Return\n->";
    int choice2= ask_int();

    if(choice2==0){break;}

    std::cerr<<"Provide id of a student\n->";
    int id_s=ask_int(); 
    std::cerr<<"Input id of the course\n->";
    int id_c=ask_int();

    if(uni->findStudById(id_s)==nullptr && uni->findCourseById(id_c)==nullptr){
        std::cerr<<"No course nor student with given id...\n";
        sys_break();
        break;
    }

    if(uni->findStudById(id_s)==nullptr){
        std::cerr<<"No such student with given id\n";
        sys_break();
        break;
    }
    if(uni->findCourseById(id_c)==nullptr){
        std::cerr<<"Non-existient course\n"; 
        sys_break();
        break;
    }

    if(uni->findCourseById(id_c)->get_course()->get_status()==1){std::cerr<<"Course has already finished. Modification forbidden\n"; sys_break(); break;}

    if(choice2==1){

        if(uni->does_student_attend(uni->findStudById(id_s)->get_student(),uni->findCourseById(id_c)->get_course()) ==1){
            std::cerr<<"\nStudent is already enrolled in this course\n";
            sys_break();
            break;
        }
        uni->enroll_student(id_s,uni->findCourseById(id_c)->get_course());
    }

    if(choice2==2){
        if(uni->does_student_attend(uni->findStudById(id_s)->get_student(),uni->findCourseById(id_c)->get_course()) ==0){
            std::cerr<<"\nStudent is not attending the course\n";
            sys_break();
            break;
        }

        uni->deroll_student(id_s,uni->findCourseById(id_c)->get_course());
    }
    sys_break();
    break;
}

case 3:{
    std::cerr<<"Print list of ...\n1.Students\n2.Teachers\n3.Courses\n0./Return\n->";
    choice2 = ask_int();

        if(choice2==0) break;
        if(choice2==1){
            u3a::node_s* currptr = uni->get_pHead_student();
            if(currptr==nullptr){std::cerr<<"Empty list\n";} else cleanscreen();

            while(currptr!=nullptr){
                currptr->get_student()->print_student();
                currptr=currptr->get_next();
            }
        }
        if(choice2==2){
            u3a::node_t* currptr = uni->get_pHead_teacher();
            if(currptr==nullptr){std::cerr<<"Empty list\n";} else cleanscreen();

            while(currptr!=nullptr){
                currptr->get_teacher()->print_teacher();
                currptr=currptr->get_next();
            }
        }
        if(choice2==3){
            u3a::node_c* currptr = uni->get_pHead_course();
            if(currptr==nullptr){std::cerr<<"Empty list\n";} else cleanscreen();
            while(currptr!=nullptr){
                currptr->get_course()->print_course();
                currptr=currptr->get_next();
            }
        }
    
    sys_break();
    break;
}

case 4:{
    std::cerr<<"Input student's Id\n->";

    int id_chosen = ask_int();

    u3a::node_s* stud = uni->findStudById(id_chosen);
    if(stud==nullptr){
        std::cerr<<"No such Id\n"; 
        sys_break(); break;
    }
    if(stud->get_student()->get_courses() == nullptr){std::cerr<<"No active courses\n";}
    else{std::cerr<<"ACTIVE COURSES: \n";
    stud->get_student()->get_courses()->print_all();}
    
    if(stud->get_student()->get_completed()!=nullptr){
        std::cerr<<"\nCOMPLETED COURSES:\n";
        stud->get_student()->get_completed()->print_all();
    }
    
    
    sys_break();
    break;
}

case 5:{
    std::cerr<<"Print details about...\n1.Student\n2.Teacher\n3.Course\n0./Return\n";
    choice2=ask_int();

    if(choice2==0){break;}

    if(choice2==1){
        std::cerr<<"Provide student ID:\n->";
        int id = ask_int();
        if(uni->findStudById(id)==nullptr) std::cerr<<"No student with such id\n";
        else{
            cleanscreen();
            uni->findStudById(id)->print_student();
        }
    }

    if(choice2==2){
        std::cerr<<"Provide teacher ID:\n->";
        int id = ask_int();
        if(uni->findTeacherById(id)==nullptr) std::cerr<<"No teacher with such id\n";
        else{
            cleanscreen();
            uni->findTeacherById(id)->print_teacher();
            
            u3a::node_c* currptr = uni->findTeacherById(id)->get_teacher()->get_courses_conducted();
            std::cerr<<"Active courses list:\n\n";
            while(currptr!=nullptr){
                std::cerr<<"COURSE INFO:\nId: "<<currptr->get_course()->get_id()<<"\nName: "<<currptr->get_course()->get_name()<<"\nCapacity: "<<currptr->get_course()->get_student_count()<<"/"<<currptr->get_course()->get_capacity()<<"\n\n";
                currptr = currptr->get_next();
            }
            if(uni->findTeacherById(id)->get_teacher()->get_completed()!=nullptr){
                currptr = uni->findTeacherById(id)->get_teacher()->get_completed();
                std::cerr<<"\nCOMPLETED COURSES:\n\n";
                while(currptr!=nullptr){
                    std::cerr<<"COURSE INFO:\nId: "<<currptr->get_course()->get_id()<<"\nName: "<<currptr->get_course()->get_name()<<"\nCapacity: "<<currptr->get_course()->get_student_count()<<"/"<<currptr->get_course()->get_capacity()<<"\n\n";
                    currptr = currptr->get_next();
                }
            }
        }
    }

    if(choice2==3){
        std::cerr<<"Provide course ID:\n->";
        int id=ask_int();
        if(uni->findCourseById(id)==nullptr) std::cerr<<"No course with such id\n";
        else{
            cleanscreen();
            uni->findCourseById(id)->print_course();
            std::cerr<<"Student list:\n";
            u3a::node_s* currptr = uni->findCourseById(id)->get_course()->get_studentPHead();
            while(currptr!=nullptr){
                currptr->get_student()->print_student();
                currptr=currptr->get_next();
            }
        }
    }
    sys_break();
    break;
}

case 6:{ //delete a student/teacher/course
    std::cerr<<"Delete a...\n1.Student\n2.Teacher\n3.Course\n0./Return\n->";
    int choice2=ask_int();
    

    if(choice2==0){break;}

    if(choice2==1){
        std::cerr<<"Input student's id:\n->";
        int id = ask_int();
        if(uni->findStudById(id)==nullptr)
        {
            std::cerr<<"Invalid id\n";
            sys_break();break;
        }
        u3a::student* Student = uni->findStudById(id)->get_student();
            //Deroll a student from every course he's attending
        while(Student->get_courses()!=nullptr){
            uni->deroll_student(id,Student->get_courses()->get_course());
        }


        //Remove a student from the stack
        uni->remove_from_pHead_student(Student);

        //Remove student from completed courses history



        //find student
        //remove student

    }

    if(choice2==2){
        std::cerr<<"Input teacher's id:\n->";
        int id = ask_int();
        if(uni->findTeacherById(id)==nullptr){std::cerr<<"Invalid id";break;}
        u3a::teacher* Teacher = uni->findTeacherById(id)->get_teacher();

        //Check all courses if he teaches anything and delete him
        u3a::node_c* currptr= Teacher->get_courses_conducted();
        while(currptr!=nullptr){
            uni->remove_lecturer(uni->findTeacherById(id)->get_teacher(), currptr->get_course());
            currptr=currptr->get_next();
        }
        uni->remove_from_pHead_teacher(Teacher);
        break;
    }

    if(choice2==3){ //works
        std::cerr<<"Input course's id:\n->";
        int id = ask_int();
        if(uni->findCourseById(id)==nullptr){std::cerr<<"Invalid id";break;}
        if(uni->findCourseById(id)->get_course()->get_status()==1){std::cerr<<"This course has already finished. Modification forbidden.\n";sys_break();break;}
        u3a::course* Course = uni->findCourseById(id)->get_course();

        //Delete lecturers
            while(Course->get_lecturer()!=nullptr){
                uni->remove_lecturer(Course->get_lecturer()->get_teacher(), Course);
            }
        //Delete student list
            while(Course->get_studentPHead() != nullptr){
                uni->deroll_student(Course->get_studentPHead()->get_student()->get_id(), Course);
            }
        //Remove from the stack
            uni->remove_from_pHead_course(Course);
    }


 sys_break();
 break;
}

case 7:{
    std::cerr<<"Pick...\n1.Create a new course group\n2.Append a course to an existing group\n3.Remove a course from a group\n4.Delete a course group\n5.Print groups\n0./Return\n\n->";
    int choice2 = ask_int();

    if(choice2==0){break;}

    if(choice2==5){ //printing
        u3a::grouper* currptr = uni->get_pHead_grouper();
        while(currptr!=nullptr){
            std::cerr<<"GROUP INFO\nId: "<<currptr->get_id()<<"\nGroup name:"<<currptr->get_name()<<"\nGroupped courses:";
            u3a::node_c* currptr2 = currptr->get_pHead();
            while(currptr2!=nullptr){
                std::cerr<<"\nName:"<<currptr2->get_course()->get_name()<<", Id:"<<currptr2->get_course()->get_id()<<", Lecturer's name:"<<currptr2->get_course()->get_lecturer()->get_teacher()->get_name();
                currptr2=currptr2->get_next();
            }
            std::cerr<<"\n\n";
            currptr=currptr->get_next();}
        sys_break();
        break;} 



    if(choice2==1){ //creating a group
        std::cerr<<"\nInput new group's name\n->";
        char* name = ask_str();
       
        u3a::grouper* creation = new u3a::grouper(name);

        if(uni->get_pHead_grouper()==nullptr){
            uni->set_pHead_grouper(creation);
        }
        else
        {
            u3a::grouper* currptr = uni->get_pHead_grouper();
            while(currptr!=nullptr){
                if(currptr->get_next() == nullptr){
                    currptr->set_next(creation);
                    break;
                }
                currptr=currptr->get_next();
            }
        }   
        uni->log(combine_strings("Added a new group of courses(id:",uni->lowest_nontaken_id_grouper(),")"));
        creation->set_id(uni->lowest_nontaken_id_grouper());

        break;
    }


    if(choice2>=2 && choice2<=4){
        int id_c, id_g;
        if(choice2!=4){
            std::cerr<<"\nInput course's id\n->";
            id_c = ask_int();
            if(uni->findCourseById(id_c)==nullptr){std::cerr<<"No such course\n"; sys_break(); break;}
        }
        std::cerr<<"Input group's id\n->";
        id_g = ask_int();
        if(uni->findGroupById(id_g)==nullptr){std::cerr<<"No such group\n"; sys_break();   break;}


        if(choice2==2){ // append

            u3a::course* Course = uni->findCourseById(id_c)->get_course();
            u3a::grouper* group = uni->findGroupById(id_g);
            //check if not already appended
            u3a::node_c* currptr = group->get_pHead();
            
            //Error check
            try{
                while(currptr!=nullptr){
                    if(currptr->get_course() == Course){
                        throw u3a::AlreadyAddedException();
                    }
                    currptr=currptr->get_next();
                }
            }
            catch(u3a::AlreadyAddedException&){
                std::cerr<<"Course already in the group\n";
                sys_break();
                break;
            }

            //For 1

            uni->log(combine_strings(combine_strings("Added a course(id:",Course->get_id(),") into a group (id:"),group->get_id(),")"));

            if(group->get_pHead() ==nullptr){
                group->set_pHead(new u3a::node_c(Course));
                break;
            }

            //For 2

            if(group->get_pHead()->get_next()==nullptr){
                group->get_pHead()->set_next(new u3a::node_c(Course));
                break;
            }


            //For +2
            currptr = group->get_pHead()->get_next();
            u3a::node_c* prevptr = currptr;

            while(true){
                if(currptr==nullptr){
                    prevptr->set_next(new u3a::node_c(Course));
                    break;
                }
                prevptr = currptr;
                currptr= currptr->get_next();
            }
        break;}


        if(choice2==3){ //remove from a group
            u3a::course* Course = uni->findCourseById(id_c)->get_course();
            u3a::grouper* group = uni->findGroupById(id_g);

            u3a::node_c* currptr = group->get_pHead();
            //Error check
            int check = 0;
            try{
                while(currptr!=nullptr){
                    if(currptr->get_course() == Course){
                        check=1;
                    }
                    currptr=currptr->get_next();
                }
                if(!check) throw u3a::notFoundException(421);
            }
            catch(u3a::notFoundException&){
                std::cerr<<"Course not found\n";
                sys_break();
                break;
            }

            uni->log(combine_strings(combine_strings("Removed a course(id:",Course->get_id(),") from a group (id:"),group->get_id(),")"));
            uni->remove_from_group(group,Course);

        break;}


        if(choice2==4){
            u3a::grouper* group = uni->findGroupById(id_g);
            
            while(group->get_pHead()!=nullptr){
                uni->remove_from_group(group,group->get_pHead()->get_course());
            }
            
            u3a::grouper* currptr =  uni->get_pHead_grouper();
            u3a::grouper* prevptr = currptr;
            
            uni->log(combine_strings("Deleted a course (id:",group->get_id(),")"));

            //if first
            if(uni->get_pHead_grouper()==group){
                uni->set_pHead_grouper(group->get_next());
                delete group;
                break;
            }

            // //if not first 
            while(currptr!=nullptr){

                if(currptr==group){
                    prevptr->set_next(currptr->get_next());
                    delete group;
                    break;
                }
                prevptr = currptr;
                currptr =  currptr->get_next();
                
            }

            //check if exist
            //remove every course from group
            //remove a group

        }
    }


    
 break;
}

case 8:{ //Add/remove lecturer from a course
    std::cerr<<"...\n1.Add a lecturer\n2.Remove a lecturer\n0./Return\n->";
    int choice2 = ask_int();

    if(choice2==0){break;}

    std::cerr<<"\nInput teacher's id\n->";
    int id_l = ask_int(); 
    std::cerr<<"Input id of the course\n->";
    int id_c = ask_int();

    if(uni->findTeacherById(id_l)==nullptr){std::cerr<<"No such teacher\n"; sys_break();break;}
    if(uni->findCourseById(id_c)==nullptr){std::cerr<<"No such course\n"; sys_break();break;}
    if(uni->findCourseById(id_c)->get_course()->get_status()==1){std::cerr<<"This course has already finished. Modification forbidden!\n"; sys_break(); break;}
    if(choice2==1){
        if(uni->does_teacher_conduct(uni->findTeacherById(id_l)->get_teacher(),uni->findCourseById(id_c)->get_course()) == 1){
            std::cerr<<"This teacher is already conducting this course\n";
            sys_break();break;
        }
        
        uni->log(combine_strings(combine_strings("Added a lecturer(id:",uni->findTeacherById(id_l)->get_teacher()->get_id(),") into a course (id:"),uni->findCourseById(id_c)->get_course()->get_id(),")"));

        uni->add_lecturer(uni->findTeacherById(id_l)->get_teacher(),uni->findCourseById(id_c)->get_course());
    }
    if(choice2==2){
        if(uni->does_teacher_conduct(uni->findTeacherById(id_l)->get_teacher(),uni->findCourseById(id_c)->get_course())==0){
            std::cerr<<"This teacher is not conducting this course\n"; 
            sys_break();
            break;
        }
        if(uni->findCourseById(id_c)->get_course()->get_lecturer()->get_next()==nullptr){
            std::cerr<<"Removing this lecturer would mean a lecturer-less course. Add someone else first to remove this lecturer\n"; 
            sys_break();
            break;
        }

        uni->log(combine_strings(combine_strings("Removed a lecturer(id:",uni->findTeacherById(id_l)->get_teacher()->get_id(),") from a course (id:"),uni->findCourseById(id_c)->get_course()->get_id(),")"));
        uni->remove_lecturer(uni->findTeacherById(id_l)->get_teacher(),uni->findCourseById(id_c)->get_course());
    }
    
break;}
    


case 9:{
    std::cerr<<"Provide course ID:\n->";

    int id = ask_int();
    

    //Check for non-existien course id
    if(uni->findCourseById(id)==nullptr){
        std::cerr<<"No such course\n";
        sys_break();
        break;
    }
    cleanscreen();
    if(uni->findCourseById(id)->get_course()->get_studentPHead()==nullptr)std::cerr<<"\nNo students enrolled\n";
    else uni->findCourseById(id)->get_course()->print_student_list();

    sys_break();
    break;
}

case 10:{
    std::cerr<<"Pick...\n1.Add a new classroom\n2.Remove a classroom\n3.Schedule new activity for a classroom\n4.Print details for a classroom\n5.Print all classrooms\n0./Return\n\n->";
    int choice2 = ask_int();
    if(choice2==0){break;}
    if(choice2==1){
        uni->append_classroom();
    }

    if(choice2==5){
        u3a::classroom* currptr = uni->get_pHead_classroom();
        int order = 1;
        while(currptr!=nullptr){
            std::cerr<<"\n"<<"CLASSROOM "<<order<<":\nId:"<<currptr->get_id()<<"\n";
            order++;
            currptr=currptr->get_next();
        }
    sys_break(); break;
    }

    if(choice2==2){
        std::cerr<<"Provide id of the classroom:";
        int targetid = ask_int();
        u3a::classroom* currptr = uni->get_pHead_classroom();

        int checkk = 0;
        while(currptr!=nullptr){
            if(currptr->get_id()==targetid) checkk = 1;
            currptr=currptr->get_next();
        }
        if(checkk == 0) {std::cerr<<"No such id\n"; sys_break(); break;}
        
        uni->log(combine_strings("Removed a classroom (id:",targetid,")"));

        currptr = uni->get_pHead_classroom();
        if(currptr->get_id() == targetid){
            uni->set_pHead_classroom(currptr->get_next());
            break;
        }

        u3a::classroom* prevptr = currptr;

        while(currptr!=nullptr){
            if(currptr->get_id()==targetid){
                prevptr->set_next(currptr->get_next());
                delete currptr;
                break;
            }
            prevptr = currptr;
            currptr=currptr->get_next();
        }
    }

    if(choice2==3){ //scheduling
        try{
            std::cerr<<"Which classroom are you trying to reserve? Provide id\n\n->";
            int idcr = ask_int();
            if(uni->check_if_cr_exist(idcr)==0) throw u3a::unexpectedTimeException(-2);

            std::cerr<<"Select day of the week\n1.Monday\n2.Tuesday\n3.Wednesday\n4.Thursday\n5.Friday\n\n->";
            int day = ask_int();
            if(day<1 || day>5) throw u3a::unexpectedTimeException(-1);

            std::cerr<<"Select the starting HOUR (from 8 - 20)...\n8. 8\n9. 9\n10.10\n11.11\n12.12\netc...\n\n->";
            int hour1 = ask_int();
            if(hour1<8 || hour1>20) throw u3a::unexpectedTimeException(0);
            std::cerr<<"Select the starting quadrant...\n0.xx:00\n1.xx:15\n2.xx:30\n3.xx:45\n\n->";
            int minq1 = ask_int();
            if(minq1<0 || minq1>3) throw u3a::unexpectedTimeException(0);
            
            std::cerr<<"Select the ending HOUR (from 8 - 20)...\n8. 8\n9. 9\n10.10\n11.11\n12.12\netc...\n\n->";
            int hour2 = ask_int();
            if(hour2<8 || hour2>20) throw u3a::unexpectedTimeException(1);
            std::cerr<<"Select the ending quadrant...\n0.xx:00\n1.xx:15\n2.xx:30\n3.xx:45\n\n->";
            int minq2 = ask_int();
            if(minq2<0 || minq2>3) throw u3a::unexpectedTimeException(1);
            
            int index1 = (day-1)*48 + (hour1-8)*4 + minq1;
            int index2 = (day-1)*48 + (hour2-8)*4 + minq2;

            if(index1>=index2) throw u3a::unexpectedTimeException(2);

            std::cerr<<"Provide id of the course that's going to be conducted in these hours\n\n->";
            u3a::node_c* preco = uni->findCourseById(ask_int());
            if(preco==nullptr) throw u3a::unexpectedTimeException(4);
            u3a::course* co = preco->get_course();

            //Now check if it is occupied or no
            if(uni->check_if_free(uni->findCrById(idcr), index1, index2-index1)==0) throw u3a::unexpectedTimeException(3);
            uni->take_up(uni->findCrById(idcr), index1, index2-index1, co);
        }
        catch(u3a::unexpectedTimeException& e){
            if(e.i==-2)std::cerr<<"No such classroom\n";
            if(e.i==-1)std::cerr<<"Wrong day selected\n";
            if(e.i==0) std::cerr<<"Wrong Starting time given\n";
            if(e.i==1) std::cerr<<"Wrong Ending time given\n";
            if(e.i==2) std::cerr<<"Ending time can't be earlier than starting time\n";
            if(e.i==3) std::cerr<<"Given time period is already partially (or fully) reserved\n";
            if(e.i==4) std::cerr<<"No such course";
            //if(e.i==) std::cerr<<"";

            sys_break(); break;
        }

            sys_break(); break;
    }

    if(choice2==4){
        try{
            std::cerr<<"Provide id of the classroom\n\n->";
            int idrc = ask_int();
            if(uni->findCrById(idrc)==nullptr) throw u3a::unexpectedIdException(633);
            u3a::classroom* rc = uni->findCrById(idrc);
            cleanscreen();

            std::cerr<<"Which day?\n1.Monday\n2.Tuesday\n3.Wednesday\n4.Thursday\n5.Friday\n\n->";
            int choice3 = ask_int();
            if(choice3>5 || choice3<1)throw u3a::unexpectedIdException(642);

            if(choice3==1){std::cerr<<"Monday:\n";}
            if(choice3==2){std::cerr<<"Tuesday:\n";}
            if(choice3==3){std::cerr<<"Wednesday:\n";}
            if(choice3==4){std::cerr<<"Thursday:\n";}
            if(choice3==5){std::cerr<<"Friday:\n";}

                
            for(int i=0;i!=48;i++){
                std::cerr<<(i/4)+8<<":"<<(i%4)*15;
                if(i%4==0) std::cerr<<"0";

                if(rc->get(i+48*(choice3-1))!=nullptr) std::cerr<<"- Course: "<<rc->get(i+48*(choice3-1))->get_name()<<"("<<rc->get(i+48*(choice3-1))->get_id()<<")\n";
                else{std::cerr<<"\n";}
                }

            sys_break();
        }
        catch(u3a::unexpectedIdException& e){
            if(e.line == 633)std::cerr<<"No such classroom\n"; 
            if(e.line == 642)std::cerr<<"Wrong day selected\n";
    
            sys_break(); break;
        }
    }
break;}

case 11:{
    try{
        std::cerr<<"Provide course id:\n->";
        int cid = ask_int();
        if(uni->findCourseById(cid)==nullptr) throw u3a::unexpectedIdException(674);
        u3a::course* course1 = uni->findCourseById(cid)->get_course();

        u3a::student* temp;
        u3a::node_s* currptr = course1->get_studentPHead(); 
        uni->log(combine_strings("Set course(id:)",cid,") as completed"));
        while(currptr!=nullptr){
            temp = currptr->get_student();
            currptr=currptr->get_next();
            uni->complete(temp,course1); 
        }
        u3a::node_t* teachptr = course1->get_lecturer(); 
        u3a::teacher* tempteachptr = teachptr->get_teacher();
        while(teachptr!=nullptr){
            tempteachptr = teachptr->get_teacher();
            teachptr=teachptr->get_next();
            uni->complete(tempteachptr,course1);
        }
    }
    catch(u3a::unexpectedIdException& e){
        if(e.line == 674) std::cerr<<"No course with this id found\n";

        sys_break();
    }
break;
}   


case 12:{ //check log
    cleanscreen();
    u3a::datalog* cur = uni->get_pHead_datalog();
    int i=0;
    while(cur!=nullptr){
        i++;
        std::cerr<<"Log"<<i<<":"<< cur->get_message()<<"\n";
        
        cur=cur->get_next();
    }
sys_break();
break;
}


case 99:{
//debug program
    char name1[] = "abc";
    char name2[] = "def";
    char name3[] = "hij";
    char name4[] = "klm";
    char name5[] = "opr";
    char name6[] = "stu";
    char name7[] = "wxy";
    char name8[] = "zzz";

    uni->insert_new_student(18,name1);
    uni->insert_new_student(20,name2);
    uni->insert_new_student(22,name3);
    uni->insert_new_teacher(name4);
    uni->insert_new_teacher(name5);
    uni->insert_new_teacher(name6);
    uni->append_conduct(uni->findTeacherById(0)->get_teacher(),uni->insert_new_course(name7,0,5));
    uni->append_conduct(uni->findTeacherById(1)->get_teacher(),uni->insert_new_course(name8,1,5));
    uni->insert_new_course(name8,1,5);
    u3a::grouper* creation = new u3a::grouper(name1);
    uni->set_pHead_grouper(creation);
    uni->add_to_group(uni->findGroupById(0),uni->findCourseById(0)->get_course());
    uni->add_to_group(uni->findGroupById(0),uni->findCourseById(1)->get_course());
    uni->add_to_group(uni->findGroupById(0),uni->findCourseById(2)->get_course());
    uni->append_classroom();

    std::cerr<<"Debug controlls applied\n\n";
    sys_break();
break;

}
}//end of switch
}//end of loop
}//end of programme
