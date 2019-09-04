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
typedef  char WCHAR ;

/* Variables and functions */
 scalar_t__ WEOF ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,char,...) ; 
 int swscanf (char*,char const*,...) ; 

__attribute__((used)) static void test_swscanf( void )
{
    wchar_t buffer[100];
    int result, ret;
    static const WCHAR formatd[] = {'%','d',0};
    const WCHAR format2[] = {'a',0x1234,'%',0x1234,'%','c',0};
    WCHAR c;

    /* check WEOF */
    /* WEOF is an unsigned short -1 but swscanf returns int
       so it should be sign-extended */
    buffer[0] = 0;
    ret = swscanf(buffer, formatd, &result);
    /* msvcrt returns 0 but should return -1 (later versions do) */
    ok( ret == (short)WEOF || broken(ret == 0),
        "swscanf returns %x instead of %x\n", ret, WEOF );

    buffer[0] = 'a';
    buffer[1] = 0x1234;
    buffer[2] = 0x1234;
    buffer[3] = 'b';
    ret = swscanf(buffer, format2, &c);
    ok(ret == 1, "swscanf returned %d\n", ret);
    ok(c == 'b', "c = %x\n", c);
}