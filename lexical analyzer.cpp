#include <iostream>
#include <regex>
#include <map>
#include <vector>

using namespace std;

map<string, string> Make_Regex_Map() {
    return {
        {R"(\b(int|float|char|bool|if|else|while|for|return|main|cin|cout|using|namespace|std)\b)", "Keyword"},
        {R"(\b(include|define)\b)", "Preprocessor"},
        {R"(\b(iostream|stdio|string)\b)", "Library"},
        {R"([a-zA-Z_][a-zA-Z0-9_]*)", "Identifier"},
        {R"(\b\d+\b)", "Number"},
        {R"(\+|\-|\*|\/|=|==|<<|>>|<|>)", "Operator"},
        {R"(\{|\}|\(|\)|;|,)", "Symbol"}
    };
}

vector<pair<string, string>> Analyze_Code(const string& code) {
    map<string, string> patterns = Make_Regex_Map();
    vector<pair<string, string>> tokens;

    for (const auto& [pattern, type] : patterns) {
        regex re(pattern);
        auto begin = sregex_iterator(code.begin(), code.end(), re);
        auto end = sregex_iterator();

        for (auto it = begin; it != end; ++it) {
            tokens.push_back({ it->str(), type });
        }
    }

    return tokens;
}

int main() {
    string code;
    cout << "Enter your code:\n> ";
    getline(cin, code);

    auto tokens = Analyze_Code(code);

    cout << "\nLexeme\t\tToken\n------------------------------\n";
    for (const auto& [lexeme, token] : tokens) {
        cout << lexeme << "\t\t" << token << endl;
    }

    return 0;
}
