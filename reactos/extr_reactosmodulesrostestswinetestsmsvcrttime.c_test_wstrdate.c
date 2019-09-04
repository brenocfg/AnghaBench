#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char wchar_t ;

/* Variables and functions */
 char* _wstrdate (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int swscanf (char*,char*,int*,int*,int*) ; 
 int wcslen (char*) ; 

__attribute__((used)) static void test_wstrdate(void)
{
    wchar_t date[16], * result;
    int month, day, year, count, len;
    wchar_t format[] = { '%','0','2','d','/','%','0','2','d','/','%','0','2','d',0 };

    result = _wstrdate(date);
    ok(result == date, "Wrong return value\n");
    len = wcslen(date);
    ok(len == 8, "Wrong length: returned %d, should be 8\n", len);
    count = swscanf(date, format, &month, &day, &year);
    ok(count == 3, "Wrong format: count = %d, should be 3\n", count);
}