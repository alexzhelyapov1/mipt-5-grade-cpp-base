#include <iostream>

class Entity;

class EntityAttorney
{
    static void call_v1(Entity& e);
    static void call_v2(Entity& e);

    friend class Tester_v1;
    friend class Tester_v2;
};

class Entity
{
    friend class EntityAttorney;

    void test_v1()
    {
        std::cout << "Entity::test_v1 executed." << std::endl;
    }

    void test_v2()
    {
        std::cout << "Entity::test_v2 executed." << std::endl;
    }

public:
    Entity() = default;
};

void EntityAttorney::call_v1(Entity& e)
{
    e.test_v1();
}

void EntityAttorney::call_v2(Entity& e)
{
    e.test_v2();
}

class Tester_v1
{
public:
    void run(Entity& e)
    {
        std::cout << "[Tester_v1] Running test..." << std::endl;
        EntityAttorney::call_v1(e);
    }
};

class Tester_v2
{
public:
    void run(Entity& e)
    {
        std::cout << "[Tester_v2] Running test..." << std::endl;
        EntityAttorney::call_v2(e);
    }
};

int main()
{
    Entity entity;
    Tester_v1 t1;
    Tester_v2 t2;

    t1.run(entity);
    t2.run(entity);
}