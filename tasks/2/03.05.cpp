#include <iostream>

class Entity_v1
{
public:
    virtual void test() = 0;
    virtual ~Entity_v1() = default;
};

class Entity_v2
{
public:
    virtual void test() = 0;
    virtual ~Entity_v2() = default;
};

class Adapter_v1 : public Entity_v1
{
public:
    void test() override final
    {
        test_v1();
    }

    virtual void test_v1() = 0;
};

class Adapter_v2 : public Entity_v2
{
public:
    void test() override final
    {
        test_v2();
    }

    virtual void test_v2() = 0;
};

class Client : public Adapter_v1, public Adapter_v2
{
public:
    void test_v1() override
    {
        std::cout << "Client processing Entity_v1 task." << std::endl;
    }

    void test_v2() override
    {
        std::cout << "Client processing Entity_v2 task." << std::endl;
    }
};

int main()
{
    Client client;

    Entity_v1* e1 = &client;
    Entity_v2* e2 = &client;

    e1->test();
    e2->test();
}