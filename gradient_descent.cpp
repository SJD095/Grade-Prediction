#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>

using namespace std;

const double __ALPHA = 0.00001;
const int _ITERATIONS = 1000;
const int row_number = 383;
int row = 0;

vector<vector<double> > data;
vector<double> result;
double temp[row_number];
vector<double> theta(383, 0);
vector<double> theta_tmp(row_number, 0);
vector<double> derivative(row_number, 0);

void read_data(string filename);
void gradient_descent();
double get_partial_derivative(int index);
double H(int index);

void read_data(string filename)
{
    ifstream input(filename);
    string line;
    getline(input, line);

    while(getline(input, line))
    {
        istringstream words(line);
        string word;
        vector<double> tmp;
        words >> word;
        if (word != "")
        {

            for(int i = 0; i < 383; i++)
            {
                words >> word;
                tmp.push_back(atof(word.c_str()));
            }

            words >> word;
            result.push_back(atof(word.c_str()));
            data.push_back(tmp);
            row++;

        }
    }
}

void gradient_descent()
{
    int count = 0;
    while(count < _ITERATIONS)
    {
        cout << count++ << endl;

        for(int i = 0; i < row_number; i++)
        {
            derivative[i] = get_partial_derivative(i);
            theta_tmp[i] = theta[i] - __ALPHA * derivative[i];
        }

        for(int i = 0; i < row_number; i++)
        {
            theta[i] = theta_tmp[i];
        }

        //for(auto iter = theta.begin(); iter != theta.end(); iter++)
        //{
            //cout << *iter << '\t';
        //}
        //cout << endl;
    }
}

double get_partial_derivative(int index)
{
    double sum = 0;

    for (int i = 0; i < row; i++)
    {
        sum += ( H(i) - result[i]) * data[i][index];
    }
    //cout << sum << endl;

    return sum / row;
}

double H(int index)
{
    double hx = 0;

    for(int i = 0; i < row_number; i++)
    {
        hx += theta[i] * data[index][i];
    }
    return hx;
}

int main()
{
    read_data("train.csv");
    gradient_descent();

    double pingjuncha = 0;

    for(auto iter = theta.begin(); iter != theta.end(); iter++)
    {
        cout << *iter << endl;
    }

    for(int i = 0; i < 10; i++)
    {
        if(result[i] - H(i) > 8) cout << result[i] << '\t' << H(i) << endl;
        pingjuncha += (result[i] - H(i) > 0 ? result[i] - H(i) : H(i) - result[i]);
    }

    cout << pingjuncha/10 << endl;
    cout << row << endl;
}
