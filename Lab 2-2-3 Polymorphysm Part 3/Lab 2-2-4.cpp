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

        return parts == 3; // debería tener 3 puntos (es una direccion ip)
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

// ---------- MAIN ----------
int main() {
    std::string ip_array[3];

    for (int i = 0; i < 3;i++)
    {
        std::cout << "Enter IP address " << i + 1 << ": " <<std::endl;
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
