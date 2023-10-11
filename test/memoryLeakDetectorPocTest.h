#include "memoryLeakDetectorBase.h"
#include "gtest/gtest.h"

// The fixture for testing class Foo.
class MemoryLeakDetectorPocTest : public MemoryLeakDetectorBase {
protected:
    // You can do set-up work for each test here.
    MemoryLeakDetectorPocTest();

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~MemoryLeakDetectorPocTest();

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp();

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown();
};