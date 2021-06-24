using namespace std;

bool equal(string const &haystack, int i, string const &needle, int j)
{
    while (j < needle.size())
    {
        if (haystack[i] != needle[j])
            return false;
        ++i;
        ++j;
    }

    return true;
}

int rabin_karp(string const &haystack, string const &needle)
{
    int hLen = haystack.length();
    int nLen = needle.length();

    int base = 26;
    int mod = 101;

    int nHash = 0;
    int hHash = 0;

    int power = 1;
    for (int i = 0; i < nLen - 1; ++i)
        power = (power * base) % mod;

    //Calculating needle hash and first haystack hash
    for (int i = 0; i < nLen; ++i)
    {
        nHash = (base * nHash + needle[i]) % mod;
        hHash = (base * hHash + haystack[i]) % mod;
    }

    for (int i = 0; i <= (hLen - nLen); ++i)
    {
        if (hHash == nHash)
        {
            if (equal(haystack, i, needle, 0))
                return i;
        }
        if (i < (hLen - nLen))
        {
            hHash = (base * (hHash - haystack[i] * power) + haystack[i + nLen]) % mod;
            if (hHash < 0)
                hHash += mod;
        }
    }
    return -1;
}