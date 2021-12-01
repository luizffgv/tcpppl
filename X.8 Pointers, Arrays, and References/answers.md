# X.8 Pointers, Arrays, and References

---

The code solutions might have implicit `#include` and `using` directives, and be
assumed to be inside the `main` function.

---

1. - ```cpp
     char ch;
     char *a = &ch;
     ```
   - `int b[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}`
   - `int (&c)[10] = b`
   - ```cpp
     char *strs[5] = {nullptr};
     char *(*d)[5] = &strs;
     ```
   - `char **e = &a`
   - `int const f = 5`
   - `int const *g = &f`
   - ```cpp
     int i = 5;
     int *const h = &i;
     ```

2. A `char*` can have any natural value, a `int*` should be a multiple of 4 and
   a `void*` can also have any natural value.

3. - `using uc = unsigned char;`
   - `using cuc = unsigned char const;`
   - `using pi = int *;`
   - `using pc = char **;`
   - `using pca = char (*)[]; // Uhh...`
   - `using api = int *[7];`
   - `using papi = int *(*)[7];`
   - `using aapi = int *[8][7];`

4. ```cpp
   char  arr[100]{};
   char *ptrs[2]{&arr[25], &arr[75]};

   cout << "Distance: " << abs(ptrs[0] - ptrs[1]) << endl;
   ```

5. ```cpp
   int  arr[100]{};
   int *ptrs[2]{&arr[25], &arr[75]};

   cout << "Distance: " << abs(ptrs[0] - ptrs[1]) << endl;
   ```

6. | Array  | Access       | Optimization | Effect          |
   | ------ | ------------ | ------------ | --------------- |
   | global | close        | low (`-O0`)  | Fine            |
   | global | close        | high (`-O3`) | Fine            |
   | global | close behind | low          | Fine            |
   | global | close behind | high         | Fine            |
   | global | far          | low          | Fine            |
   | global | far          | high         | Fine            |
   | global | far behind   | low          | Crash, no error |
   | global | far behind   | high         | Crash, no error |
   | local  | close        | low          | Fine            |
   | local  | close        | high         | Fine            |
   | local  | close behind | low          | Fine            |
   | local  | close behind | high         | Fine            |
   | local  | far          | low          | Fine            |
   | local  | far          | high         | Fine            |
   | local  | far behind   | low          | Fine            |
   | local  | far behind   | high         | Fine            |
   | heap   | close        | low          | Fine            |
   | heap   | close        | high         | Fine            |
   | heap   | close behind | low          | Fine            |
   | heap   | close behind | high         | Fine            |
   | heap   | far          | low          | Fine            |
   | heap   | far          | high         | Fine            |
   | heap   | far behind   | low          | Fine            |
   | heap   | far behind   | high         | Fine            |

7. ```cpp
   void Swap(int *a, int *b)
   {
       int tmp{*a};
       *a = *b;
       *b = tmp;
   }

   void Swap(int &a, int &b)
   {
       int tmp{a};
       a = b;
       b = tmp;
   }
   ```

8. 15 bytes.

9. | Function         | Argument | Legal?         | Temporary? |
   | ---------------- | -------- | -------------- | ---------- |
   | `f(char)`        | `'a'`    | Yes            | No         |
   | `f(char)`        | `49`     | Yes            | No         |
   | `f(char)`        | `3300`   | Yes, overflows | No         |
   | `f(char)`        | `c`      | Yes            | No         |
   | `f(char)`        | `uc`     | Yes            | No         |
   | `f(char)`        | `sc`     | Yes            | No         |
   | `g(char&)`       | `'a'`    | No             |            |
   | `g(char&)`       | `49`     | No             |            |
   | `g(char&)`       | `3300`   | No             |            |
   | `g(char&)`       | `c`      | Yes            | No         |
   | `g(char&)`       | `uc`     | No             |            |
   | `g(char&)`       | `sc`     | No             |            |
   | `h(const char&)` | `'a'`    | Yes            | Yes        |
   | `h(const char&)` | `49`     | Yes            | Yes        |
   | `h(const char&)` | `3300`   | Yes, overflows | Yes        |
   | `h(const char&)` | `c`      | Yes            | No         |
   | `h(const char&)` | `uc`     | Yes            | Yes        |
   | `h(const char&)` | `sc`     | Yes            | Yes        |

10. ```cpp
    void PrintMonths(char const *const months[12])
    {
        for (size_t i{}; i < 12; ++i)
            cout << months[i] << endl;
    }

    int main()
    {
        char const *const months[12]{"January",
                                     "February",
                                     "March",
                                     "April",
                                     "May",
                                     "June",
                                     "July",
                                     "August",
                                     "September",
                                     "October",
                                     "November",
                                     "December"};

        for (auto const &month : months)
            cout << month << endl;

        PrintMonths(months);

        return 0;
    }
    ```

11. ```cpp
    set<string> words;

    for (istream_iterator<string> it{cin}; *it != "Quit"; ++it)
        words.insert(*it);

    for (auto const &word : words)
        cout << word << endl;
    ```

12. ```cpp
    size_t CountPairs(string const &str, pair<char, char> const &chars)
    {
        size_t cnt{};

        for (auto it{str.cbegin()}; it != str.cend(); advance(it, 1))
            if (*it == chars.first && *next(it) == chars.second)
            {
                ++cnt;
                advance(it, 1);
            }

        return cnt;
    }

    size_t CountPairs(char const *str, pair<char, char> const &chars)
    {
        size_t cnt{};

        for (char const *p = str; *p; ++p)
            if (*p == chars.first && *++p == chars.second)
                ++cnt;

        return cnt;
    }
    ```

13. It generates roughly equivalent code with the default optimization level.
    When more optimization was requested, the compiler unrolled only the
    indexing loop.
