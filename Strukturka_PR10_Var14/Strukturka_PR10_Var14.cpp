#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Метод поиска Рабина - Карпа.
//https://pro-prof.com/forums/topic/%D1%80%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D1%8F-%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D0%B0-%D1%80%D0%B0%D0%B1%D0%B8%D0%BD%D0%B0-%D0%BA%D0%B0%D1%80%D0%BF%D0%B0-%D0%BD%D0%B0-c#:~:text=%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D0%B0%20%D0%A0%D0%B0%D0%B1%D0%B8%D0%BD%D0%B0%2D%D0%9A%D0%B0%D1%80%D0%BF%D0%B0%20%D1%80%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D1%83%D0%B5%D1%82%20%D0%BF%D0%BE%D0%B8%D1%81%D0%BA,%D0%B4%D0%B5%D1%88%D0%B5%D0%B2%D0%BB%D0%B5%2C%20%D1%87%D0%B5%D0%BC%20%D1%81%D1%80%D0%B0%D0%B2%D0%BD%D0%B8%D0%B2%D0%B0%D1%82%D1%8C%20%D0%BF%D0%BE%D0%B4%D1%81%D1%82%D1%80%D0%BE%D0%BA%D0%B8%20%D0%BF%D0%BE%D1%81%D0%B8%D0%BC%D0%B2%D0%BE%D0%BB%D1%8C%D0%BD%D0%BE.

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

int RabinKarpMatch(char* T, char* P, int d, int q, vector<int>&hashes)
{
    int i, j, p, t, n, m, h, found;
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
        if (p == t)
        {
            found = 1;
            for (j = 0; j < m; j++)
                if (P[j] != T[i + j])
                {
                    found = 0;
                    break;
                }
            if (found)
                return i + 1;
        }
        else
        {
            t = (d * (t - ((tonum(T[i]) * h) % q)) + tonum(T[i + m])) % q;
        }
    }
    return -1;
}

int main()
{
    int sum = 0, menu;
    char *s = new char[100];
    char *substring = new char[100];
    int n;
    int d = 1, q = 1000;
    vector<int> hashes;

    cout << "What to do?\n"
        << "1 - Task#1 - Determine how many times each of the samples appears in the source text;" << endl
        << "2 - Task#2 - Find the names of text files, except for those that end in a number,\n             "
        << "and the first character is a given letter.\nEnter: ";
    cin >> menu;
    if (menu == 1)
    {
        cout << "Enter a number of substrings: ";
        cin >> n;
        cout << "Enter text: ";
        cin >> s;
        for (int i = 0; i < n; i++)
        {
            cout << "Enter " << i + 1 << " substring: ";
            cin >> substring;
            if (RabinKarpMatch(s, substring, d, q, hashes) != -1)
                sum += 1;
        }

        cout << "Hash-table:\n";
        for (int i = 0; i < hashes.size(); i++)
            cout << hashes[i] << endl;

        cout << "Total substrings in text: " << sum;
    }
    else if (menu == 2)
    {
        cout << "Task#2";
    }
    else return 0;

} //Iloveloveloveyouyou