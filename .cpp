#include <iostream>
#include <string>
#include <vector>

std::string jsToCpp(const std::string& jsCode) {
    std::string cppCode;
    std::vector<std::string> lines;

    // Split JavaScript code by lines
    size_t pos = 0;
    while (pos < jsCode.size()) {
        size_t nextLineBreak = jsCode.find('\n', pos);
        lines.push_back(jsCode.substr(pos, nextLineBreak - pos));
        pos = nextLineBreak == std::string::npos ? std::string::npos : nextLineBreak + 1;
    }

    for (const auto& line : lines) {
        std::string trimmedLine = line;
        // Remove leading and trailing whitespaces
        size_t firstNonSpace = trimmedLine.find_first_not_of(" \t\r\n");
        if (firstNonSpace != std::string::npos)
            trimmedLine = trimmedLine.substr(firstNonSpace);

        if (trimmedLine.empty() || trimmedLine.substr(0, 2) == "//") {
            // Skip empty lines and comments
            continue;
        } else if (trimmedLine.find("var") == 0 || trimmedLine.find("let") == 0 || trimmedLine.find("const") == 0) {
            // Translate variable declaration
            size_t equalSignPos = trimmedLine.find('=');
            std::string varName = trimmedLine.substr(trimmedLine.find(' ') + 1, equalSignPos - trimmedLine.find(' ') - 1);
            std::string varValue = trimmedLine.substr(equalSignPos + 1);
            cppCode += "int " + varName + " = " + varValue + ";\n";
        } else if (trimmedLine.find("function") == 0) {
            // Function declaration
            size_t funcNamePos = trimmedLine.find(' ') + 1;
            size_t openParenPos = trimmedLine.find('(');
            std::string funcName = trimmedLine.substr(funcNamePos, openParenPos - funcNamePos);
            std::string funcParams = trimmedLine.substr(openParenPos + 1, trimmedLine.find(')') - openParenPos - 1);

            std::string funcBody;
            // Capture the function body
            for (size_t i = 0; i < lines.size(); ++i) {
                if (lines[i].find("}") != std::string::npos) {
                    funcBody += lines[i];
                    break;
                }
                funcBody += lines[i] + '\n';
            }

            // Replace '+' with ' + ', '-' with ' - ', '*' with ' * ', '/' with ' / '
            size_t pos = 0;
            while ((pos = funcBody.find_first_of("+-*/", pos)) != std::string::npos) {
                funcBody.insert(pos, " ");
                funcBody.insert(pos + 2, " ");
                pos += 3;
            }

            cppCode += "int " + funcName + "(" + funcParams + ") {\n" + funcBody + "}\n";
        }
    }

    return cppCode;
}

int main() {
    // Example JavaScript code
    std::string jsCode = R"(
        var x = 10;
        var y = 20;

        function add(a, b) {
            return a + b;
        }

        let result = add(x, y);
        console.log("Result:", result);
    )";

    // Translate JavaScript code to C++
    std::string cppCode = jsToCpp(jsCode);
    std::cout << "Translated C++ code:\n";
    std::cout << cppCode << std::endl;

    return 0;
}
