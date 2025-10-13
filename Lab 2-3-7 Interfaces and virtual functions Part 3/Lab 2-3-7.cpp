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
    ExactValidator(const std::string& p) : pattern(p) {}

    bool isValid(std::string& text) override {
        return text == pattern;
    }
};

// ---------- Clase derivada Validator ---> MinLengthValidator --------

class MinLengthValidator : public Validator {
    size_t minLength;
public:
    MinLengthValidator(size_t len) : minLength(len) {}

    bool isValid(std::string& text) override {
        return text.length() > minLength;
    }
};

// ---------- Clase derivada Validator ---> MaxLengthValidator ----------

class MaxLengthValidator : public Validator {
    size_t maxLength;
public:
    MaxLengthValidator(size_t len) : maxLength(len) {}

    bool isValid(std::string& text) override
    {
        return text.length() < maxLength;
    }
};

// ---------- Clase derivada Validator ---> PatternValidator ----------

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

        // letra minuscula -> Coincide sin importar mayusculas (se suma a su valor ASCII 32 y después se compara)
        if (patternChar >= 'a' && patternChar <= 'z') 
        {
            char lowerText = (textChar >= 'A' && textChar <= 'Z') ? (textChar + 32) : textChar;
            return lowerText == patternChar;
        }

        // En este caso, un caracter especial (cualquiera que no sea letra mayuscula o minuscula ni decimal
        return !((textChar >= 'A' && textChar <= 'Z') || (textChar >= 'a' && textChar <= 'z') || (textChar >= '0' && textChar <= '9'));
    }

public:

    PatternValidator(const std::string& p) : pattern(p) {}

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


// ---------- Composite Validator ----------
class CompositeValidator : public Validator {
    static const int MAX_VALIDATORS = 10;   // Esta vez vamos a usar 5 validators
    Validator* validators[MAX_VALIDATORS];
    int count;

public:

    CompositeValidator() : count(0)
    {
        for (int i = 0; i < MAX_VALIDATORS; ++i) 
        {
            validators[i] = nullptr;
        }
    }

    void addValidator(Validator* v) 
    {
        if (count < MAX_VALIDATORS) 
        {
            validators[count++] = v;
        }
        else {
            std::cout << "You can't add more validators to this composite validator" << std::endl;
        }
    }

    bool isValid(std::string& text) override  //Revisa que TODOS los validators se cumplan en el string
    {
        for (int i = 0; i < count; ++i) 
        {
            if (!validators[i]->isValid(text)) 
            {
                return false;
            }
        }
        return true;
    }

    ~CompositeValidator() {
        for (int i = 0; i < count; ++i) 
        {
            delete validators[i];
        }
    }
};

// ---------- MAIN ----------
int main() {

    CompositeValidator* validator = new CompositeValidator(); //El validator compuesto que alamacenará el resto

    validator->addValidator(new MinLengthValidator(8));  // Minimo 8 caracteres
    validator->addValidator(new PatternValidator("A")); // al menos una mayuscula
    validator->addValidator(new PatternValidator("a")); // al menos una minuscula
    validator->addValidator(new PatternValidator("D")); // al menos un digito
    validator->addValidator(new PatternValidator("?")); // al menos un caracter especial

    while (true)
    {
        std::string password;
        std::cout << "--------- Password Validator ---------";
        std::cout << "The password must meet the following requierements:" << std::endl;
        std::cout << "- At least 8 characters" << std::endl;
        std::cout << "- At least one uppercase letter" << std::endl;
        std::cout << "- At least one lowercase letter" << std::endl;
        std::cout << "- At least one digit" << std::endl;
        std::cout << "- At least one special character" << std::endl;
        std::cout << "Enter password to validate: ";
        std::getline(std::cin, password);

        // Validar
        if (validator->isValid(password))
        {
            std::cout << "Password is valid" << std::endl;
            break;
        }
        else
        {
            std::cout << "Password is invalid" << std::endl;
        }
    }

    delete validator;
    return 0;

}