#include "src.hpp"
#include <iostream>

struct TestClass {
    int value;
    TestClass(int v) : value(v) {
        std::cout << "Constructor: " << value << std::endl;
    }
    ~TestClass() {
        std::cout << "Destructor: " << value << std::endl;
    }
};

int main() {
    // Test 1: Default constructor
    {
        sjtu::unique_ptr<int> p1;
        std::cout << "Test 1: Default constructor - get() should be nullptr: " 
                  << (p1.get() == nullptr ? "PASS" : "FAIL") << std::endl;
    }
    
    // Test 2: Constructor from raw pointer
    {
        sjtu::unique_ptr<int> p2(new int(42));
        std::cout << "Test 2: Constructor from raw pointer - value: " 
                  << *p2 << " (expected 42): " 
                  << (*p2 == 42 ? "PASS" : "FAIL") << std::endl;
    }
    
    // Test 3: Move constructor
    {
        sjtu::unique_ptr<int> p3(new int(100));
        sjtu::unique_ptr<int> p4(std::move(p3));
        std::cout << "Test 3: Move constructor - p3 is nullptr: " 
                  << (p3.get() == nullptr ? "PASS" : "FAIL") << std::endl;
        std::cout << "Test 3: Move constructor - p4 value: " 
                  << *p4 << " (expected 100): " 
                  << (*p4 == 100 ? "PASS" : "FAIL") << std::endl;
    }
    
    // Test 4: Move assignment
    {
        sjtu::unique_ptr<int> p5(new int(200));
        sjtu::unique_ptr<int> p6(new int(300));
        p6 = std::move(p5);
        std::cout << "Test 4: Move assignment - p5 is nullptr: " 
                  << (p5.get() == nullptr ? "PASS" : "FAIL") << std::endl;
        std::cout << "Test 4: Move assignment - p6 value: " 
                  << *p6 << " (expected 200): " 
                  << (*p6 == 200 ? "PASS" : "FAIL") << std::endl;
    }
    
    // Test 5: reset()
    {
        sjtu::unique_ptr<int> p7(new int(400));
        p7.reset();
        std::cout << "Test 5: reset() - p7 is nullptr: " 
                  << (p7.get() == nullptr ? "PASS" : "FAIL") << std::endl;
    }
    
    // Test 6: release()
    {
        sjtu::unique_ptr<int> p8(new int(500));
        int* raw = p8.release();
        std::cout << "Test 6: release() - p8 is nullptr: " 
                  << (p8.get() == nullptr ? "PASS" : "FAIL") << std::endl;
        std::cout << "Test 6: release() - raw value: " 
                  << *raw << " (expected 500): " 
                  << (*raw == 500 ? "PASS" : "FAIL") << std::endl;
        delete raw;
    }
    
    // Test 7: operator->
    {
        sjtu::unique_ptr<TestClass> p9(new TestClass(600));
        std::cout << "Test 7: operator-> - value: " 
                  << p9->value << " (expected 600): " 
                  << (p9->value == 600 ? "PASS" : "FAIL") << std::endl;
    }
    
    // Test 8: make_unique
    {
        auto p10 = sjtu::make_unique<int>(700);
        std::cout << "Test 8: make_unique - value: " 
                  << *p10 << " (expected 700): " 
                  << (*p10 == 700 ? "PASS" : "FAIL") << std::endl;
    }
    
    // Test 9: Size constraint
    std::cout << "Test 9: Size constraint - sizeof(unique_ptr<int>): " 
              << sizeof(sjtu::unique_ptr<int>) 
              << " <= sizeof(void*): " << sizeof(void*)
              << " : " << (sizeof(sjtu::unique_ptr<int>) <= sizeof(void*) ? "PASS" : "FAIL") 
              << std::endl;
    
    std::cout << "\nAll tests completed!" << std::endl;
    return 0;
}
