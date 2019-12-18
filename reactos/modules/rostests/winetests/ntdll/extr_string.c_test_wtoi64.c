#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_6__ {int overflow; scalar_t__ value; int /*<<< orphan*/  str; } ;
typedef  scalar_t__ LONGLONG ;

/* Variables and functions */
 int NB_STR2LONGLONG ; 
 scalar_t__ ULL (int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pRtlCreateUnicodeStringFromAsciiz (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pRtlFreeUnicodeString (TYPE_1__*) ; 
 scalar_t__ p_wtoi64 (int /*<<< orphan*/ ) ; 
 TYPE_2__* str2longlong ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (scalar_t__) ; 

__attribute__((used)) static void test_wtoi64(void)
{
    int test_num;
    UNICODE_STRING uni;
    LONGLONG result;

    for (test_num = 0; test_num < NB_STR2LONGLONG; test_num++) {
	pRtlCreateUnicodeStringFromAsciiz(&uni, str2longlong[test_num].str);
	result = p_wtoi64(uni.Buffer);
        if (str2longlong[test_num].overflow)
            ok(result == str2longlong[test_num].value ||
               (result == ((str2longlong[test_num].overflow == -1) ?
                ULL(0x80000000,0x00000000) : ULL(0x7fffffff,0xffffffff))),
               "(test %d): call failed: _atoi64(\"%s\") has result 0x%s, expected: 0x%s\n",
               test_num, str2longlong[test_num].str, wine_dbgstr_longlong(result),
               wine_dbgstr_longlong(str2longlong[test_num].value));
        else
            ok(result == str2longlong[test_num].value,
               "(test %d): call failed: _atoi64(\"%s\") has result 0x%s, expected: 0x%s\n",
               test_num, str2longlong[test_num].str, wine_dbgstr_longlong(result),
               wine_dbgstr_longlong(str2longlong[test_num].value));
	pRtlFreeUnicodeString(&uni);
    }
}