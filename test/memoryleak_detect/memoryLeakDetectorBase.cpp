#include <iostream>
#include <malloc.h>

#include "memoryLeakDetectorBase.h"

int g_numOfExtraBytesAllocatedByGtestUponTestFailure = 0;

static int display_mallinfo_and_return_uordblks() {
    struct mallinfo2 mi;

    mi = mallinfo2();
    std::cout << "========================================" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Total non-mmapped bytes (arena):" << mi.arena << std::endl;
    std::cout << "# of free chunks (ordblks):" << mi.ordblks << std::endl;
    std::cout << "# of free fastbin blocks (smblks):" << mi.smblks << std::endl;
    std::cout << "# of mapped regions (hblks):" << mi.hblks << std::endl;
    std::cout << "Bytes in mapped regions (hblkhd):" << mi.hblkhd << std::endl;
    std::cout << "Max. total allocated space (usmblks):" << mi.usmblks
              << std::endl;
    std::cout << "Free bytes held in fastbins (fsmblks):" << mi.fsmblks
              << std::endl;
    std::cout << "Total allocated space (uordblks):" << mi.uordblks
              << std::endl;
    std::cout << "Total free space (fordblks):" << mi.fordblks << std::endl;
    std::cout << "Topmost releasable block (keepcost):" << mi.keepcost
              << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    return mi.uordblks;
}

MemoryLeakDetectorBase::MemoryLeakDetectorBase()
    : m_ignoreMemoryLeakCheckForThisTest(false), m_isFirstTestRun(false),
      m_getSmartDiff(false),
      m_numOfBytesNotToConsiderAsMemoryLeakForThisTest(0) {
    std::cout << "MemoryLeakDetectorBase::MemoryLeakDetectorBase" << std::endl;
    m_firstCheck = display_mallinfo_and_return_uordblks();
}

MemoryLeakDetectorBase::~MemoryLeakDetectorBase() {
    std::cout << "MemoryLeakDetectorBase::~MemoryLeakDetectorBase" << std::endl;
    m_secondCheck = display_mallinfo_and_return_uordblks();
    PerformMemoryCheckLogic();
}

void MemoryLeakDetectorBase::PerformMemoryCheckLogic() {
    if (m_isFirstTestRun) {
        std::cout << "MemoryLeakDetectorBase::PerformMemoryCheckLogic - after "
                     "the first test"
                  << std::endl;
        int diff = m_secondCheck - m_firstCheck;
        if (diff > 0) {
            std::cout << "MemoryLeakDetectorBase::PerformMemoryCheckLogic - "
                         "setting "
                         "g_numOfExtraBytesAllocatedByGtestUponTestFailure to:"
                      << diff << std::endl;
            g_numOfExtraBytesAllocatedByGtestUponTestFailure = diff;
        }
        return;
    }

    if (m_ignoreMemoryLeakCheckForThisTest) { return; }
    std::cout << "MemoryLeakDetectorBase::PerformMemoryCheckLogic" << std::endl;

    int naiveDiff = m_secondCheck - m_firstCheck;

    // in case you wish for "more accurate" difference calculation call this method
    if (m_getSmartDiff) { getSmartDiff(naiveDiff); }

    EXPECT_EQ(m_firstCheck, m_secondCheck);
    std::cout << "MemoryLeakDetectorBase::PerformMemoryCheckLogic - the "
                 "difference is:"
              << naiveDiff << std::endl;
}

void MemoryLeakDetectorBase::getSmartDiff(int naiveDiff) {
    // according to some invastigations and assumemptions, it seems like once there is at least one
    // allocation which is not handled - GTest allocates 32 bytes on the heap, so in case the difference
    // prior for any further substrcutions is less than 32 - we will assume that the test does not need to
    // go over memory leak check...
    std::cout << "MemoryLeakDetectorBase::"
                 "getMoreAccurateAmountOfBytesToSubstructFromSecondMemoryCheck "
                 "- start"
              << std::endl;
    if (naiveDiff <= 32) {
        std::cout << "MemoryLeakDetectorBase::getSmartDiff - the naive diff <= "
                     "32 - ignoring..."
                  << std::endl;
        return;
    }

    size_t numOfBytesToReduceFromTheSecondMemoryCheck =
            m_numOfBytesNotToConsiderAsMemoryLeakForThisTest +
            g_numOfExtraBytesAllocatedByGtestUponTestFailure;
    m_secondCheck -= numOfBytesToReduceFromTheSecondMemoryCheck;
    std::cout << "MemoryLeakDetectorBase::getSmartDiff - substructing "
              << numOfBytesToReduceFromTheSecondMemoryCheck << std::endl;
}

void MemoryLeakDetectorBase::SetUp() {
    std::cout << "MemoryLeakDetectorBase::SetUp" << std::endl;
}

void MemoryLeakDetectorBase::TearDown() {
    std::cout << "MemoryLeakDetectorBase::TearDown" << std::endl;
}

// The actual test of this module:


TEST_F(MemoryLeakDetectorBase,
       getNumOfExtraBytesGTestAllocatesUponTestFailureTest) {
    std::cout << "MemoryLeakDetectorPocTest::"
                 "getNumOfExtraBytesGTestAllocatesUponTestFailureTest - START"
              << std::endl;

    // Allocate some bytes on the heap and DO NOT delete them so we can find out the amount
    // of extra bytes GTest framework allocates upon a failure of a test.
    // This way, upon our legit test failure, we will be able to determine of many bytes were NOT
    // deleted EXACTLY by our test.

    std::cout << "MemoryLeakDetectorPocTest::"
                 "getNumOfExtraBytesGTestAllocatesUponTestFailureTest - size "
                 "of char:"
              << sizeof(char) << std::endl;
    char *pChar = new char('g');
    SetIsFirstCheckRun();
    std::cout << "MemoryLeakDetectorPocTest::"
                 "getNumOfExtraBytesGTestAllocatesUponTestFailureTest - END"
              << std::endl;
}