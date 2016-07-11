#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>

using namespace std;

void file_operate(char* filename);
void find_student_direct(string filepath);

int main()
{
    string students_path = "/Users/SJD/Desktop/2013/students/";
    find_student_direct(students_path);
}

void file_operate(char* filename)
{
    ofstream result("student_direct", ofstream::app);
    string prefix = "/Users/SJD/Desktop/2013/students/";
    ifstream input(prefix+filename);
    string line, sex, major, experience, grade;
    for(int i = 0; i < 4; i++)
    {
        switch(i)
        {
            case 0:
                getline(input, sex);
                break;
            case 1:
                getline(input, major);
                break;
            case 2:
                getline(input, experience);
                break;
            case 3:
                getline(input, grade);
        }
    }
    result << filename << '\t' << (grade == "0" ? 1 : 0) << '\n';
}


void find_student_direct(string filepath)
{
    DIR *dir;
    struct dirent *ptr;
    char path[50] = "/Users/SJD/Desktop/2013/students/";

    dir=opendir(path);

    while ((ptr=readdir(dir)) != NULL)
    {
        string filename(ptr -> d_name);
        if(ptr->d_type == 8 && filename != ".DS_Store" && filename != "readme")
        {
             file_operate(ptr -> d_name);
        }
    }
}
