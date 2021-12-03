# X.9 Structures, Unions, and Enumerations

1. ```cpp
   struct Big // 64 bytes
   {
       // The order kinda doesn't matter too much here
       bool        a;
       long double f;
       char        b;
       double      e;
       int         c;
       long        d;
   };

   struct Small // 48 bytes
   {
       long double a;
       double      b;
       long        c;
       int         d;
       char        e;
       bool        f;
   };
   ```

2. ```cpp
   const int         days[12]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
   const char *const months[12]{"January",
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

   cout << "|   Month    | Days |\n"
        << "|------------|------|\n";

   for (size_t month_i{}; month_i < 12; ++month_i)
       cout << "| " << setw(10) << left << months[month_i] << " | " << setw(4)
            << days[month_i] << " |\n";

   cout.flush();
   ```

   ```cpp
   struct Month
   {
       const char *name;
       int         days;
   };

   const Month months[12]{{"January", 31},
                          {"February", 28},
                          {"March", 31},
                          {"April", 30},
                          {"May", 31},
                          {"June", 30},
                          {"July", 31},
                          {"August", 31},
                          {"September", 30},
                          {"October", 31},
                          {"November", 30},
                          {"December", 31}};

   cout << "|   Month    | Days |\n"
        << "|------------|------|\n";

   for (auto const &month : months)
       cout << "| " << setw(10) << left << month.name << " | " << setw(4)
            << month.days << " |\n";

   cout.flush();
   ```

3. You could store the size of a `size_t` in a `size_t` as
   `size_t v{sizeof v};`.

4. ```cpp
   struct Date
   {
       uint_least8_t day;
       uint_least8_t month;
       unsigned      year;

       Date(istream &iss);
       Date(istream &&iss);
       Date(string const &str);
   };

   template <typename CharT, typename Traits>
   basic_ostream<CharT, Traits> &operator<<(basic_ostream<CharT, Traits> &os,
                                            Date const                   &d)
   {
       os << setfill('0') << setw(2) << (short)d.day << '/' << setw(2)
          << (short)d.month << '/' << d.year;

       return os;
   }

   template <typename CharT, typename Traits>
   basic_istream<CharT, Traits> &operator>>(basic_istream<CharT, Traits> &is,
                                            Date                         &d)
   {
       auto check_slash{[&is] {
           return is.get() == '/' ? true : (is.setstate(ios_base::failbit), false);
       }};

       // So basic_istream::operator>> treats input as an integer, since
       //  uint_least8_t might be a character type
       short tmp_integer;

       is >> tmp_integer;
       d.day = tmp_integer;
       if (!check_slash())
           return is;
       is >> tmp_integer;
       d.month = tmp_integer;
       if (!check_slash())
           return is;
       is >> d.year;

       return is;
   }

   Date::Date(istream &iss) { iss >> *this; }
   Date::Date(istream &&iss) : Date{iss} {}
   Date::Date(string const &str) : Date{istringstream{str}} {}
   ```
