#include <stdio.h>
#include <iostream>
class Animal {
    public:
    virtual void bark() {
        std::cout << "bark like an animal" << std::endl;
    }
};

class Dog: public Animal {
    public:
    void bark() override {
        std::cout << "bark like a dog" << std::endl;
    }
};

int main() {
    Animal mypet = Dog();
    mypet.bark();
}