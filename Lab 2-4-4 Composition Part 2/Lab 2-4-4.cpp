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
        // Configurar los 10 focos (que horror)
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

    void print() //Se imprime el carro por partes
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
