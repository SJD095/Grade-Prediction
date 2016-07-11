#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <dirent.h>
#include <cctype>

using namespace std;
int tem_higest_submit = 0;
ofstream out("running_result");

double cal_total_submit_score = 0;
double cal_submit_count = 0;
double cal_average_higest_score = 0;
double cal_average_code_length = 0;
double cal_total_submit = 0;

int student_count = 0;

class student
{
public:
    string student_id = "";
    string total_submit_score = "0";
    string submit_count = "";
    string average_higest_score = "";
    string average_code_length = "";
    int total_submit = 0;
    string direct = "0";
    map<string, int> homework_higest_grades;
    double final_grade = 0;
    void print()
    {
        double xueyechengji = this -> total_submit * atof(this -> average_higest_score.c_str())/310;

        double meicitijiao = 0;

        if (atoi(this -> submit_count.c_str()) == 0) meicitijiao = 0;
        else
        {
            meicitijiao = atof(this -> total_submit_score.c_str())/atof(this -> submit_count.c_str());
        }

        out << this -> student_id << '\t' << this -> total_submit_score << '\t' << this -> submit_count << '\t' << this -> average_higest_score << '\t' << this -> average_code_length << '\t' << 310 - this -> total_submit << '\t' << this -> direct << '\t' << xueyechengji << '\t' << meicitijiao << '\t' << this -> final_grade << endl;
    }
};

class program_class
{
public:
    string class_id;
    vector<student> students;
    vector<string> homeworks;
    vector<string> exams;
    vector<string> studentids;
};

struct combyValue
{
   bool operator()(pair<string, double> &lhs,pair<string, double> &rhs)
   {return lhs.second>rhs.second;}
};

map<string, student> get_student()
{
    map<string, student> result;
    ifstream direct("student_direct");
    ifstream codelength("student_average_codeLength");
    ifstream scores("scores");
    //ifstream submission("student_submissions");
    string line, word;

    while(getline(scores, line))
    {
        student tmp_student;
        istringstream words(line);
        words >> tmp_student.student_id >> tmp_student.total_submit_score>>tmp_student.submit_count >> tmp_student.average_higest_score;
        result[tmp_student.student_id] = tmp_student;
    }

    while(getline(codelength, line))
    {
        istringstream words(line);
        string student_id, code_length;
        words >> student_id >> code_length;
        result[student_id].average_code_length = code_length;
    }

    while(getline(direct, line))
    {
        istringstream words(line);
        string student_id, direct;
        words >> student_id >> direct;
        result[student_id].direct = direct;
    }

    //while(getline(student_submissions, line))
    //{
    //    istringstream tmp(line);
    //    string student_id, submission_id;
    //    tmp >> student_id;
    //    while(tmp >> submission_id)
    //    {
    //        result[student_id].submission_ids.push_back(submission_id);
    //    }
    //}

    return result;
}

vector<string> find_file_names(string file)
{
    vector<string> names;
    DIR *dir;
    struct dirent *ptr;
    string prefix = "/Users/SJD/Desktop/2013/";
    prefix = prefix + file + '/';

    dir=opendir(prefix.c_str());

    while ((ptr=readdir(dir)) != NULL)
    {
        string filename(ptr -> d_name);
        if(ptr->d_type == 8 && filename != ".DS_Store" && filename != "readme"  && filename != "Untitled" && filename != "find_code.cpp" && filename != "code_result" && filename != "Untitled.cpp")
        {
             names.push_back(ptr -> d_name);
        }
    }

    return names;
}

vector<string> get_homeworks(string homeworks)
{
    vector<string> homework_list;
    string homeworkpath = "/Users/SJD/Desktop/2013/homework/";
    homeworkpath += homeworks;
    ifstream homework_input(homeworkpath);
    string line;

    while(getline(homework_input, line))
    {
        homework_list.push_back(line);
    }

    return homework_list;
}

vector<string> get_exams(string exams)
{
    string exampath = "/Users/SJD/Desktop/2013/exams/";
    istringstream exam_in_string(exams);
    string exam_spec, line;
    vector<string> exam_list;

    while(exam_in_string >> exam_spec)
    {
        string tem_path = exampath;
        tem_path += exam_spec;
        ifstream exam_input(tem_path);

        exam_input >> line;
        while(exam_input >> line)
        {
            bool digit = true;
            for(auto iter = line.begin(); iter != line.end(); iter++)
            {
                if(!isdigit(*iter))
                {
                    digit = false;
                }
            }
            if(digit) exam_list.push_back(line);
        }
    }

    return exam_list;

}

program_class file_operate(string filename)
{
    program_class tem_class;
    tem_class.class_id = filename;

    string prefix = "/Users/SJD/Desktop/2013/classes/";
    ifstream input(prefix+filename);
    string class_kind, homeworks, exams, student;

    getline(input, class_kind);
    getline(input, homeworks);
    getline(input, exams);
    while(getline(input, student))
    {
        tem_class.studentids.push_back(student);
        cout << tem_class.class_id << '\t' << student << endl;
    }

    tem_class.homeworks = get_homeworks(homeworks);
    tem_class.exams = get_exams(exams);

    return tem_class;
}

vector<program_class> get_classes()
{
    vector<program_class> result;
    vector<string> class_list = find_file_names("classes");

    for(auto iter = class_list.begin(); iter != class_list.end(); iter++)
    {
        result.push_back(file_operate(*iter));
    }

    return result;
}

void test_student(student &input_student)
{

    input_student.print();

    if(input_student.total_submit > tem_higest_submit)
    {
        tem_higest_submit = input_student.total_submit;
    }

    cal_total_submit_score += atof(input_student.total_submit_score.c_str());
    cal_submit_count += atof(input_student.submit_count.c_str());
    cal_average_higest_score += atof(input_student.average_higest_score.c_str());
    cal_average_code_length += atof(input_student.average_code_length.c_str());
    cal_total_submit += input_student.total_submit;

    student_count++;

    //cout << "homework and higest grade\t" << endl;
    //for(auto iter = input_student.homework_higest_grades.begin(); iter != input_student.homework_higest_grades.end(); iter++)
    //{
    //    cout << iter -> first << " " << iter -> second << endl;
    //}
}

void test_class(program_class &input_class)
{
    //cout << "class\t" << input_class.class_id << endl;
    //cout << "studnet_list" << endl;
    for(auto iter = input_class.students.begin(); iter != input_class.students.end(); iter++)
    {
        test_student(*iter);
    }

    //cout << "homeworks" << endl;

    for(auto iter = input_class.homeworks.begin(); iter != input_class.homeworks.end(); iter++)
    {
        //cout << *iter << endl;
    }

    //cout << "exams" << endl;

    for(auto iter = input_class.exams.begin(); iter != input_class.exams.end(); iter++)
    {
        //cout << *iter << endl;
    }
}

void write_homework_and_grade()
{
    string path = "/Users/SJD/Desktop/2013/submissions/";
    vector<string> file_names = find_file_names("submissions");
    ofstream output("home_work_and_grade");

    for(auto iter = file_names.begin(); iter != file_names.end(); iter++)
    {
        string submissionid = *iter;
        string tmp_path = path + *iter;
        ifstream tmp_submission(tmp_path);
        string line, student_id, homework_id, grade;

        getline(tmp_submission, student_id);
        getline(tmp_submission, homework_id);
        getline(tmp_submission, line);
        getline(tmp_submission, grade);
        //cout << "get\t" << submissionid << '\t' << student_id << "\t" << homework_id << "\t" << grade << endl;

        for(auto iter = grade.begin(); iter != grade.end(); iter++)
        {
            if(!isdigit(*iter))
            {
                grade = "0";
                break;
            }
        }

        output << student_id << '\t' << homework_id << '\t' << grade << endl;
    }
}

map<string, map<string, int> > get_submission_and_grade()
{
    map<string, map<string, int> > map_student_submission_higestgrade;
    ifstream input("home_work_and_grade");
    string student_id, homework_id, grade, line;
    while(getline(input, line))
    {
        istringstream tem_words(line);
        tem_words >> student_id >> homework_id >> grade;

        int grade_int = atoi(grade.c_str());
        if(map_student_submission_higestgrade.find(student_id) != map_student_submission_higestgrade.end())
        {
            if (map_student_submission_higestgrade[student_id].find(homework_id) != map_student_submission_higestgrade[student_id].end())
            {
                if (grade_int > map_student_submission_higestgrade[student_id][homework_id])
                {
                    map_student_submission_higestgrade[student_id][homework_id] = grade_int;
                }

            }
            else
            {
                map_student_submission_higestgrade[student_id][homework_id] = grade_int;
            }
        }
        else
        {
            map_student_submission_higestgrade[student_id][homework_id] = grade_int;
        }

    }

    return map_student_submission_higestgrade;
}

void calcute_final_grade(vector<program_class> &input_classes)
{
    double tmp_final_grade = 0;
    for(auto iter3 = input_classes.begin(); iter3 != input_classes.end(); iter3++)
    {
        for (auto iter = iter3 -> students.begin(); iter != iter3 -> students.end(); iter++)
        {
            iter -> total_submit = iter -> homework_higest_grades.size();

            for(auto iter2 = iter3 -> exams.begin(); iter2 != iter3 -> exams.end(); iter2++)
            {
                if (iter -> homework_higest_grades.find(*iter2) != iter -> homework_higest_grades.end())
                {
                    tmp_final_grade += iter -> homework_higest_grades[*iter2];
                    //if (iter -> homework_higest_grades[*iter2] >= 90) tmp_final_grade++;
                }
            }
            //iter -> final_grade = tmp_final_grade;
            iter -> final_grade = tmp_final_grade/iter3 -> exams.size();
            tmp_final_grade = 0;
        }
    }
}


void sort_and_output(string filename, vector<program_class> &input_classes)
{
    string prefix = "/Users/SJD/Desktop/2013/";
    string path = prefix + filename + '/';
    vector<double> theta;
    map<string, double> map_for_sort;
    theta.push_back(-0.222304);
    theta.push_back(0.166761);
    theta.push_back(0.115874);
    theta.push_back(0.501839);
    theta.push_back(0.330346);

    for(auto iter = input_classes.begin(); iter != input_classes.end(); iter++)
    {
        ofstream output(path + iter -> class_id);
        double tmp = 0;

        for(auto student_iter = iter -> students.begin(); student_iter != iter -> students.end(); student_iter++)
        {
            double forecast_grade = 0;

            if(student_iter -> student_id != "")
            {
                forecast_grade = atof(student_iter -> submit_count.c_str()) * theta[0] / 50 + atof(student_iter -> average_higest_score.c_str()) * theta[1] + atof(student_iter -> average_code_length.c_str()) * theta[2] + student_iter -> total_submit * theta[4] + atof(student_iter -> direct.c_str()) * theta[3];

                map_for_sort[student_iter -> student_id] = forecast_grade;
                tmp = forecast_grade;
            }

        }

        for(auto studnetids = iter -> studentids.begin(); studnetids != iter -> studentids.end(); studnetids++)
        {
            bool la = false;

            for(auto iter5 = iter -> students.begin(); iter5 != iter -> students.end(); iter5++)
            {
                if(iter5 -> student_id == *studnetids)
                {
                    la = true;
                }
            }

            if(la == false)
            {
                map_for_sort[*studnetids] = 0;
                if(iter -> class_id == "16832")
                {
                    cout << *studnetids << endl;
                }
            }
        }

        vector<pair<string,double> > vec(map_for_sort.begin(),map_for_sort.end());
        sort(vec.begin(),vec.end(),combyValue());

        for(auto iter = vec.begin(); iter != vec.end(); iter++)
        {
            output << iter -> first << endl;
        }
        map_for_sort.clear();
    }
}

int main()
{
    //write_homework_and_grade();
    map<string, student> all_student = get_student();
    vector<program_class> classes = get_classes();
    map<string, map<string, int> > student_homework_grade = get_submission_and_grade();

    for(auto iter = student_homework_grade.begin(); iter != student_homework_grade.end(); iter++)
    {
        string student_id = iter -> first;
        for(auto iter2 = iter->second.begin(); iter2 != iter -> second.end(); iter2++)
        {
            all_student[student_id].homework_higest_grades[iter2->first] = iter2->second;
        }
    }

    for(auto iter = classes.begin(); iter != classes.end(); iter++)
    {
        for(auto iter_studentid = iter->studentids.begin(); iter_studentid != iter->studentids.end(); iter_studentid++)
        {
            if (all_student.find(*iter_studentid) != all_student.end())
            {
                student tem_student = all_student[*iter_studentid];
                //if (tem_student.student_id == "") cout << "student_id is empty\t" << *iter_studentid << endl;
                //if (tem_student.student_id == "93321") cout << iter -> class_id << endl;
                iter->students.push_back(tem_student);
            }
        }
    }

    calcute_final_grade(classes);

    sort_and_output("result", classes);

    for(auto iter = classes.begin(); iter != classes.end(); iter++)
    {
        test_class(*iter);
    }

    cout << cal_total_submit_score/student_count
<< '\t' << cal_submit_count/student_count
<< '\t' << cal_average_higest_score/student_count
<< '\t' << cal_average_code_length/student_count
<< '\t' << cal_total_submit/student_count << endl;
}
