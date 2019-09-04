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
struct TYPE_3__ {int /*<<< orphan*/  FunctionName; int /*<<< orphan*/  LibraryName; } ;
typedef  TYPE_1__* PHOOKAPI ;
typedef  int /*<<< orphan*/  PCSTR ;

/* Variables and functions */
 int lstrcmpA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  winetest_ok (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void expect_shim_imp(PHOOKAPI hook, PCSTR library, PCSTR function, PCSTR shim, int* same)
{
    int lib = lstrcmpA(library, hook->LibraryName);
    int fn = lstrcmpA(function, hook->FunctionName);
    winetest_ok(lib == 0, "Expected LibrarayName to be %s, was: %s for %s\n", library, hook->LibraryName, shim);
    winetest_ok(fn == 0, "Expected FunctionName to be %s, was: %s for %s\n", function, hook->FunctionName, shim);
    *same = (lib == 0 && fn == 0);
}