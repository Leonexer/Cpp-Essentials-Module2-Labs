#include <iostream>
#include <string>

// ---------- Clase Base ----------

class Validator {
public:
    virtual bool isValid(std::string& text) = 0;
    virtual ~Validator() {}
};

// ---------- ExactValidator ----------
class ExactValidator : public Validator {
    std::string pattern;
public:
    ExactValidator(std::string& p) : pattern(p) {}

    bool isValid(std::string& text) override {
        return text == pattern;
    }
};

// ---------- MinLengthValidator ----------

class MinLengthValidator : public Validator {
    size_t minLength;
public:
    MinLengthValidator(size_t len) : minLength(len) {}

    bool isValid(std::string& text) override {
        return text.length() > minLength;
    }
};

// ---------- MaxLengthValidator ----------

class MaxLengthValidator : public Validator {
    size_t maxLength;
public:
    MaxLengthValidator(size_t len) : maxLength(len) {}

    bool isValid(std::string& text) override 
    {
        return text.length() < maxLength;
    }
};

// ---------- PatternValidator ----------

class PatternValidator : public Validator {
    std::string pattern;

    bool matchChar(char patternChar, char textChar) //Aquí está la salsa jaja
    {

        // D = Digito decimal
        if (patternChar == 'D')
        {
            return textChar >= '0' && textChar <= '9';
        }

        // A = Letra (mayuscula o minuscula)
        if (patternChar == 'A')
        {
            return (textChar >= 'A' && textChar <= 'Z') || (textChar >= 'a' && textChar <= 'z');
        }

        // ? = Cualquier caracter
        if (patternChar == '?')
        {
            return true;
        }

        // letra minuscula -> Coincide sin importar mayusculas (se suma a su valor ASCII 32 y después se compara)
        if (patternChar >= 'a' && patternChar <= 'z') 
        {
            char lowerText = (textChar >= 'A' && textChar <= 'Z') ? (textChar + 32) : textChar;
            return lowerText == patternChar;
        }

        // Cualquier otro simbolo debe coincidir exactamente
        return textChar == patternChar;
    }

public:

    PatternValidator(std::string& p) : pattern(p) {}
    
    bool isValid(std::string& text) override 
    {
        if (text.length() < pattern.length())
            return false;

        for (size_t i = 0; i <= text.length() - pattern.length(); ++i) //Se recorre el strong para buscar una coincidencia para el inicio del patrón
        {
            bool match = true;

            for (size_t j = 0; j < pattern.length(); ++j) //Recorre el string para comparar el patron y el string.
            {
                if (!matchChar(pattern[j], text[i + j])) 
                {
                    match = false;
                    break;
                }
            }

            if (match) return true; //En caso que se haya encontrado el patron simplemente devuelve true, sino,
        }                           //se sigue recorriendo el inicio de un posible patron y comparando. 
        return false;               //Si no existe el patron en ningun punto del string, devuelve false.
    }
};

// ---------- MAIN ----------
int main() {
    std::string pass = "Secret";
    ExactValidator exact(pass);
    std::string minInput = "abcd";
    std::string maxInput = "abcdefghijklmn";
    std::string pattern = "AA-DDD";
    std::string patternInput = "NE-785";

    MinLengthValidator minVal(3);
    MaxLengthValidator maxVal(10);
    PatternValidator patVal(pattern);

    std::cout << "ExactValidator:\n";
    std::cout << (exact.isValid(pass) ? "Valid" : "Invalid") << "\n\n";

    std::cout << "MinLengthValidator:\n";
    std::cout << (minVal.isValid(minInput) ? "Valid" : "Invalid") << "\n\n";

    std::cout << "MaxLengthValidator:\n";
    std::cout << (maxVal.isValid(maxInput) ? "Valid" : "Invalid") << "\n\n";

    std::cout << "PatternValidator:\n";
    std::cout << (patVal.isValid(patternInput) ? "Valid" : "Invalid") << "\n";

    return 0;
}
