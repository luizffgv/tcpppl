# X.10 Statements

---

The code solutions might have implicit `#include` and `using` directives, and be
assumed to be inside the `main` function.

---

1. ```cpp
   decltype(input_line)::size_type i{0};
   while (i != max_length)
       if (input_line[i++] == '?')
           quest_count++;
   ```

   ```cpp
   for (auto p{input_line.data()};
        distance(input_line.data(), p) != max_length;
        ++p)
       if (*p == '?')
           quest_count++;
   ```

   ```cpp
   for (auto const &ch : input_line)
       if (ch == '?')
           quest_count++;
   ```

2. It displays warnings in the first two cases and an error for the third.

   ```cpp
   int      a{5};  // Redefinition of a
   unsigned u{-2}; // Narrowing brace initialization

   return true; // Returning value in void function
   ```

   The compiler errors/warnings are similar to the comments.

3. Same as `memcpy` but crappy and for integers. Behaves incorrectly if count is
   zero, too. Writing something like that should be avoided like the plague
   unless it runs way better than `memcpy` in the target systems.

4. ```cpp
   int constexpr atoi(const char *str)
   {
       int  val{};
       bool negative{};

       if (*str == '-')
       { // Negative
           negative = true;
           ++str;
       }
       if (*str == '\'') // Character literal
           val = *++str;
       else if (*str == '0' && ++str)
           if (*str == 'X' || *str == 'x') // Hexadecimal
               while (*++str)
               {
                   auto constexpr hex_chtoi{[](unsigned char ch) constexpr
                                            {
                                                switch (ch)
                                                {
                                                case 'A':
                                                case 'a': return 0xA;
                                                case 'B':
                                                case 'b': return 0xB;
                                                case 'C':
                                                case 'c': return 0xC;
                                                case 'D':
                                                case 'd': return 0xD;
                                                case 'E':
                                                case 'e': return 0xE;
                                                case 'F':
                                                case 'f': return 0xF;
                                                default: return ch - '0';
                                                }
                                            }};

                   val = val * 0x10 + hex_chtoi(*str);
               }
           else // Octal
               while (*str)
                   val = val * 010 + *str++ - '0';
       else // Decimal
           while (*str)
               val = val * 10 + *str++ - '0';

       return negative ? -val : val;
   }
   ```

5. ```cpp
   void itoa(int i, char b[])
   {
       size_t len{i ? static_cast<size_t>(log10(abs(i))) + 1 : 1};

       if (i < 0)
       {
           ++len;
           *b = '-';
       }

       auto push{[cur{b + len - 1}](remove_reference_t<decltype(*b)> ch) mutable
                 { *cur-- = ch; }};

       do
           push('0' + abs(i) % 10);
       while (i /= 10);

       b[len] = '\0';
   }
   ```

6. ```cpp
   // If b_sz is not large enough, we return false and the contents of b are
   // undefined
   bool itoa(int i, char b[], size_t b_sz)
   {
       size_t len{i ? static_cast<size_t>(log10(abs(i))) + 1 : 1};

       if (i < 0)
       {
           ++len;
           *b = '-';
       }

       if (len + 1 > b_sz)
           return false;

       auto push{[cur{b + len - 1}](remove_reference_t<decltype(*b)> ch) mutable
                 { *cur-- = ch; }};

       do
           push('0' + abs(i) % 10);
       while (i /= 10);

       b[len] = '\0';

       return true;
   }
   ```

7. See `7/`.

8. N/A.
