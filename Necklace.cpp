#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str1;
    char str2[200];
    int i;
    static int cnt[26][200];

    cin >> i;
    getline(cin,str1);

    str1.insert(str1.begin(),' ');

    //Table generation
    for(int j = 1;j <= i;j += 1)
    {
        cnt[(int)str1[j] - 65][0] += 1;
        cnt[(int)str1[j] - 65][cnt[(int)str1[j] - 65][0]] = j;
    }

    //Printing the table
    for(int j = 0;j < 26;j += 1)
    {
        cout << cnt[j][0];
        for(int k = 1;k <= cnt[j][0];k += 1)
            cout << " " << cnt[j][k];
        cout << endl;
    }

    return 0;
}
