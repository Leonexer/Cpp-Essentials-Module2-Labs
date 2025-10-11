#include <iostream>

class Tree {
public:
    virtual void draw() {   // Virtual para que se pueda hacer override en las subclases
        std::cout << "This is a generic tree." << std::endl;
    }
};

class PineTree : public Tree {
public:
    void draw() {
        std::cout << "   *   " << std::endl;
        std::cout << "  ***  " << std::endl;
        std::cout << " ***** " << std::endl;
        std::cout << "*******" << std::endl;
        std::cout << "  |||  " << std::endl;
    }
};

class OakTree : public Tree {
public:
    void draw() {
        std::cout << "  /**\\  " << std::endl;
        std::cout << " /****\\ " << std::endl;
        std::cout << "/******\\" << std::endl;
        std::cout << "  |||  " << std::endl;
    }
};

class PalmTree : public Tree {
public:
    void draw() {
        std::cout << "   ||   " << std::endl;
        std::cout << "  /**\\  " << std::endl;
        std::cout << " /***\\  " << std::endl;
        std::cout << "   ||   " << std::endl;
    }
};

int main()
{
    Tree* treeArray[3];

    PineTree pine;
    OakTree oak;
    PalmTree palm;

    treeArray[0] = &pine;
    treeArray[1] = &oak;
    treeArray[2] = &palm;

    for (int i = 0; i < 3; i++) {
        treeArray[i]->draw();  // Calls the correct version of draw()
        std::cout << std::endl;
    }

}

