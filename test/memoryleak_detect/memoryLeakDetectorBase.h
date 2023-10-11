#include "gtest/gtest.h"

extern int g_numOfExtraBytesAllocatedByGtestUponTestFailure;

// The fixture for testing class Foo.
class MemoryLeakDetectorBase : public ::testing::Test {
    // methods:
    // -------
public:
    void SetIgnoreMemoryLeakCheckForThisTest() {
        m_ignoreMemoryLeakCheckForThisTest = true;
    }
    void SetIsFirstCheckRun() { m_isFirstTestRun = true; }

protected:
    // You can do set-up work for each test here.
    MemoryLeakDetectorBase();

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~MemoryLeakDetectorBase();

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp();

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown();

private:
    void getSmartDiff(int naiveDiff);
    // Add the extra memory check logic according to our
    // settings for each test (this method is invoked right
    // after the Dtor).
    virtual void PerformMemoryCheckLogic();

    // members:
    // -------
private:
    bool m_ignoreMemoryLeakCheckForThisTest;
    bool m_isFirstTestRun;
    bool m_getSmartDiff;
    size_t m_numOfBytesNotToConsiderAsMemoryLeakForThisTest;
    int m_firstCheck;
    int m_secondCheck;
};