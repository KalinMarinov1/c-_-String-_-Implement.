#include "kstring_h.h"

using namespace kalin;

int main() {
    Kstring s1 = "Hello, lady!";
    std::cout << s1;
    Kstring s2{"Bonjour!"};
    std::cout << "\n" <<s2;
    Kstring s3("What a lovely weather we've got here.");
    s1 = "Yes, indeed.";
    std::cout << "\n" << s3 << "\n" << s1;


    if (s1 > s2)
        std::cout << "\n" << "Unexpected";
    else
        std::cout << "\n" << "Even more unexpected";

    s1 += "a ";
    s1 += s2;
    std::cout << s1;

}