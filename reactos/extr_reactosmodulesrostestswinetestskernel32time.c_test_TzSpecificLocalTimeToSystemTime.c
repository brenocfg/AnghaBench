#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tzW ;
typedef  int /*<<< orphan*/  tzS ;
typedef  int /*<<< orphan*/  tzE ;
struct TYPE_18__ {int wYear; int wDay; } ;
struct TYPE_14__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; } ;
struct TYPE_15__ {int member_0; int member_3; scalar_t__ ehour; scalar_t__ nr; TYPE_7__ slt; int /*<<< orphan*/  ptz; TYPE_3__ member_2; TYPE_5__* member_1; } ;
typedef  TYPE_4__ TZLT2ST_case ;
struct TYPE_17__ {scalar_t__ wHour; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wDay; int /*<<< orphan*/  wMonth; int /*<<< orphan*/  wYear; } ;
struct TYPE_13__ {int wMonth; int wDay; int wHour; } ;
struct TYPE_12__ {int wMonth; int wDay; int wHour; scalar_t__ wDayOfWeek; } ;
struct TYPE_16__ {int Bias; int DaylightBias; TYPE_2__ DaylightDate; TYPE_1__ StandardDate; scalar_t__ StandardBias; } ;
typedef  TYPE_5__ TIME_ZONE_INFORMATION ;
typedef  TYPE_6__ SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  ZeroMemory (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pSystemTimeToTzSpecificLocalTime (int /*<<< orphan*/ ,TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  pTzSpecificLocalTimeToSystemTime (int /*<<< orphan*/ ,TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_TzSpecificLocalTimeToSystemTime(void)
{    
    TIME_ZONE_INFORMATION tzE, tzW, tzS;
    SYSTEMTIME result;
    int i, j, year;

    if (!pTzSpecificLocalTimeToSystemTime || !pSystemTimeToTzSpecificLocalTime)
    {
        win_skip("TzSpecificLocalTimeToSystemTime or SystemTimeToTzSpecificLocalTime not available\n");
        return;
    }

    ZeroMemory( &tzE, sizeof(tzE));
    ZeroMemory( &tzW, sizeof(tzW));
    ZeroMemory( &tzS, sizeof(tzS));
    /* timezone Eastern hemisphere */
    tzE.Bias=-600;
    tzE.StandardBias=0;
    tzE.DaylightBias=-60;
    tzE.StandardDate.wMonth=10;
    tzE.StandardDate.wDayOfWeek=0; /* Sunday */
    tzE.StandardDate.wDay=5;       /* last (Sunday) of the month */
    tzE.StandardDate.wHour=3;
    tzE.DaylightDate.wMonth=3;
    tzE.DaylightDate.wDay=5;
    tzE.DaylightDate.wHour=2;
    /* timezone Western hemisphere */
    tzW.Bias=240;
    tzW.StandardBias=0;
    tzW.DaylightBias=-60;
    tzW.StandardDate.wMonth=10;
    tzW.StandardDate.wDayOfWeek=0; /* Sunday */
    tzW.StandardDate.wDay=4;       /* 4th (Sunday) of the month */
    tzW.StandardDate.wHour=2;
    tzW.DaylightDate.wMonth=4;
    tzW.DaylightDate.wDay=1;
    tzW.DaylightDate.wHour=2;
    /* timezone Southern hemisphere */
    tzS.Bias=240;
    tzS.StandardBias=0;
    tzS.DaylightBias=-60;
    tzS.StandardDate.wMonth=4;
    tzS.StandardDate.wDayOfWeek=0; /*Sunday */
    tzS.StandardDate.wDay=1;       /* 1st (Sunday) of the month */
    tzS.StandardDate.wHour=2;
    tzS.DaylightDate.wMonth=10;
    tzS.DaylightDate.wDay=4;
    tzS.DaylightDate.wHour=2;
    /*tests*/
        /* TzSpecificLocalTimeToSystemTime */
    {   TZLT2ST_case cases[] = {
            /* standard->daylight transition */
            { 1, &tzE, {2004,3,-1,28,1,0,0,0}, 15 },
            { 2, &tzE, {2004,3,-1,28,1,59,59,999}, 15},
            { 3, &tzE, {2004,3,-1,28,2,0,0,0}, 15},
            /* daylight->standard transition */
            { 4, &tzE, {2004,10,-1,31,2,0,0,0} , 15 },
            { 5, &tzE, {2004,10,-1,31,2,59,59,999}, 15 },
            { 6, &tzE, {2004,10,-1,31,3,0,0,0}, 17 },
            /* West and with fixed weekday of the month */
            { 7, &tzW, {2004,4,-1,4,1,0,0,0}, 5},
            { 8, &tzW, {2004,4,-1,4,1,59,59,999}, 5},
            { 9, &tzW, {2004,4,-1,4,2,0,0,0}, 5},
            { 10, &tzW, {2004,10,-1,24,1,0,0,0}, 4},
            { 11, &tzW, {2004,10,-1,24,1,59,59,999}, 4},
            { 12, &tzW, {2004,10,-1,24,2,0,0,0 }, 6},
            /* and now South */
            { 13, &tzS, {2004,4,-1,4,1,0,0,0}, 4},
            { 14, &tzS, {2004,4,-1,4,1,59,59,999}, 4},
            { 15, &tzS, {2004,4,-1,4,2,0,0,0}, 6},
            { 16, &tzS, {2004,10,-1,24,1,0,0,0}, 5},
            { 17, &tzS, {2004,10,-1,24,1,59,59,999}, 5},
            { 18, &tzS, {2004,10,-1,24,2,0,0,0}, 5},
            {0}
        };
    /*  days of transitions to put into the cases array */
        int yeardays[][6]=
        {
              {28,31,4,24,4,24}  /* 1999 */
            , {26,29,2,22,2,22}  /* 2000 */
            , {25,28,1,28,1,28}  /* 2001 */
            , {31,27,7,27,7,27}  /* 2002 */
            , {30,26,6,26,6,26}  /* 2003 */
            , {28,31,4,24,4,24}  /* 2004 */
            , {27,30,3,23,3,23}  /* 2005 */
            , {26,29,2,22,2,22}  /* 2006 */
            , {25,28,1,28,1,28}  /* 2007 */
            , {30,26,6,26,6,26}  /* 2008 */
            , {29,25,5,25,5,25}  /* 2009 */
            , {28,31,4,24,4,24}  /* 2010 */
            , {27,30,3,23,3,23}  /* 2011 */
            , {25,28,1,28,1,28}  /* 2012 */
            , {31,27,7,27,7,27}  /* 2013 */
            , {30,26,6,26,6,26}  /* 2014 */
            , {29,25,5,25,5,25}  /* 2015 */
            , {27,30,3,23,3,23}  /* 2016 */
            , {26,29,2,22,2,22}  /* 2017 */
            , {25,28,1,28,1,28}  /* 2018 */
            , {31,27,7,27,7,27}  /* 2019 */
            ,{0}
        };
        for( j=0 , year = 1999; yeardays[j][0] ; j++, year++) {
            for (i=0; cases[i].nr; i++) {
                if(i) cases[i].nr += 18;
                cases[i].slt.wYear = year;
                cases[i].slt.wDay = yeardays[j][i/3];
                pTzSpecificLocalTimeToSystemTime( cases[i].ptz, &(cases[i].slt), &result);
                ok( result.wHour == cases[i].ehour,
                        "Test TzSpecificLocalTimeToSystemTime #%d. Got %4d-%02d-%02d %02d:%02d. Expect hour =  %02d\n", 
                        cases[i].nr, result.wYear, result.wMonth, result.wDay,
                        result.wHour, result.wMinute, cases[i].ehour);
            }
        }
    }
        /* SystemTimeToTzSpecificLocalTime */
    {   TZLT2ST_case cases[] = {
            /* standard->daylight transition */
            { 1, &tzE, {2004,3,-1,27,15,0,0,0}, 1 },
            { 2, &tzE, {2004,3,-1,27,15,59,59,999}, 1},
            { 3, &tzE, {2004,3,-1,27,16,0,0,0}, 3},
            /* daylight->standard transition */
            { 4,  &tzE, {2004,10,-1,30,15,0,0,0}, 2 },
            { 5, &tzE, {2004,10,-1,30,15,59,59,999}, 2 },
            { 6, &tzE, {2004,10,-1,30,16,0,0,0}, 2 },
            /* West and with fixed weekday of the month */
            { 7, &tzW, {2004,4,-1,4,5,0,0,0}, 1},
            { 8, &tzW, {2004,4,-1,4,5,59,59,999}, 1},
            { 9, &tzW, {2004,4,-1,4,6,0,0,0}, 3},
            { 10, &tzW, {2004,10,-1,24,4,0,0,0}, 1},
            { 11, &tzW, {2004,10,-1,24,4,59,59,999}, 1},
            { 12, &tzW, {2004,10,-1,24,5,0,0,0 }, 1},
            /* and now South */
            { 13, &tzS, {2004,4,-1,4,4,0,0,0}, 1},
            { 14, &tzS, {2004,4,-1,4,4,59,59,999}, 1},
            { 15, &tzS, {2004,4,-1,4,5,0,0,0}, 1},
            { 16, &tzS, {2004,10,-1,24,5,0,0,0}, 1},
            { 17, &tzS, {2004,10,-1,24,5,59,59,999}, 1},
            { 18, &tzS, {2004,10,-1,24,6,0,0,0}, 3},

            {0}
        }; 
    /*  days of transitions to put into the cases array */
        int yeardays[][6]=
        {
              {27,30,4,24,4,24}  /* 1999 */
            , {25,28,2,22,2,22}  /* 2000 */
            , {24,27,1,28,1,28}  /* 2001 */
            , {30,26,7,27,7,27}  /* 2002 */
            , {29,25,6,26,6,26}  /* 2003 */
            , {27,30,4,24,4,24}  /* 2004 */
            , {26,29,3,23,3,23}  /* 2005 */
            , {25,28,2,22,2,22}  /* 2006 */
            , {24,27,1,28,1,28}  /* 2007 */
            , {29,25,6,26,6,26}  /* 2008 */
            , {28,24,5,25,5,25}  /* 2009 */
            , {27,30,4,24,4,24}  /* 2010 */
            , {26,29,3,23,3,23}  /* 2011 */
            , {24,27,1,28,1,28}  /* 2012 */
            , {30,26,7,27,7,27}  /* 2013 */
            , {29,25,6,26,6,26}  /* 2014 */
            , {28,24,5,25,5,25}  /* 2015 */
            , {26,29,3,23,3,23}  /* 2016 */
            , {25,28,2,22,2,22}  /* 2017 */
            , {24,27,1,28,1,28}  /* 2018 */
            , {30,26,7,27,7,27}  /* 2019 */
            , {0}
        };
        for( j=0 , year = 1999; yeardays[j][0] ; j++, year++) {
            for (i=0; cases[i].nr; i++) {
                if(i) cases[i].nr += 18;
                cases[i].slt.wYear = year;
                cases[i].slt.wDay = yeardays[j][i/3];
                pSystemTimeToTzSpecificLocalTime( cases[i].ptz, &(cases[i].slt), &result);
                ok( result.wHour == cases[i].ehour,
                        "Test SystemTimeToTzSpecificLocalTime #%d. Got %4d-%02d-%02d %02d:%02d. Expect hour = %02d\n", 
                        cases[i].nr, result.wYear, result.wMonth, result.wDay,
                        result.wHour, result.wMinute, cases[i].ehour);
            }
        }

    }        
}