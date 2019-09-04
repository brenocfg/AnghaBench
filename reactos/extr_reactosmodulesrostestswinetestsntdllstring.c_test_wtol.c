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
struct TYPE_6__ {scalar_t__ value; int /*<<< orphan*/  str; } ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 int NB_STR2LONG ; 
 int /*<<< orphan*/  ok (int,char*,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pRtlCreateUnicodeStringFromAsciiz (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pRtlFreeUnicodeString (TYPE_1__*) ; 
 scalar_t__ p_wtol (int /*<<< orphan*/ ) ; 
 TYPE_2__* str2long ; 

__attribute__((used)) static void test_wtol(void)
{
    int test_num;
    UNICODE_STRING uni;
    LONG result;

    for (test_num = 0; test_num < NB_STR2LONG; test_num++) {
	pRtlCreateUnicodeStringFromAsciiz(&uni, str2long[test_num].str);
	result = p_wtol(uni.Buffer);
	ok(result == str2long[test_num].value,
           "(test %d): call failed: _wtol(\"%s\") has result %d, expected: %d\n",
	   test_num, str2long[test_num].str, result, str2long[test_num].value);
	pRtlFreeUnicodeString(&uni);
    } /* for */
}