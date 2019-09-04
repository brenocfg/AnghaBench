#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  digits; scalar_t__ ms; int /*<<< orphan*/  time_interval; } ;
typedef  TYPE_1__ StrFromTimeIntervalResult ;

/* Variables and functions */
 int /*<<< orphan*/  StrFromTimeIntervalA (char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* StrFromTimeInterval_results ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_StrFromTimeIntervalA(void)
{
  char szBuff[256];
  const StrFromTimeIntervalResult* result = StrFromTimeInterval_results;

  while(result->ms)
  {
    StrFromTimeIntervalA(szBuff, 256, result->ms, result->digits);

    ok(!strcmp(result->time_interval, szBuff), "Formatted %d %d wrong: %s\n",
       result->ms, result->digits, szBuff);
    result++;
  }
}