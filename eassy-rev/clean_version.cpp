#include <iostream>
#include <string>
#include <vector>
#include <map>

class StringTransformer {
private:
    const std::string sub_pairs = "_E}S{I978Z7rCHBPAhz}ybxtwvvfu3twsWrFqx6BpJ55oY4Vns3caub{cMd9eyfkglhRi8jGkC0_lg1nmj2XDUE1FLGmH4I0JiKDL6MoNaONPQQzRqSTTdU2VpWOXAYeZK";
    std::map<char, char> sub_map;
    const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_{}";

    void init_substitutions() {
        // Create substitution pairs from the string
        for (size_t i = 0; i < sub_pairs.length(); i += 2) {
            if (i + 1 < sub_pairs.length()) {
                sub_map[sub_pairs[i]] = sub_pairs[i + 1];
            }
        }
    }

    void transform1(char* data, int length) {
        // Substitute each character according to the mapping
        for (int i = 0; i < length; i++) {
            if (sub_map.find(data[i]) != sub_map.end()) {
                data[i] = sub_map[data[i]];
            }
        }
    }

    void transform2(std::string& str) {
        std::string temp;
        for (size_t i = 0; i < str.length(); i++) {
            temp += str[i];
            if ((i + 1) % 3 == 0) {
                temp += charset[i % charset.length()];
            }
        }
        str = temp;
    }

    void transform3(char* data, int length) {
        for (int i = 0; i < length; i++) {
            data[i] = data[i] % '@';
        }
    }

public:
    StringTransformer() {
        init_substitutions();
    }

    std::vector<int> process(const std::string& input) {
        if (input.empty()) return {};

        std::unique_ptr<char[]> buffer(new char[input.length() * 2 + 1]);
        strcpy(buffer.get(), input.c_str());
        int length = input.length();

        transform1(buffer.get(), length);
        std::string intermediate(buffer.get(), length);
        transform2(intermediate);
        
        length = intermediate.length();
        strcpy(buffer.get(), intermediate.c_str());
        transform3(buffer.get(), length);

        // Convert to vector of ints for output
        std::vector<int> result;
        for (int i = 0; i < length; i++) {
            result.push_back(static_cast<unsigned char>(buffer.get()[i]));
        }
        return result;
    }
};

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <string>" << std::endl;
        return 1;
    }

    StringTransformer transformer;
    auto result = transformer.process(argv[1]);

    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}