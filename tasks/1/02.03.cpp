#include <iostream>

int main() {
    char c = 0;
    std::cin >> c;

    switch (c) {
        case 'A' ... 'Z':
            std::cout << "Uppercase letter" << std::endl;
            break;
        case 'a' ... 'z':
            std::cout << "Lowercase letter" << std::endl;
            break;
        case '0' ... '9':
            std::cout << "Digit" << std::endl;
            break;
        case '!': case '"': case '#': case '$': case '%': case '&': case '\'':
        case '(': case ')': case '*': case '+': case ',': case '-': case '.': case '/':
        case ':': case ';': case '<': case '=': case '>': case '?': case '@':
        case '[': case '\\': case ']': case '^': case '_': case '`':
        case '{': case '|': case '}': case '~':
            std::cout << "Punctuation" << std::endl;
            break;
        default:
            std::cout << "Other" << std::endl;
            break;
    }

    return 0;
}

// Pedantic output:
// -- Build files have been written to: /home/alex/mipt/cpp-base/build
// [1/2] Building CXX object tasks/1/CMakeFiles/02.03.dir/02.03.cpp.o
// /home/alex/mipt/cpp-base/tasks/1/02.03.cpp: In function ‘int main()’:
// /home/alex/mipt/cpp-base/tasks/1/02.03.cpp:8:9: warning: range expressions in switch statements are non-standard [-Wpedantic]
//     8 |         case 'A' ... 'Z':
//       |         ^~~~
// /home/alex/mipt/cpp-base/tasks/1/02.03.cpp:11:9: warning: range expressions in switch statements are non-standard [-Wpedantic]
//    11 |         case 'a' ... 'z':
//       |         ^~~~
// /home/alex/mipt/cpp-base/tasks/1/02.03.cpp:14:9: warning: range expressions in switch statements are non-standard [-Wpedantic]
//    14 |         case '0' ... '9':
//       |         ^~~~
// [2/2] Linking CXX executable tasks/1/02.03
