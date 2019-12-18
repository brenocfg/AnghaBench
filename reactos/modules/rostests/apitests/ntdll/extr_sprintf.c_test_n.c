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
typedef  int __int64 ;

/* Variables and functions */
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_int (int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int*) ; 

void
test_n()
{
    int len = 123;
    __int64 len64;
    char buffer[64];

    sprintf(buffer, "%07s%n", "test", &len);
    ok_int(len, 7);

    len = 0x12345678;
    sprintf(buffer, "%s%hn", "test", &len);
    ok_int(len, 0x12340004);

    len = 0x12345678;
    sprintf(buffer, "%s%hhn", "test", &len);
    ok_int(len, 0x12340004);

    len64 = 0x0123456781234567ULL;
    sprintf(buffer, "%s%lln", "test", &len64);
    ok(len64 == 0x123456700000004ULL, " ");

}