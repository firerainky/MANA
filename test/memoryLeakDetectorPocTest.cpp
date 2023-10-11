// Memoryleak test for Gtest: third answer at https://stackoverflow.com/questions/2980917/c-is-it-possible-to-implement-memory-leak-testing-in-a-unit-test

#include "memoryLeakDetectorPocTest.h"
#include <cstdlib>// for malloc

class MyObject {

public:
    MyObject(int a, int b) : m_a(a), m_b(b) {
        std::cout << "MyObject::MyObject" << std::endl;
    }
    ~MyObject() { std::cout << "MyObject::~MyObject" << std::endl; }

private:
    int m_a;
    int m_b;
};

MemoryLeakDetectorPocTest::MemoryLeakDetectorPocTest() {
    std::cout << "MemoryLeakDetectorPocTest::MemoryLeakDetectorPocTest"
              << std::endl;
}

MemoryLeakDetectorPocTest::~MemoryLeakDetectorPocTest() {
    std::cout << "MemoryLeakDetectorPocTest::~MemoryLeakDetectorPocTest"
              << std::endl;
}

void MemoryLeakDetectorPocTest::SetUp() {
    std::cout << "MemoryLeakDetectorPocTest::SetUp" << std::endl;
}

void MemoryLeakDetectorPocTest::TearDown() {
    std::cout << "MemoryLeakDetectorPocTest::TearDown" << std::endl;
}

TEST_F(MemoryLeakDetectorPocTest, verifyNewAllocationForNativeType) {

    std::cout << "MemoryLeakDetectorPocTest::verifyNewAllocationForNativeType "
                 "- START"
              << std::endl;

    // allocate some bytes on the heap and intentially DONT release them...
    const size_t numOfCharsOnHeap = 23;
    std::cout << "size of char is:" << sizeof(char) << " bytes" << std::endl;
    std::cout << "allocating " << sizeof(char) * numOfCharsOnHeap
              << " bytes on the heap using new []" << std::endl;
    char *arr = new char[numOfCharsOnHeap];

    // DO NOT delete it on purpose...
    //delete [] arr;
    std::cout << "MemoryLeakDetectorPocTest::verifyNewAllocationForNativeType "
                 "- END"
              << std::endl;
}

TEST_F(MemoryLeakDetectorPocTest, verifyNewAllocationForUserDefinedType) {
    std::cout << "MemoryLeakDetectorPocTest::"
                 "verifyNewAllocationForUserDefinedType - START"
              << std::endl;

    std::cout << "size of MyObject is:" << sizeof(MyObject) << " bytes"
              << std::endl;
    std::cout << "allocating MyObject on the heap using new" << std::endl;
    MyObject *myObj1 = new MyObject(12, 17);

    delete myObj1;
    std::cout << "MemoryLeakDetectorPocTest::"
                 "verifyNewAllocationForUserDefinedType - END"
              << std::endl;
}

TEST_F(MemoryLeakDetectorPocTest, verifyMallocAllocationForNativeType) {
    std::cout << "MemoryLeakDetectorPocTest::"
                 "verifyMallocAllocationForNativeType - START"
              << std::endl;
    size_t numOfDoublesOnTheHeap = 3;
    std::cout << "MemoryLeakDetectorPocTest::"
                 "verifyMallocAllocationForNativeType - sizeof double is "
              << sizeof(double) << std::endl;
    std::cout << "MemoryLeakDetectorPocTest::"
                 "verifyMallocAllocationForNativeType - allocaitng "
              << sizeof(double) * numOfDoublesOnTheHeap << " bytes on the heap"
              << std::endl;
    double *arr = static_cast<double *>(
            malloc(sizeof(double) * numOfDoublesOnTheHeap));

    // NOT free-ing them on purpose !!
    // free(arr);
    std::cout << "MemoryLeakDetectorPocTest::"
                 "verifyMallocAllocationForNativeType - END"
              << std::endl;
}

TEST_F(MemoryLeakDetectorPocTest, verifyNewAllocationForNativeSTLVectorType) {
    std::cout << "MemoryLeakDetectorPocTest::"
                 "verifyNewAllocationForNativeSTLVectorType - START"
              << std::endl;
    std::vector<int> vecInt;
    vecInt.push_back(12);
    vecInt.push_back(15);
    vecInt.push_back(17);

    std::cout << "MemoryLeakDetectorPocTest::"
                 "verifyNewAllocationForNativeSTLVectorType - END"
              << std::endl;
}

TEST_F(MemoryLeakDetectorPocTest,
       verifyNewAllocationForUserDefinedSTLVectorType) {
    std::cout << "MemoryLeakDetectorPocTest::"
                 "verifyNewAllocationForUserDefinedSTLVectorType - START"
              << std::endl;
    std::vector<MyObject *> vecMyObj;
    vecMyObj.push_back(new MyObject(7, 8));
    vecMyObj.push_back(new MyObject(9, 10));

    size_t vecSize = vecMyObj.size();
    for (int i = 0; i < vecSize; ++i) { delete vecMyObj[i]; }

    std::cout << "MemoryLeakDetectorPocTest::"
                 "verifyNewAllocationForUserDefinedSTLVectorType - END"
              << std::endl;
}

TEST_F(MemoryLeakDetectorPocTest,
       verifyInPlaceAllocationAndDeAllocationForUserDefinedType) {
    std::cout << "MemoryLeakDetectorPocTest::"
                 "verifyInPlaceAllocationAndDeAllocationForUserDefinedType - "
                 "START"
              << std::endl;
    void *p1 = malloc(sizeof(MyObject));
    MyObject *p2 = new (p1) MyObject(12, 13);

    p2->~MyObject();
    std::cout
            << "MemoryLeakDetectorPocTest::"
               "verifyInPlaceAllocationAndDeAllocationForUserDefinedType - END"
            << std::endl;
}

TEST_F(MemoryLeakDetectorPocTest, verifyInPlaceAllocationForUserDefinedType) {
    std::cout << "MemoryLeakDetectorPocTest::"
                 "verifyInPlaceAllocationForUserDefinedType - START"
              << std::endl;
    void *p1 = malloc(sizeof(MyObject));
    MyObject *p2 = new (p1) MyObject(12, 13);

    // Dont delete the object on purpose !!
    //p2->~MyObject();
    std::cout << "MemoryLeakDetectorPocTest::"
                 "verifyInPlaceAllocationForUserDefinedType - END"
              << std::endl;
}