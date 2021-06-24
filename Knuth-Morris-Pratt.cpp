#include <vector>
using namespace std;


/*

Taken from Cormen et al.

Pi encapsulates knowledge about how the pattern matches aganinst itself
*/

vector<int> computePrefixFunction(string const &pattern)
{
    int m = pattern.size();
    vector<int> pi(pattern.size(), 0);
    //If there's a mismatch at the first index of pattern, go back to the beginning
    pi[0] = -1;

    /*
    k denotes the index of the Longest Proper Prefix of Pattern[q] that is also a 
    suffix of Pattern[q]

    In other words, is the next anchor point of the pattern against itself

    ababa
    |||
    aba

    ababa
      |||
      aba
    */
    int k = -1;

    //q denotes the index at Pattern
    for (int q = 1; q < m; ++q)
    {
        //Mismatch between the prefix (patt[k+1]) and suffix (patt[q])
        while (k >= 0 and pattern[k + 1] != pattern[q])
            k = pi[k];
        //If there's a match, advance the prefix end
        if (pattern[k + 1] == pattern[q])
            k++;

        //Updating the table, if a mismatch at q, go back to index k of pattern
        pi[q] = k;
    }

    return pi;
}

int kmp(string const &text, string const &pattern)
{
    if (pattern.empty())
        return 0;
    if (text.empty())
        return -1;

    int n = text.size();
    int m = pattern.size();

    auto const pi = computePrefixFunction(pattern);

    //q is number of characters of pattern matched, i.e. the index of the pattern
    int q = -1;

    //i is the index in the input text
    for (int i = 0; i < n; ++i)
    {
        //This is to handle mismatch, go back in pattern and align with the next possible
        //alignment
        while (q >= 0 and pattern[q + 1] != text[i])
            q = pi[q];

        //If there is a match, advance the pattern index
        if (pattern[q + 1] == text[i])
            q++;

        //We have consumed the entire pattern, i.e. this is a match, report it and go back to the previous
        //possible alignment
        if (q == m - 1)
        {
            return i - (m - 1);
            q = pi[q];
        }
    }

    return -1;
}