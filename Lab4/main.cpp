#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

string read_file(const string &path) {
    ifstream source_stream(path);
    ostringstream string_stream;

    string_stream << source_stream.rdbuf();
    source_stream.close();

    return string_stream.str();
}

vector<string> get_cities_sentences(const string &source) {
    vector<string> cities_sentences;

    regex cities_regex(R"([^\n\t\.?!]*(Нижн[а-я]+ Новгород|Москв)[^\n\t.?!]*[\.!?])", regex::optimize);
    sregex_iterator regex_it(source.begin(), source.end(), cities_regex), end;
    for (; regex_it != end; regex_it++) {
        smatch match_res = *regex_it;
        string match_str = match_res.str();
        cities_sentences.push_back(match_str);
        cout << match_str << endl;
    }
    return cities_sentences;
}


void write_sentences(const string &path, const vector<string> &sentences) {
    ofstream output_stream(path);
    output_stream << "<cities_sentences>" << endl << endl;
    for (const string &s: sentences) {
        output_stream << "\t<t>" << s << "</t>" << endl << endl;
    }
    output_stream << "</cities_sentences>" << endl;
    output_stream.close();
}


int main() {
    string input_path = "/home/alexey/TFL/soloview.txt";
    string output_path = "/home/alexey/TFL/output.txt";

    string input = read_file(input_path);
    write_sentences(output_path, get_cities_sentences(input));

    return 0;
}
