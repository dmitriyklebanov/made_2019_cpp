#include <iostream>

#include "format/format.hpp"
#include "lib/tester.hpp"

int formatTest() {
    Tester format_tester;

    format_tester.execute("1 two test 3.1", false, "{0} {1} test {2}", 1, "two", 3.1);
    format_tester.execute("1 interesting 3.1 test four", false,
        "{0} interesting {2} test {3}", 1, "two", 3.1, "four");
    format_tester.execute("1 very 1 interesting 3.1 test four", false,
        "{0} very {1} interesting {2} test {3}", 1, true, 3.1, "four");
    format_tester.execute("abc; 3", false, "{0000}; {00001}", "abc", 3);
    format_tester.execute("", true, "{-1}; {00001}", "abc", 3);
    format_tester.execute("", true, "{abc{ads}}; {00001}");
    format_tester.execute("", true, "{0}}", "abc");
    format_tester.execute("", true, "{{0}", "abc");
    format_tester.execute("", true, "{{0}}", "abc");
    format_tester.execute("", true, "{0}; {1}; {2}", "abc", "def");

    format_tester.printStatistics();
    return format_tester.getTotal() != format_tester.getSuccess();
}


int main() {
    return formatTest();
}
