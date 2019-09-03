#include <cassert>
#include <iostream>
#include <list>
#include <functional>
#include <memory>

#include "TestTools/initGaudi.h"
#include "TestTools/expect.h"
#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/ITHistSvc.h"
#include "AthenaKernel/getMessageSvc.h"

#include "AthenaMonitoring/ExampleClass.h"

using namespace std;
using namespace Monitored;

#define REGISTER_TEST_CASE(TEST_CASE_NAME) registerTestCase(&ExampleClassTestSuite::TEST_CASE_NAME, #TEST_CASE_NAME)

class ExampleClassTestSuite {
  // ==================== All registered test cases ====================
  private:
    list<function<void(void)>> registeredTestCases() {
      return {
        REGISTER_TEST_CASE(test_shouldCalculateProperValue),
      };
    }

  // ==================== Test code ====================
  private:
    void beforeEach() {
      // Prepare unit test environment
    }

    void afterEach() {
      // Clean up unit test environment
    }

    void test_shouldCalculateProperValue() {
      VALUE(m_testObj->calculate()) EXPECTED(7);
    }

  // ==================== Helper methods ====================
  private:

  // ==================== Initialization & run ====================
  public:
    ExampleClassTestSuite() 
      : m_log(Athena::getMessageSvc(), "ExampleClassTestSuite") {
    }

    void run() {
      for (function<void(void)> testCase : registeredTestCases()) {
        testCase();
      }
    }

  // ==================== Test case registration ====================
  private:
    typedef void (ExampleClassTestSuite::*TestCase)(void);

    function<void(void)> registerTestCase(TestCase testCase, const string& testCaseName) {
      return [this, testCase, testCaseName]() {
        m_log << MSG::INFO << "Current test case: " << testCaseName << endmsg;
        beforeEach();
        invoke(testCase, this);
        afterEach();
      };
    }

  // ==================== Properties ====================
  private:
    MsgStream m_log;

    shared_ptr<ExampleClass> m_testObj;
};

int main() {
  ISvcLocator* pSvcLoc;

  if (!Athena_test::initGaudi("GenericMon.txt", pSvcLoc)) {
    throw runtime_error("This test can not be run: GenericMon.txt is missing");
  }

  ExampleClassTestSuite().run();

  return 0;
}