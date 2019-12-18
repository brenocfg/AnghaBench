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

/* Variables and functions */
 int /*<<< orphan*/  ok_int (int,int) ; 
 int /*<<< orphan*/  ok_str (char*,char*) ; 
 int sprintf (char*,char*,int,...) ; 

void
test_d()
{
    char buffer[5000];
    int result;

    sprintf(buffer, "%d", 1234567);
    ok_str(buffer, "1234567");

    sprintf(buffer, "%d", -1234567);
    ok_str(buffer, "-1234567");

    sprintf(buffer, "%hd", 1234567);
    ok_str(buffer, "-10617");

    sprintf(buffer, "%08d", 1234);
    ok_str(buffer, "00001234");

    sprintf(buffer, "%-08d", 1234);
    ok_str(buffer, "1234    ");

    sprintf(buffer, "%+08d", 1234);
    ok_str(buffer, "+0001234");

    sprintf(buffer, "%+3d", 1234);
    ok_str(buffer, "+1234");

    sprintf(buffer, "%3.3d", 1234);
    ok_str(buffer, "1234");

    sprintf(buffer, "%3.6d", 1234);
    ok_str(buffer, "001234");

    sprintf(buffer, "%8d", -1234);
    ok_str(buffer, "   -1234");

    sprintf(buffer, "%08d", -1234);
    ok_str(buffer, "-0001234");

    sprintf(buffer, "%ld", -1234);
    ok_str(buffer, "-1234");

    sprintf(buffer, "%wd", -1234);
    ok_str(buffer, "-1234");

    sprintf(buffer, "%ld", -5149074030855LL);
    ok_str(buffer, "591757049");

    sprintf(buffer, "%lld", -5149074030855LL);
    ok_str(buffer, "591757049");

    sprintf(buffer, "%I64d", -5149074030855LL);
    ok_str(buffer, "-5149074030855");

    sprintf(buffer, "%Ld", -5149074030855LL);
    ok_str(buffer, "591757049");

    sprintf(buffer, "%lhwI64d", -5149074030855LL);
    ok_str(buffer, "-5149074030855");

    sprintf(buffer, "%I64hlwd", -5149074030855LL);
    ok_str(buffer, "-5149074030855");

    sprintf(buffer, "%hlwd", -5149074030855LL);
    ok_str(buffer, "32505");

    sprintf(buffer, "%Ild", -5149074030855LL);
    ok_str(buffer, "Ild");

    sprintf(buffer, "%hd", -5149074030855LL);
    ok_str(buffer, "32505");

    sprintf(buffer, "%hhd", -5149074030855LL);
    ok_str(buffer, "32505");

    sprintf(buffer, "%hI32hd", -5149074030855LL);
    ok_str(buffer, "32505");

    sprintf(buffer, "%wd", -5149074030855LL);
    ok_str(buffer, "591757049");

    result = sprintf(buffer, " %d.%d", 3, 0);
    ok_int(result, 4);

}