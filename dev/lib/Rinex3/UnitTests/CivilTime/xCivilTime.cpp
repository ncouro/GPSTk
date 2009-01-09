#include "xCivilTime.hpp"
#include <iostream>
#include <fstream>

CPPUNIT_TEST_SUITE_REGISTRATION (xCivilTime);

using namespace gpstk;

void xCivilTime :: setUp (void)
{
}

void xCivilTime :: setFromInfoTest (void)
{
	Rinex3::CivilTime setFromInfo1;
	Rinex3::CivilTime setFromInfo2;
	Rinex3::CivilTime setFromInfo3;
	Rinex3::CivilTime setFromInfo4;
	Rinex3::CivilTime setFromInfo5;
	
	gpstk::TimeTag::IdToValue Id;
	Id.insert(make_pair('b',"Dec"));
	Id.insert(make_pair('d',"31"));
	Id.insert(make_pair('Y',"2008"));
	Id.insert(make_pair('H',"12"));
	Id.insert(make_pair('M',"00"));
	Id.insert(make_pair('S',"00"));
	CPPUNIT_ASSERT(setFromInfo1.setFromInfo(Id));
	Id.erase('b');
	Id.erase('Y');
	Id.insert(make_pair('m',"12"));
	Id.insert(make_pair('y',"06"));
	CPPUNIT_ASSERT(setFromInfo2.setFromInfo(Id));
	Id.erase('y');
	Id.insert(make_pair('y',"006"));
	CPPUNIT_ASSERT(setFromInfo3.setFromInfo(Id));
	Id.erase('y');
	CPPUNIT_ASSERT(setFromInfo4.setFromInfo(Id));
	Id.erase('m');
	Id.insert(make_pair('b',"AAA"));
	CPPUNIT_ASSERT(!(setFromInfo5.setFromInfo(Id)));
}

void xCivilTime :: operatorTest (void)
{
	Rinex3::CivilTime Zero;
	
	Rinex3::CivilTime Aug21(2008,8,21,13,30,15.);
	Rinex3::CivilTime LessThanYear(2005,8,21,13,30,15.);
	Rinex3::CivilTime LessThanMonth(2008,7,21,13,30,15.);
	Rinex3::CivilTime LessThanDay(2008,8,20,13,30,15.);
	Rinex3::CivilTime LessThanHour(2008,8,21,12,30,15.);
	Rinex3::CivilTime LessThanMinute(2008,8,21,13,20,15.);
	Rinex3::CivilTime LessThanSecond(2008,8,21,13,30,0.);
	
	Rinex3::CivilTime Aug21Copy(Aug21);
	
	Rinex3::CivilTime Aug21Copy2 = Aug21Copy;
	Aug21Copy2 = Aug21Copy;
	//Equality Assertion
	CPPUNIT_ASSERT_EQUAL(Aug21,Aug21Copy);
	//Non-equality Assertion
	CPPUNIT_ASSERT(Aug21 != LessThanYear);
	//Less than assertions
	CPPUNIT_ASSERT(LessThanYear < Aug21);
	CPPUNIT_ASSERT(!(Aug21 < LessThanYear));
	CPPUNIT_ASSERT(LessThanMonth < Aug21);
	CPPUNIT_ASSERT(!(Aug21 < LessThanMonth));
	CPPUNIT_ASSERT(LessThanDay < Aug21);
	CPPUNIT_ASSERT(!(Aug21 < LessThanDay));
	CPPUNIT_ASSERT(LessThanHour < Aug21);
	CPPUNIT_ASSERT(!(Aug21 < LessThanHour));
	CPPUNIT_ASSERT(LessThanMinute < Aug21);
	CPPUNIT_ASSERT(!(Aug21 < LessThanMinute));
	CPPUNIT_ASSERT(LessThanSecond < Aug21);
	CPPUNIT_ASSERT(!(Aug21 < LessThanSecond));
	//Greater than assertions
	CPPUNIT_ASSERT(Aug21 > LessThanYear);
	//Less than equals assertion
	CPPUNIT_ASSERT(LessThanYear <= Aug21);
	CPPUNIT_ASSERT(Aug21Copy <= Aug21);
	//Greater than equals assertion
	CPPUNIT_ASSERT(Aug21 >= LessThanYear);
	CPPUNIT_ASSERT(Aug21 >= Aug21Copy);
	
	CPPUNIT_ASSERT(Aug21.isValid());
	CPPUNIT_ASSERT(!Zero.isValid());
}

void xCivilTime :: resetTest (void)
{
	Rinex3::CivilTime Aug21(2008,8,21,13,30,15.,gpstk::GPS);

	CommonTime Test = Aug21.convertToCommonTime();

	Rinex3::CivilTime Test2;
	Test2.convertFromCommonTime(Test);

	CPPUNIT_ASSERT_EQUAL(Test2,Aug21);
	CPPUNIT_ASSERT_EQUAL(gpstk::GPS,Aug21.getTimeSystem());

	Aug21.reset();
	CPPUNIT_ASSERT_EQUAL(gpstk::Unknown,Aug21.getTimeSystem());
	CPPUNIT_ASSERT_EQUAL(0,(int)Aug21.year);
	CPPUNIT_ASSERT_EQUAL(1,(int)Aug21.month);
	CPPUNIT_ASSERT_EQUAL(1,(int)Aug21.day);
	CPPUNIT_ASSERT_EQUAL(0,(int)Aug21.hour);
	CPPUNIT_ASSERT_EQUAL(0,(int)Aug21.minute);
	CPPUNIT_ASSERT_EQUAL(0,(int)Aug21.second);
}

void xCivilTime :: timeSystemTest (void)
{

	Rinex3::CivilTime GPS1(   2008,8,21,13,30,15.,gpstk::GPS);
	Rinex3::CivilTime GPS2(   2005,8,21,13,30,15.,gpstk::GPS);
	Rinex3::CivilTime UTC(    2008,8,21,13,30,15.,gpstk::UTC);
	Rinex3::CivilTime UNKNOWN(2008,8,21,13,30,15.,gpstk::Unknown);
	Rinex3::CivilTime ANY(    2008,8,21,13,30,15.,gpstk::Any);

	CPPUNIT_ASSERT(GPS1 != GPS2);
	CPPUNIT_ASSERT_EQUAL(GPS1.getTimeSystem(),GPS2.getTimeSystem());
	CPPUNIT_ASSERT(GPS1 != UTC);
	CPPUNIT_ASSERT(GPS1 != UNKNOWN);
	CPPUNIT_ASSERT(GPS1.convertToCommonTime() > gpstk::CommonTime::BEGINNING_OF_TIME);
	CPPUNIT_ASSERT(gpstk::CommonTime::BEGINNING_OF_TIME < GPS1);
	CPPUNIT_ASSERT_EQUAL(GPS1,ANY);
	CPPUNIT_ASSERT_EQUAL(UTC,ANY);
	CPPUNIT_ASSERT_EQUAL(UNKNOWN,ANY);
	CPPUNIT_ASSERT(GPS2 != ANY);
	CPPUNIT_ASSERT(GPS2 < GPS1);
	CPPUNIT_ASSERT(GPS2 < ANY);

	UNKNOWN.setTimeSystem(gpstk::GPS);
	CPPUNIT_ASSERT_EQUAL(UNKNOWN.getTimeSystem(),gpstk::GPS);

}

void xCivilTime :: printfTest (void)
{
	Rinex3::CivilTime GPS1(2008,8,21,13,30,15.,gpstk::GPS);
	Rinex3::CivilTime UTC(2008,8,21,13,30,15.,gpstk::UTC);

	CPPUNIT_ASSERT_EQUAL(GPS1.printf("%04Y %02y %02m %02b %02d %02H %02M %02S %02f %02P"),(std::string)"2008 08 08 Aug 21 13 30 15 15.000000 02");
	CPPUNIT_ASSERT_EQUAL(UTC.printf("%04Y %02y %02m %02b %02d %02H %02M %02S %02f %02P"),(std::string)"2008 08 08 Aug 21 13 30 15 15.000000 03");
	CPPUNIT_ASSERT_EQUAL(GPS1.printError("%04Y %02y %02m %02b %02d %02H %02M %02S %02f %02P"),(std::string)"ErrorBadTime ErrorBadTime ErrorBadTime ErrorBadTime ErrorBadTime ErrorBadTime ErrorBadTime ErrorBadTime ErrorBadTime ErrorBadTime");
	CPPUNIT_ASSERT_EQUAL(GPS1.printError("%04Y %02y %02m %02b %02d %02H %02M %02S %02f %02P"),(std::string)"ErrorBadTime ErrorBadTime ErrorBadTime ErrorBadTime ErrorBadTime ErrorBadTime ErrorBadTime ErrorBadTime ErrorBadTime ErrorBadTime");
}