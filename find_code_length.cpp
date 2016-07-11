#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <set>

using namespace std;

map<string, vector<string> > read_code(string filepath)
{
    filepath = "code_id";
    map<string, vector<string> > result;

    ifstream inputs(filepath);
    string line;

    int tem_size = 0;

    while(getline(inputs, line))
    {
        string tmp, student_id;
        int start_position = 0;

        while(line[start_position] != '\t')
        {
            if (line[start_position] != ' ') tmp += line[start_position];
            start_position++;
        }
        student_id = tmp;
        tmp = "";

        for(int count = start_position + 1; count < line.length(); count++)
        {
            if(line[count] != '\t')
            {
                if (line[count] != ' ') tmp += line[count];
            }
            else
                {
                    result[student_id].push_back(tmp);
                    tmp = "";
                }

            if (count == line.length() - 1) result[student_id].push_back(tmp);
        }

        if (tem_size == result.size()) cout << "here" << endl;
        cout << student_id << '\t' << result.size() << endl;
        tem_size = result.size();
    }
    return result;
}

double average_line_count(vector<string> filenames)
{
    int file_count = 0;
    int line_count = 0;
    for(auto iter = filenames.begin(); iter != filenames.end(); iter++)
        {
            ifstream tmp_input(*iter);
            if (tmp_input.is_open())
            {
                string line;
                while(getline(tmp_input, line))
                {
                    line_count++;
                }
                file_count++;
            }
            else
            {
                cout << "file does not exist " << *iter << endl;
            }
        }
    return static_cast<double>(line_count)/file_count;
}

int main()
{
    map<string, vector<string> > code_id;
    code_id = read_code("");
    map<string, double> student_and_average_length;
    ofstream output("student_and_length");

    //for(auto iter = code_id.begin(); iter != code_id.end(); iter++)
    //{
    //    double average_length = average_line_count(iter -> second);
    //    student_and_average_length[iter -> first] = average_length;
    //    cout <<"student_id " << iter -> first << "completed" << endl;
    //}

    for(auto iter = code_id.begin(); iter != code_id.end(); iter++)
    {
        //double average_length = average_line_count(iter -> second);
        //output << iter -> first << '\t';
        //output << average_length << '\n';
        //cout <<"student_id " << iter -> first << "completed" << endl;
    }
}
