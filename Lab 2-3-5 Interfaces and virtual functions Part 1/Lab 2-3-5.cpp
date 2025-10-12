#include <iostream>
#include <string>

// ---------- Clase Base ----------
class Validator {
public:
    virtual bool isValid(std::string& text) = 0;
    virtual ~Validator() {}
};

// ---------- Clase derivada Validator ---> ExactValidator ----------
class ExactValidator : public Validator {
    std::string pattern;

public:
    ExactValidator(std::string& p) : pattern(p) {}

    bool isValid(std::string& text) override
    {
        return text == pattern;
    }
};

// ---------- MAIN ----------
int main() {
    std::string correctPassword;
    std::cout << "Set your password: ";
    std::cin >> correctPassword;

    ExactValidator validator(correctPassword);

    std::string attempt;
    std::cout << "Enter password to validate: ";
    std::cin >> attempt;

    if (validator.isValid(attempt)) 
    {
        std::cout << "The string ' " << attempt << "' is valid" << std::endl;
    }
    else
    {
        std::cout << "The string '" << attempt << "' is invalid" << std::endl;
    }

    return 0;
}
