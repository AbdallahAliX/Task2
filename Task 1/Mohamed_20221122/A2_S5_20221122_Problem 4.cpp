// File: Problem 4.cpp
// Author: Mohamed Sabry
// Section: S5/S6
// ID: 20221122
// TA: Nardeen/Maya


#include <iostream>
#include <bits/stdc++.h>

#define ll long long
using namespace std;

int main()
{
    int n;
    cin >> n;
    int a[n];
    a[0] = 0;
    a[1] = 0;
    for (int i = 2; i <= n; ++i)
    {
        a[i] = i;
    }
    for (int i = 2; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            if (j % i == 0)
            {
                a[j] = 0;
            }
        }
    }
    for (int i = 2; i <= n; ++i)
    {
        if (a[i] != 0)
        {
            cout << a[i] << " ";
        }
    }
}