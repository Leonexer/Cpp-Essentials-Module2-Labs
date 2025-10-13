#include <iostream>
#include <string>

// --------- Clase base ----------
class IPAddress {
protected:
    std::string address;

public:
    IPAddress(std::string addr = "") : address(addr) {}
    IPAddress(const IPAddress& other)
    {
        address = other.address;
    }

    std::string getAddress()
    {
        return address;
    }

    virtual void print()
    {
        std::cout << "IP Address: " << address << std::endl;
    }
};

//---------- Clase derivada IPAddress ---> IPAddressChecked ------------
class IPAddressChecked : public IPAddress {
    bool isCorrect;

    bool validateIP(std::string addr)
    {
        int parts = 0;
        std::string num = "";

        for (char c : addr) {
            if (c == '.') {
                if (num.empty() || std::stoi(num) < 0 || std::stoi(num) > 255)
                    return false;
                num = "";
                parts++;
            }
            else if (isdigit(c)) {
                num += c;
            }
            else {
                return false;
            }
        }

        if (num.empty() || stoi(num) < 0 || stoi(num) > 255)
        {
            return false;
        }

        return parts == 3;
    }

public:
    IPAddressChecked(std::string addr = "") : IPAddress(addr)
    {
        isCorrect = validateIP(addr);
    }

    IPAddressChecked(const IPAddressChecked& other) : IPAddress(other)
    {
        isCorrect = other.isCorrect;
    }

    void print() override {
        IPAddress::print();
        std::cout << "Status: " << (isCorrect ? "Correct" : "Not Correct") << std::endl;
    }
};

// ---------- Clase Network ----------
class Network {
private:
    std::string name;
    IPAddress* addresses[10];
    int count;

public:
    Network(std::string n = "") : name(n), count(0) {}

    void add(IPAddress* ip)
    {
        if (count < 10) 
        {
            addresses[count] = ip;
            count++;
        }
        else 
        {
            std::cout << "Network full, cannot add more IPs." << std::endl;
        }
    }

    void print()
    {
        std::cout << "\n=== Network: " << name << " ===" << std::endl;
        for (int i = 0; i < count; i++) 
        {
            addresses[i]->print();
            std::cout << std::endl;
        }
    }
};

// ---------- MAIN ----------
int main() {
    std::string ip_inputs[5];

    // Obtener 5 direcciones IP del usuario
    for (int i = 0; i < 5; i++) {
        std::cout << "Enter IP address " << i + 1 << ": ";
        std::cin >> ip_inputs[i];
    }

    IPAddress ip1(ip_inputs[0]);
    IPAddress ip2(ip_inputs[1]);
    IPAddress ip3(ip_inputs[2]);
    IPAddress ip4(ip_inputs[3]);
    IPAddress ip5(ip_inputs[4]);

    Network netA("Office Network");
    Network netB("Home Network");

    // Agrego las direcciones
    netA.add(&ip1);
    netA.add(&ip2);
    netA.add(&ip3);

    netB.add(&ip3);  // ip3 está en ambas redes
    netB.add(&ip4);
    netB.add(&ip5);

    // Se imprimen ambas redes
    netA.print();
    netB.print();

    return 0;
}