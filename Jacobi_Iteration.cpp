#include <iostream>
#include <vector>
#include <iomanip>
#include <windows.h>

#define SWITCH_SHOW_INTER_VAR 0
#define SWITCH_EQUATION_MANUAL_INPUT 0
#define SWITCH_MAX_MANUAL_INPUT 0
#define SWTICH_EPSILON_MANUAL_INPUT 0

using namespace std;
int main()
{
    long long Jacobi_Iteration(vector<vector<double>> & src, vector<double> & ans, long long max_times, double epsilon);
    void display_equation(vector<vector<double>> & src, vector<double> & ans);
    void display_ans(vector<double> & ans);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
    cout << "# Jacobi Iteration." << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

    vector<vector<double>> sample = {{2, -1, -1, 2}, {1, -3, 1, 0}, {1, 1, 4, 7}};
    vector<vector<double>> sample2 = {{7, -1, 5, -20}, {3, -9, -2, -13}, {5, -4, 8, -22}};
    vector<double> ans = {0, 0, 0};

    long long maximum_iteration_times = 1000;
    double epsilon = 0.000001;

    if (SWITCH_EQUATION_MANUAL_INPUT)
    {
        sample.clear();
        cout << "Input the num of equations:" << endl;
        long long n;
        cin >> n;
        sample.resize(n);
        for (long long i = 0; i < n; i++)
        {
            cout << "Input the equation_" << i + 1 << ":" << endl;
            for (long long j = 0; j <= n; j++)
            {
                if (j != n)
                {
                    cout << "x_" << j << ':' << endl;
                }
                else
                {
                    cout << "b_" << i << ':' << endl;
                }
                double input;
                cin >> input;
                sample[i].push_back(input);
            }
        }
        cout << "Input the initial values:" << endl;
        for (long long i = 0; i < n; i++)
        {
            cout << "x_" << i << ':' << endl;
            cin >> ans[i];
        }
        // display_equation(sample, ans);
    }

    if (SWTICH_EPSILON_MANUAL_INPUT)
    {
        cout << "Input the precision value:" << endl;
        cin >> epsilon;
    }

    if (SWITCH_MAX_MANUAL_INPUT)
    {
        cout << "Input the maximum_iteration_times:" << endl;
        cin >> maximum_iteration_times;
    }

    display_equation(sample, ans);

    cout << "The pricision requires is: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    cout << epsilon << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    cout << "The maximum_iteration_times is: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    cout << maximum_iteration_times;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    cout << endl;
    long long times = Jacobi_Iteration(sample, ans, maximum_iteration_times, epsilon);
    if (0 <= times)
    {
        cout << "The number of iteration is: ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN);
        cout << times;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
        cout << endl;
    }
    display_ans(ans);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
    cout << "# End Jacobi Iteration." << endl;
    // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

    return 0;
}

void display_equation(vector<vector<double>> &src, vector<double> &ans)
{
    void display_ans(vector<double> & ans, int switch_ini);
    cout << fixed;
    long long num_var = src.size();
    cout << "\nThe initial equation:" << endl;
    for (long long i = 0; i < num_var; i++)
    {
        long long m = src[i].size();
        for (long long j = 0; j < m; j++)
        {
            if (m - 1 == j)
            {
                cout << ' ' << '=' << ' ' << setw(6);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                cout << src[i][j] << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                cout << showpos << setw(6) << src[i][j];
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
                cout.unsetf(ios::showpos);
                cout << ' ' << '*' << ' ' << 'x' << '_';
                cout << j << ' ';
            }
        }
    }
    display_ans(ans, 1);
    cout << endl;
    return;
}

void display_ans(vector<double> &ans)
{
    cout << "The ans is:" << endl;
    long long m = ans.size();
    for (long long i = 0; i < m; i++)
    {
        cout << "x_" << i << " = ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        cout << ans[i] << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    }
    cout << endl;
}

void display_ans(vector<double> &ans, int switch_ini)
{
    if (!switch_ini)
    {
        cout << "The ans is:" << endl;
    }
    else
    {
        cout << "The initial values are:" << endl;
    }
    long long m = ans.size();
    for (long long i = 0; i < m; i++)
    {
        cout << "x_" << i << " = ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        cout << ans[i] << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    }
}

long long Jacobi_Iteration(vector<vector<double>> &src, vector<double> &ans, long long max_times, double epsilon)
{
    bool ipsilon_reached = false;
    long long times = 0;
    vector<double> delta(src.size(), 0);
    for (times++; times <= max_times; times++)
    {
        vector<double> ans_old(ans);
        long long m = src.size();
        for (long long i = 0; i < m; i++)
        {
            double sum_pro = 0;
            for (long long k = 0; k < m; k++)
            {
                if (k == i)
                {
                    continue;
                }
                sum_pro += ans_old[k] * src[i][k];
            }
            ans[i] = (src[i][m] - sum_pro) / src[i][i];
            delta[i] = abs(ans[i] - ans_old[i]);
        }
        sort(delta.begin(), delta.end());
        double max_delta = delta[delta.size() - 1];
        if (max_delta < epsilon)
        {
            ipsilon_reached = true;
            break;
        }
        // Output the inter vars
        if (SWITCH_SHOW_INTER_VAR)
        {
            cout << times << ":\n";
            display_ans(ans);
        }
    }
    if (ipsilon_reached)
    {
        cout << "\nThe precision is reached, Jacobi computing terminated." << endl;
    }
    else
    {
        cout << "\nThe precision is not reached and the maximum_iteration_times is reached, Jacobi iteration terminated." << endl;
    }
    return times;
}