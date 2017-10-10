#include <iostream>
#include <string>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>

#include "main.hpp"

using namespace CppUnit;
using namespace std;

/******************** Test class for Monster class**********************/
class TestMonster : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestMonster);
    CPPUNIT_TEST(testgetNumber);
    CPPUNIT_TEST(testgetCity);
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp(void);
    void tearDown(void);

  protected:
    void testgetNumber(void);
    void testgetCity(void);

  private:
    Monster *monsterObj;
};

void TestMonster::testgetNumber(void)
{
    CPPUNIT_ASSERT(5 == monsterObj->getNumber());
}

void TestMonster::testgetCity(void)
{
    CPPUNIT_ASSERT("London" == monsterObj->getCity());
}

void TestMonster::setUp(void)
{
    monsterObj = new Monster(5, "London");
}

void TestMonster::tearDown(void)
{
    delete monsterObj;
}

/*************** Test class for City class ************************************/
class TestCity : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestCity);
    CPPUNIT_TEST(testGetMonster1);
    CPPUNIT_TEST(testGetMonster2);
    CPPUNIT_TEST(testGetName);
    CPPUNIT_TEST(testGetEast);
    CPPUNIT_TEST(testGetWest);
    CPPUNIT_TEST(testGetSouth);
    CPPUNIT_TEST(testGetNorth);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp(void);
    void tearDown(void);

  protected:
    void testGetMonster1(void);
    void testGetMonster2(void);
    void testGetName(void);
    void testGetEast(void);
    void testGetWest(void);
    void testGetSouth(void);
    void testGetNorth(void);

  private:
    City *cityObj;
};

void TestCity::testGetMonster1(void)
{
    Monster *obj;
    obj = cityObj->getMonster1();
    CPPUNIT_ASSERT(5 == obj->getNumber());
}

void TestCity::testGetMonster2(void)
{
    Monster *obj;
    obj = cityObj->getMonster2();
    CPPUNIT_ASSERT(6 == obj->getNumber());
}

void TestCity::testGetName(void)
{
    CPPUNIT_ASSERT("London" == cityObj->getName());
}

void TestCity::testGetEast(void)
{
    CPPUNIT_ASSERT("x" == cityObj->getEast());
}

void TestCity::testGetWest(void)
{
    CPPUNIT_ASSERT("y" == cityObj->getWest());
}

void TestCity::testGetSouth(void)
{
    CPPUNIT_ASSERT("a" == cityObj->getSouth());
}

void TestCity::testGetNorth(void)
{
    CPPUNIT_ASSERT("b" == cityObj->getNorth());
}

void TestCity::setUp(void)
{
    cityObj = new City("London", "x", "y", "a", "b");
    Monster *mobj1 = new Monster(5, "London");
    Monster *mobj2 = new Monster(6, "Leeds");
    cityObj->setMonster1(mobj1);
    cityObj->setMonster2(mobj2);
}

void TestCity::tearDown(void)
{
    delete cityObj;
}

/***************** Actual test runner ***********************************/

CPPUNIT_TEST_SUITE_REGISTRATION(TestMonster);
CPPUNIT_TEST_SUITE_REGISTRATION(TestCity);

int main(int argc, char *argv[])
{
    // informs test-listener about testresults
    CPPUNIT_NS::TestResult testresult;

    // register listener for collecting the test-results
    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener(&collectedresults);

    // register listener for per-test progress output
    CPPUNIT_NS::BriefTestProgressListener progress;
    testresult.addListener(&progress);

    // insert test-suite at test-runner by registry
    CPPUNIT_NS::TestRunner testrunner;
    testrunner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
    testrunner.run(testresult);

    // output results in compiler-format
    CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
    compileroutputter.write();

    // Output XML for Jenkins CPPunit plugin
    ofstream xmlFileOut("TestResults.xml");
    XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}