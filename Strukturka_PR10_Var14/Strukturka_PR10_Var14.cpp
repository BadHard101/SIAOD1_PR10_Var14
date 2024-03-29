﻿#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <ctime>
using namespace std;


//http://mindhalls.ru/rabin-karp-search/
//https://www.cyberforum.ru/cpp-beginners/thread957633.html
#define tonum(c) (c >= 'A' && c <= 'Z' ? c - 'A' : c - 'a' + 26)

int mod(int d, int m, int q)
{
    if (m == 0)
        return 1;
    int sqr = mod(d, m / 2, q) % q;

    if (m & 1)
        return ((d % q) * sqr) % q;
    else
        return sqr;
}

int RabinKarpMatch(char* T, char* P, vector<int>&hashes, int& D)
{
    int d = 1, q = 1000;
    int sum = 0, i, j, p, t, n, m, h, found;
    n = strlen(T);
    m = strlen(P) - 1;
    h = mod(d, m, q);
    p = t = 0;

    for (i = 0; i < m; i++)
    {
        p = (d * p + tonum(P[i])) % q;
        t = (d * t + tonum(T[i])) % q;
    }

    hashes.push_back(p);

    for (i = 0; i <= n; i++)
    {
        D++;
        if (p == t)
        {
            found = 1;
            for (j = 0; j < m; j++) {
                D++;
                if (P[j] != T[i + j])
                {
                    found = 0;
                    break;
                }
            }
            if (found)
                sum += 1;
        }
        else
        {
            t = (d * (t - ((tonum(T[i]) * h) % q)) + tonum(T[i + m])) % q;
        }
    }
    return sum;
}

//https://ru.stackoverflow.com/questions/868619/%D0%BF%D0%BE%D0%B8%D1%81%D0%BA-%D0%B2-%D1%81%D1%82%D1%80%D0%BE%D0%BA%D0%B5-%D1%80%D0%B5%D0%B3%D1%83%D0%BB%D1%8F%D1%80%D0%BD%D0%BE%D0%B3%D0%BE-%D0%B2%D1%8B%D1%80%D0%B0%D0%B6%D0%B5%D0%BD%D0%B8%D1%8F-%D1%81-%D0%BF%D0%BE%D0%B4%D1%81%D1%82%D1%80%D0%BE%D0%BA%D0%BE%D0%B9-c
void find_files(string str, regex rex) {
    sregex_iterator beg{ str.cbegin(), str.cend(), rex };
    sregex_iterator end{};

    for (auto i = beg; i != end; ++i)
        cout << i->str() << "\n";
}

int main()
{
    srand(time(NULL));
    unsigned int start_time;
    unsigned int end_time;

    int sum = 0, D = 0, menu;
    char *s = new char[1000];
    int n;
    vector<int> hashes;
    vector<int> sums;
    vector<const char*> substrings;

    cout << "What to do?\n"
        << "1 - Task#1 - Determine how many times each of the samples appears in the source text;" << endl
        << "2 - Task#2 - Find the names of text files, except for those that end in a number,\n             "
        << "and the first character is a given letter.\nEnter: ";
    cin >> menu;
    if (menu == 1)
    {
        cout << "Task#1\n";
        cout << "Enter a number of substrings: ";
        cin >> n;
        cout << "Enter text: ";
        cin >> s; // IloveIloveloveyoulovesomuchsoyoulove

        for (int i = 0; i < n; i++)
        {
            cout << "Enter " << i + 1 << " substring: ";
            char* substring = new char[100];
            cin >> substring;
            substrings.push_back(substring);
            start_time = clock();
            sum += RabinKarpMatch(s, substring, hashes, D);
            end_time = clock();
            /*cout << "time: "
                << (end_time - start_time) / 1000.0
                << " sec\n\n";*/
            if (i!=0)
                sums.push_back(sum-sums[i-1]);
            else
                sums.push_back(sum);
        }

        cout << "\nHash-table:\n";
        for (int i = 0; i < hashes.size(); i++)
            cout << hashes[i] << endl;

        cout << "\nTotal substrings in text:\n";

        for (int i = 0; i < n; i++)
            cout << substrings[i] << ": " << sums[i] << endl;

        cout << "Cf + Mf = " << D << endl;
    }
    else if (menu == 2)
    {
        string first_letter, regular;
        string s = "myfile,my1k2019,m1y2f,123q,q3,m,123,q789475dfg,q";
       
        cout << "Task#2\n";
        cout << "Enter list of file names: ";
        cin >> s;
        cout << "Enter first letter: ";
        cin >> first_letter;
        regex r(R"((\b[^)"+first_letter+R"(,]\w+[^\d,]\b)|(\b[^)"+first_letter+R"(,]\b))");
        cout << "All founded file names:\n";
        find_files(s, r);
    }
    else return 0;

} 