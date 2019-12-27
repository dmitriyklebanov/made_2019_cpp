#include "parser.h"
#include "tester.hpp"

int test() {
    using TestFunc = std::function<bool(const std::vector<std::string>&,
        const std::vector<int>&, std::string&&)>;
    TestFunc test_func = [](
        const std::vector<std::string>& resultStringTokens,
        const std::vector<int>& resultIntTokens,
        std::string&& to_parse)
        {
            int start = 0;
            std::vector<std::string> stringTokens;
            std::vector<int> intTokens;
            int finish = 0;
            Parser parser = Parser()
                .registerOnStart([&start]() { start++; })
                .registerOnToken([&stringTokens](std::string token) {
                    stringTokens.emplace_back(std::move(token));
                })
                .registerOnToken([&intTokens](int token) {
                    intTokens.emplace_back(token);
                })
                .registerOnFinish([&finish]() { finish++; });
            parser.parse(std::move(to_parse));

            return start == 1 && finish == 1 && resultStringTokens == stringTokens &&
                resultIntTokens == intTokens;
        };
    Tester<TestFunc> parser_tester(test_func);

    parser_tester.execute(std::vector<std::string>{"test"},
        std::vector<int>{1, -1}, std::string("1 \ttest\n-1"));

    parser_tester.execute(std::vector<std::string>{},
        std::vector<int>{1, -1}, std::string("1\n\n -1"));

    parser_tester.execute(std::vector<std::string>{"abc", "def"},
        std::vector<int>{123}, std::string("abc\tdef\t123"));

    parser_tester.execute(std::vector<std::string>{"word"},
        std::vector<int>{-3}, std::string("\n\n\n -3 word\t \n"));

    parser_tester.execute(std::vector<std::string>{},
        std::vector<int>{}, std::string("\n"));

    parser_tester.execute(std::vector<std::string>{},
        std::vector<int>{}, std::string("\n   \t\n\t   "));

    parser_tester.execute(std::vector<std::string>{"-+12", "--2", "abc2d"},
        std::vector<int>{}, std::string("-+12\n\t--2\tabc2d"));

    parser_tester.execute(std::vector<std::string>{"-o"},
        std::vector<int>{0}, std::string("-0\n-o"));

    parser_tester.printStatistics();
    return parser_tester.getTotal() != parser_tester.getSuccess();
}

int main() {
    return test();
}
