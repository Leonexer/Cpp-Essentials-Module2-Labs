# Cpp-Essentials-Module2-Labs
## Laboratorios 2.2.2 – 2.2.4: Polimorfismo en C++

### Objetivo General

Estos laboratorios tienen como propósito familiarizar al estudiante con el **concepto de polimorfismo**, uno de los pilares de la **programación orientada a objetos (POO)**. A través de la implementación de jerarquías de clases con métodos virtuales y sobreescritura, se busca comprender cómo diferentes objetos pueden compartir una misma interfaz y responder de manera distinta según su tipo concreto.

---

### Polimorfismo: Parte 1–3

A lo largo de las tres partes de esta práctica, el estudiante aplica gradualmente los fundamentos del polimorfismo en C++:

- **Parte 1:** Introduce el uso de una clase base con un método virtual (`draw`) que es redefinido en clases derivadas, mostrando cómo una misma llamada puede producir resultados distintos según el tipo de objeto.
- **Parte 2:** Aplica el polimorfismo en un contexto más realista (un juego de damas), demostrando cómo las clases derivadas pueden implementar comportamientos específicos (movimientos distintos para piezas de tipo *man* y *king*).
- **Parte 3:** Consolida los conceptos anteriores mediante una jerarquía práctica que maneja direcciones IP, donde la clase derivada amplía la funcionalidad de la base, reutilizando y extendiendo su comportamiento.

Estos ejercicios muestran cómo el polimorfismo permite construir sistemas **flexibles, reutilizables y mantenibles**, en los cuales el código puede manejar objetos de distintas clases de forma uniforme a través de punteros o referencias a la clase base.

---

### Código final (Parte 3)

A continuación se muestra el código correspondiente al **laboratorio 2.2.4**, donde se implementa una jerarquía de clases que aplica los principios de polimorfismo aprendidos en las partes anteriores:

```cpp
#include <iostream>
#include <string>

// --------- Clase base ----------
class IPAddress {
protected:
    std::string address;
public:
    IPAddress(std::string addr = "") : address(addr) {}
    IPAddress(const IPAddress& other) { address = other.address; }
    std::string getAddress() { return address; }
    virtual void print() {
        std::cout << "IP Address: " << address << std::endl;
    }
};

//---------- Clase derivada IPAddress ---> IPAddressChecked ------------
class IPAddressChecked : public IPAddress {
    bool isCorrect;
    bool validateIP(std::string addr) {
        int parts = 0;
        std::string num = "";
        for (char c : addr) {
            if (c == '.') {
                if (num.empty() || std::stoi(num) < 0 || std::stoi(num) > 255) return false;
                num = "";
                parts++;
            } else if (isdigit(c)) {
                num += c;
            } else {
                return false;
            }
        }
        if (num.empty() || stoi(num) < 0 || stoi(num) > 255) {
            return false;
        }
        return parts == 3; // debería tener 3 puntos (es una direccion ip)
    }
public:
    IPAddressChecked(std::string addr = "") : IPAddress(addr) {
        isCorrect = validateIP(addr);
    }
    IPAddressChecked(const IPAddressChecked& other) : IPAddress(other) {
        isCorrect = other.isCorrect;
    }
    void print() override {
        IPAddress::print();
        std::cout << "Status: " << (isCorrect ? "Correct" : "Not Correct") << std::endl;
    }
};

// ---------- MAIN ----------
int main() {
    std::string ip_array[3];
    for (int i = 0; i < 3; i++) {
        std::cout << "Enter IP address " << i + 1 << ": " << std::endl;
        std::cin >> ip_array[i];
    }

    IPAddress ip1(ip_array[0]);
    IPAddressChecked check1(ip_array[1]);
    IPAddressChecked check2(ip_array[2]);

    std::cout << "\n--- Results ---\n";
    ip1.print();
    std::cout << std::endl;
    check1.print();
    std::cout << std::endl;
    check2.print();

    return 0;
}

```

### Conclusión
El conjunto de laboratorios sobre **polimorfismo en C++** de Cisco nos enseña cómo las clases pueden compartir una misma interfaz pero comportarse de manera distinta según sus necesidades específicas. Este principio se refleja de forma clara en el código proporcionado, donde una clase base (`IPAddress`) define una estructura común y un método virtual, mientras que la clase derivada (`IPAddressChecked`) amplía su funcionalidad para validar direcciones IP y mostrar su estado, de esta forma, el código nos muestra cómo el polimorfismo permite reutilizar y extender comportamientos **sin modificar la lógica original** (subrayo lo último porque es literalmente TODA la razón de usar polimorfismo) , un concepto clave en la programación orientada a objetos que también se aplica en los ejercicios anteriores (árboles y piezas de damas) para unificar acciones diversas bajo una misma interfaz.

## Laboratorios 2.3.5 – 2.3.7: Interfaces y Funciones Virtuales en C++

### Objetivo general
Estos laboratorios están diseñados para profundizar en el uso de **interfaces y funciones virtuales** dentro de la programación orientada a objetos (POO) en C++.  
El objetivo principal es comprender cómo las **interfaces** permiten definir comportamientos genéricos y cómo el **polimorfismo** hace posible que distintas clases los implementen de maneras específicas, fomentando la flexibilidad, reutilización y escalabilidad del código.

---

### Interfaces y Funciones Virtuales parte 1 - 3

A lo largo de estas tres partes, el estudiante aprende a **definir interfaces**, **crear múltiples implementaciones** y **combinar validaciones** para formar sistemas más complejos:

- En la primera parte, se introduce la idea de una **interfaz base** con métodos virtuales puros (como `Validator`), estableciendo un contrato que las clases derivadas deben cumplir.
- En la segunda parte, se amplía este concepto creando distintas implementaciones de validadores que aplican reglas específicas (longitud mínima, longitud máxima, patrones de coincidencia).
- Finalmente, en la tercera parte, se aplica el principio de **composición de objetos**, uniendo múltiples validadores en un **validador compuesto** que integra varias condiciones simultáneamente, ejemplificando un uso práctico del polimorfismo.

Estas tres fases reflejan cómo un sistema puede evolucionar desde una estructura simple hasta un modelo más **modular y extensible**, donde los comportamientos se definen mediante interfaces y se combinan dinámicamente en tiempo de ejecución.

---

### Código final (Parte 3)

El siguiente programa combina los conceptos aprendidos en las tres partes anteriores.   Implementa una jerarquía de validadores que, mediante herencia y funciones virtuales, permiten construir un **sistema flexible de validación de contraseñas** en el que se reutilizaron los métodos aplicados en los laboratorios parte 1 y 2.

```cpp
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

    bool isValid(std::string& text) override {
        return text.length() < maxLength;
    }
};

// ---------- Clase derivada Validator ---> PatternValidator ----------
class PatternValidator : public Validator {
    std::string pattern;

    bool matchChar(char patternChar, char textChar) {
        if (patternChar == 'D')
            return textChar >= '0' && textChar <= '9';
        if (patternChar == 'A')
            return (textChar >= 'A' && textChar <= 'Z') || (textChar >= 'a' && textChar <= 'z');
        if (patternChar >= 'a' && patternChar <= 'z') {
            char lowerText = (textChar >= 'A' && textChar <= 'Z') ? (textChar + 32) : textChar;
            return lowerText == patternChar;
        }
        return !((textChar >= 'A' && textChar <= 'Z') || 
                 (textChar >= 'a' && textChar <= 'z') || 
                 (textChar >= '0' && textChar <= '9'));
    }

public:
    PatternValidator(const std::string& p) : pattern(p) {}

    bool isValid(std::string& text) override {
        if (text.length() < pattern.length())
            return false;

        for (size_t i = 0; i <= text.length() - pattern.length(); ++i) {
            bool match = true;
            for (size_t j = 0; j < pattern.length(); ++j) {
                if (!matchChar(pattern[j], text[i + j])) {
                    match = false;
                    break;
                }
            }
            if (match) return true;
        }
        return false;
    }
};

// ---------- Composite Validator ----------
class CompositeValidator : public Validator {
    static const int MAX_VALIDATORS = 10;
    Validator* validators[MAX_VALIDATORS];
    int count;

public:
    CompositeValidator() : count(0) {
        for (int i = 0; i < MAX_VALIDATORS; ++i)
            validators[i] = nullptr;
    }

    void addValidator(Validator* v) {
        if (count < MAX_VALIDATORS)
            validators[count++] = v;
        else
            std::cout << "You can't add more validators to this composite validator" << std::endl;
    }

    bool isValid(std::string& text) override {
        for (int i = 0; i < count; ++i)
            if (!validators[i]->isValid(text))
                return false;
        return true;
    }

    ~CompositeValidator() {
        for (int i = 0; i < count; ++i)
            delete validators[i];
    }
};

// ---------- MAIN ----------
int main() {
    CompositeValidator* validator = new CompositeValidator();

    validator->addValidator(new MinLengthValidator(8));  // Mínimo 8 caracteres
    validator->addValidator(new PatternValidator("A"));  // Al menos una mayúscula
    validator->addValidator(new PatternValidator("a"));  // Al menos una minúscula
    validator->addValidator(new PatternValidator("D"));  // Al menos un dígito
    validator->addValidator(new PatternValidator("?"));  // Al menos un carácter especial

    while (true) {
        std::string password;
        std::cout << "--------- Password Validator ---------\n";
        std::cout << "The password must meet the following requirements:\n";
        std::cout << "- At least 8 characters\n";
        std::cout << "- At least one uppercase letter\n";
        std::cout << "- At least one lowercase letter\n";
        std::cout << "- At least one digit\n";
        std::cout << "- At least one special character\n";
        std::cout << "Enter password to validate: ";
        std::getline(std::cin, password);

        if (validator->isValid(password)) {
            std::cout << "Password is valid" << std::endl;
            break;
        } else {
            std::cout << "Password is invalid" << std::endl;
        }
    }

    delete validator;
    return 0;
}
```

### Conclusión

Al igual que en la anterior sección, estos laboratorios nos demuestran cómo el **polimorfismo** facilita la flexibilidad y escalabilidad en C++, permitiendo que distintas clases compartan una interfaz común pero que, aún sea el caso, se comporten de forma diferente, aunque en este caso lo apliquemos de una forma más profunda ahora orientado a los métodos y el ***override***. El ejercicio final (2.2.4) refleja su aplicación práctica, combinando **herencia, validación y métodos virtuales** para construir un sistema más robusto y reutilizable.



## Laboratorio 2.3.8 – Your Own Game

### Objetivo General

Este laboratorio busca que apliquemos de manera creativa los conceptos fundamentales de **programación orientada a objetos (POO)** en C++, mediante el diseño e implementación de un **juego interactivo completamente funcional**.  
El propósito principal es consolidar el uso de **clases, objetos, encapsulamiento, validación de datos y presentación de información**, modelando entidades del mundo real en un entorno de juego, aplicando todo lo que hemos visto en las secciones anteriores.

---

## Descripción del Proyecto

Para este ejercicio elegí desarrollar el clásico juego **“Tic Tac Toe” (también conocido como Gato)**.  
El programa debe permitir que dos jugadores participen por turnos en un tablero de 3x3, ingresando movimientos por consola y mostrando el estado actualizado del tablero en cada turno.  
El juego deb finalizar cuando uno de los jugadores logra alinear tres símbolos iguales (horizontal, vertical o diagonalmente) o cuando el tablero se llena, resultando en empate.

El diseño del código aplica los principios trabajados en los laboratorios anteriores (Polimorfismo Parte 1–3), en especial:
- **Encapsulamiento:** cada clase controla su propio comportamiento y atributos internos.  
- **Modelado de entidades:** se representan los elementos del juego (tablero, jugadores y partida) mediante clases.  
- **Interacción entre objetos:** la clase `Game` coordina el flujo del programa usando instancias de `Board` y `Player`.  
- **Validación y control de flujo:** se verifica la validez de los movimientos y se determina automáticamente si hay un ganador o empate.  

---

### Código del Juego “Tic Tac Toe”

```cpp
#include <iostream>
#include <string>

// ---------- Clase Board ----------
class Board {
private:
    char grid[3][3];

public:
    Board() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                grid[i][j] = ' ';
    }

    void print() {
        std::cout << "\n";
        for (int i = 0; i < 3; i++) {
            std::cout << " ";
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == ' ')
                    std::cout << ((3 * i) + j + 1);
                else
                    std::cout << grid[i][j];
                if (j < 2) std::cout << " | ";
            }
            std::cout << "\n";
            if (i < 2)
                std::cout << "---+---+---\n";
        }
        std::cout << "\n";
    }

    bool placeMark(int row, int col, char symbol) {
        if (row < 0 || row > 2 || col < 0 || col > 2)
            return false;
        if (grid[row][col] != ' ')
            return false;
        grid[row][col] = symbol;
        return true;
    }

    bool isFull() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (grid[i][j] == ' ')
                    return false;
        return true;
    }

    bool checkWin(char symbol) {
        for (int i = 0; i < 3; i++) {
            if (grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol)
                return true;
            if (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol)
                return true;
        }
        if (grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol)
            return true;
        if (grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol)
            return true;
        return false;
    }
};

// -------------------- Clase Player --------------------
class Player {
private:
    std::string name;
    char symbol;

public:
    Player(std::string n = "", char s = 'X') {
        name = n;
        symbol = s;
    }

    std::string getName() { return name; }
    char getSymbol() { return symbol; }
};

// -------------------- Clase Game --------------------
class Game {
private:
    Board board;
    Player player1;
    Player player2;
    Player* currentPlayer;

public:
    Game(std::string name1, std::string name2) : player1(name1, 'X'), player2(name2, 'O') {
        currentPlayer = &player1;
    }

    void switchTurn() {
        currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
    }

    void play() {
        int move;
        while (true) {
            board.print();
            std::cout << currentPlayer->getName() << " (" << currentPlayer->getSymbol() << "), elige una casilla (1-9): ";
            std::cin >> move;

            int row = (move - 1) / 3;
            int col = (move - 1) % 3;

            if (!board.placeMark(row, col, currentPlayer->getSymbol())) {
                std::cout << "Movimiento invalido. Intenta de nuevo." << std::endl;
                continue;
            }

            if (board.checkWin(currentPlayer->getSymbol())) {
                board.print();
                std::cout << currentPlayer->getName() << " ha ganado!" << std::endl;
                break;
            }

            if (board.isFull()) {
                board.print();
                std::cout << "Empate." << std::endl;
                break;
            }

            switchTurn();
        }
    }
};

// -------------------- Funcion principal --------------------
int main() {
    std::string n1, n2;
    std::cout << "=== Tic Tac Toe ===" << std::endl;
    std::cout << "Nombre del jugador 1 (X): ";
    std::cin >> n1;
    std::cout << "Nombre del jugador 2 (O): ";
    std::cin >> n2;

    Game partida(n1, n2);
    partida.play();
    return 0;
}

 ```
### Explicación del Código

El programa está estructurado en tres clases principales:

- **`Board` (Tablero):** controla la representación visual del tablero (lo más dificil si somos sinceros) y las reglas de validación de jugadas. Se encarga de mostrar el estado actual, registrar los movimientos y comprobar si hay un ganador cuando se cumpla la condición o si el tablero está lleno.

- **`Player` (Jugador):** almacena el nombre y el símbolo asignado (‘X’ u ‘O’). Representa a los jugadores y facilita la interacción con el flujo del juego. El nombre ayuda a la legibilidad del juego.

- **`Game` (Partida):** es la clase que organiza el juego. Coordina los turnos, verifica los resultados y mantiene el ciclo principal de la partida (el tan conocido *gameloop*) hasta que haya un ganador o empate, en ambos casos el juego acaba.

La interacción entre estas clases está diseñada para demostrar cómo la programación orientada a objetos nos puede permitir el **dividir responsabilidades en nuestro código**, mantener **claridad en el código** y más importantemente **reutilizar componentes**. Además, se aplican los principios aprendidos en los laboratorios anteriores (Polimorfismo, métodos virtuales, etc.)

## Laboratorio 2.4.3–2.4.4: Composition – Parte 1 y 2

### Objetivo general
Estos laboratorios introducen el **principio de composición en C++**, el cual permite **modelar entidades complejas a partir de la unión de objetos más simples**.  
En lugar de heredar comportamientos, la composición busca que las clases colaboren entre sí para representar estructuras del mundo real.

### Composiciones parte 1 - 2

- La **Parte 1** se centra en crear una clase `Network` que contiene varios objetos `IPAddress`, para lo cual reutilizé uno de los primeros códigos de estos laboratorios y cambiando su propósito para servir las intrucciones del ejercicio.
- La **Parte 2** lleva el concepto a un nivel más tangible mediante la construcción de un objeto `Car` compuesto por múltiples clases: `Engine`, `Wheel`, `Chassis`, `Light` y `Body`, donde se utiliza la composición de objetos a un nivel un tanto superficial.

Ambos ejercicios refuerzan la comprensión de cómo **una clase puede estar formada por instancias de otras clases**, enfatizando la modularidad, la reutilización y la organización jerárquica de los componentes del programa.

---

### Código del Laboratorio – Parte 1 y 2

```cpp
#include <iostream>
#include <string>

// ---------- Clase Engine ----------
class Engine 
{
private:
    std::string capacity;

public:
    Engine(std::string c = "1.0") : capacity(c) {}

    void print()
    {
        std::cout << "Engine: " << capacity << std::endl;
    }
};

// ---------- Clase Wheel ----------
class Wheel {
private:
    int size;

public:
    Wheel(int s = 16) : size(s) {}

    void print() 
    {
        std::cout << "Wheel: " << size << "inches" << std::endl;
    }
};

// ---------- Clase Chassis ----------
class Chassis {
private:
    std::string type;

public:
    Chassis(std::string t = "Normal") : type(t) {}

    void print() 
    {
        std::cout << "Chassis: " << type << std::endl;
    }
};

// ---------- Clase Light ----------
class Light {
private:
    std::string type;

public:
    Light(std::string t = "Type 1") : type(t) {}

    void print() {
        std::cout << "Light: " << type << std::endl;
    }
};

// ---------- Clase Body ----------
class Body {
private:
    std::string color;

public:
    Body(std::string c = "Black") : color(c) {}

    void print() 
    {
        std::cout << "Body: " << color << std::endl;
    }
};

// ---------- Clase Compuesta Car ----------
class Car {
private:
    Engine engine;
    Wheel wheels[4];
    Chassis chassis;
    Light lights[10];
    Body body;

public:
    Car() {
        lights[0] = Light("Type 1");
        lights[1] = Light("Type 1");
        lights[2] = Light("Type 2");
        lights[3] = Light("Type 2");
        lights[4] = Light("Type 3");
        lights[5] = Light("Type 3");
        lights[6] = Light("Type 4");
        lights[7] = Light("Type 4");
        lights[8] = Light("Type 5");
        lights[9] = Light("Type 5");
    }

    void print()
    {
        engine.print();
        for (int i = 0; i < 4; i++)
            wheels[i].print();
        chassis.print();
        for (int i = 0; i < 10; i++)
            lights[i].print();
        body.print();
    }
};

// ---------- MAIN ----------
int main() {
    Car myCar;
    myCar.print();
    return 0;
}
```

### Conclusión

Tanto el ejercicio de **la red con direcciones IP (Parte 1)** como el del **automóvil (Parte 2)** comparten el mismo propósito: **reforzar la comprensión de cómo estructurar objetos complejos a partir de componentes más pequeños**.

- En la **Parte 1**, el enfoque está en la administración de colecciones de objetos (`IPAddress` dentro de `Network`), lo que enseña cómo **manejar relaciones de uno a muchos**.
- En la **Parte 2**, se amplía la idea hacia **una composición jerárquica y multidimensional**, donde cada parte (motor, ruedas, luces, etc.) forma parte esencial de un todo (`Car`).

Ambos ejercicios subrayan la importancia de la **modularidad del código** y la **organización orientada a objetos**, aprovechando la propiedad de los objetos que están modelando de tener ***subpartes que pueden dividir en sus propios atributos***. Lo podemos pensar como un mueble armable, cada parte puede tener una cosa que la haga **única de otras de su mismo tipo** (Tipos de tornillo, Tipo de madera del marco, Marca del colchón, etc), donde puede ser relevante el tener acceso a esta información.
