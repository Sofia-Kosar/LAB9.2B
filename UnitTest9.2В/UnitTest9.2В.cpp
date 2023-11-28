#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB9.2B/LAB9.2B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace YourProjectNamespace {
    TEST_CLASS(StudentTests) {
public:
    TEST_METHOD(TestCreateFunction) {
        const int N = 2;     
        Student* p = new Student[N];
        std::stringstream input;
        input << " Іваненко\n1\n0\n5\n4\n3\n";
        std::streambuf* originalCin = std::cin.rdbuf();
        std::cin.rdbuf(input.rdbuf());
        Create(p, N);
        std::cin.rdbuf(originalCin);
        Assert::AreEqual(std::string("Іваненко"), p[0].prizv);          
        Assert::AreEqual(5, p[0].physics);
        Assert::AreEqual(4, p[0].math);   
        Assert::AreEqual(3, p[0].program);
        delete[] p;
    }
    };
}