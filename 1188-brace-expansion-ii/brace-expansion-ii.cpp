class Solution
{
public:
    set<string> parse(string &s, int &i)
    {
        set<string> result;
        set<string> current = {""};

        while (i < s.size() && s[i] != '}')
        {
            if (s[i] == '{')
            {
                i++;

                set<string> inside = parse(s, i);
                i++;

                current = multiply(current, inside);
            }
            else if (s[i] == ',')
            {
                i++;

                result.insert(current.begin(), current.end());
                current = {""};
            }
            else
            {
                string ch(1, s[i]);
                i++;

                set<string> single = {ch};
                current = multiply(current, single);
            }
        }

        result.insert(current.begin(), current.end());

        return result;
    }

    set<string> multiply(set<string> &a, set<string> &b)
    {
        set<string> result;

        for (string x : a)
        {
            for (string y : b)
            {
                result.insert(x + y);
            }
        }

        return result;
    }

    vector<string> braceExpansionII(string expression)
    {
        int i = 0;

        set<string> result = parse(expression, i);

        return vector<string>(result.begin(), result.end());
    }
};
