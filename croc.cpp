#include <bits/stdc++.h>
using namespace std;
queue<long long>q;
int main()
{
    int n,b;
    long long sum = 0;
    cin >> n >> b;
    while(n--)
    {
        int t,d;
        cin >> t >> d;
        while(q.size() && q.front() <= t)
        q.pop();
        if(q.size() == 0)
        sum = t;
        if(q.size() <= b)
        {
            sum += d;
            q.push(sum);
            cout << sum <<' ';
        }
        else
        cout << "-1 ";
    }
    cout << '\n';
    return 0;
}