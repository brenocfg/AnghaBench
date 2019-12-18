#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ a; scalar_t__ b; scalar_t__ result; int /*<<< orphan*/  shift; } ;
typedef  scalar_t__ LONGLONG ;

/* Variables and functions */
 int NB_MAGIC_DIVIDE ; 
 TYPE_1__* magic_divide ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pRtlExtendedMagicDivide (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (scalar_t__) ; 

__attribute__((used)) static void test_RtlExtendedMagicDivide(void)
{
    int i;
    LONGLONG result;

    for (i = 0; i < NB_MAGIC_DIVIDE; i++) {
	result = pRtlExtendedMagicDivide(magic_divide[i].a, magic_divide[i].b, magic_divide[i].shift);
	ok(result == magic_divide[i].result,
           "call failed: RtlExtendedMagicDivide(0x%s, 0x%s, %d) has result 0x%s, expected 0x%s\n",
	   wine_dbgstr_longlong(magic_divide[i].a), wine_dbgstr_longlong(magic_divide[i].b), magic_divide[i].shift,
       wine_dbgstr_longlong(result), wine_dbgstr_longlong(magic_divide[i].result));
    }
}