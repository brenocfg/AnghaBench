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
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int Shell_MergeMenus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void
test_shlmenu(void) {
	HRESULT hres;
	hres = Shell_MergeMenus (0, 0, 0x42, 0x4242, 0x424242, 0);
	ok (hres == 0x4242, "expected 0x4242 but got %x\n", hres);
	hres = Shell_MergeMenus ((HMENU)42, 0, 0x42, 0x4242, 0x424242, 0);
	ok (hres == 0x4242, "expected 0x4242 but got %x\n", hres);
}