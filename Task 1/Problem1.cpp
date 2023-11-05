#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    char arr[100];
    int len, j;
    string str;
    cout << "enter string" << endl;
    getline(cin, str);
    len = str.length();
    char answer[100];
    strcpy(arr, str.c_str());
    for (int i = 0; i < len; i++)
    {
        if (arr[i] == ' ' && arr[i + 1] == ' ')
            continue;
        if (arr[i] >= 65 && arr[i] <= 90)
        {
            answer[j++] = arr[i] + 32;
        }
        else
        {
            answer[j++] = arr[i];
        }
    }
    answer[0] = answer[0] - 32;
    ;
    for (int i = 0; i < j; i++)
    {
        cout << answer[i];
    }
    return 0;
}