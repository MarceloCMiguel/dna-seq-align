#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <random>
using namespace std;

struct SubstringValue
{
    string substring;
    int score;
};

int w_score(char a, char b)
{
    if (a == b)
    {
        return 2;
    }
    else if ((a == '-') || (b == '-'))
    {
        return -1;
    }
    else
    {
        return -1;
    }
}

string create_substring(string seq, int index, int random_size)
{

    string substring;
    while ((substring.size() < random_size) && (index < seq.size()))
    {

        substring.push_back(seq[index]);
        index++;
    }
    return substring;
}

vector<string> generate_substrings(string seq, int size)
{
    vector<string> substrings;
    for (int i = 0; i < size-1; i++)
    {
        for (int j = 1; j < size-i; j++)
        {
            substrings.push_back(seq.substr(i, j));
        }
    }
    return substrings;
}

int calculate_score(string sa, string sb)
{
    int score = 0;
    for (int i = 0; i < sa.size(); i++)
    {
        if (sa[i] == sb[i])
        {
            score += 2;
        }
        else if ((sa[i] == '-') || (sb[i] == '-'))
        {
            score -= 1;
        }
        else
        {
            score -= 2;
        }
    }
    return score;
}

int main()
{
    int n;
    int m;
    cin >> n >> m;

    string a;
    string b;
    cin >> a;
    cin >> b;
    // swap para que o a sempre seje a maior sequência
    if (m > n)
    {
        a.swap(b);
        swap(n, m);
    }
    cout << "n: " << n << endl;
    cout << "m: " << m << endl;
    cout << "Seq a: " << a << endl;
    cout << "Seq b: " << b << endl;
    cout << endl;

    vector<string> substrings_a = generate_substrings(a, n);
    vector<string> substrings_b = generate_substrings(b, m);
    int size_subs_a = substrings_a.size();
    int size_subs_b = substrings_b.size();

    string best_sub_a;
    string best_sub_b;

    int max_score = -n; // menor valor possível
    int score = -n;

    for (int i = 0; i < size_subs_a; i++)
    {
        for (int j = 0; j < size_subs_b; j++)
        {
            int size_a = substrings_a.size();
            int size_b = substrings_b.size();
            if (size_a == size_b)
            {
                score = calculate_score(substrings_a[i], substrings_b[j]);
                if (score > max_score)
                {
                    max_score = score;
                    best_sub_a = substrings_a[i];
                    best_sub_b = substrings_b[j];
                }
            }
            else
            {
                bool a_bigger = true;
                string bigger;
                string smaller;
                if (size_a > size_b)
                {
                    bigger = substrings_a[i];
                    smaller = substrings_b[j];
                }
                else
                {
                    a_bigger = false;
                    bigger = substrings_b[j];
                    smaller = substrings_a[i];
                }
                for (int p = 0; p < (int(bigger.size()) - int(smaller.size())); p++)
                {
                    string bigger_cutted = bigger.substr(p, int(smaller.size()));
                    score = calculate_score(smaller, bigger_cutted);
                    if (score > max_score){
                        max_score = score;
                        if (a_bigger){
                            best_sub_a = bigger_cutted;
                            best_sub_b = smaller;
                        }
                        else{
                            best_sub_a = smaller;
                            best_sub_b = bigger_cutted;
                        }
                    }
                }
            }
        }
    }
    cout << "Score: " << max_score << endl;
    cout << "Subsequence A: " << best_sub_a << endl;
    cout << "Subsequence B: " << best_sub_b << endl;


}