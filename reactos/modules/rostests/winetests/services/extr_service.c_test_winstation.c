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
typedef  int /*<<< orphan*/  flags ;
struct TYPE_3__ {int dwFlags; } ;
typedef  TYPE_1__ USEROBJECTFLAGS ;
typedef  int /*<<< orphan*/ * HWINSTA ;
typedef  int BOOL ;

/* Variables and functions */
 int GetLastError () ; 
 int /*<<< orphan*/ * GetProcessWindowStation () ; 
 int GetUserObjectInformationA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UOI_FLAGS ; 
 int WSF_VISIBLE ; 
 int /*<<< orphan*/  service_ok (int,char*,...) ; 

__attribute__((used)) static void test_winstation(void)
{
    HWINSTA winstation;
    USEROBJECTFLAGS flags;
    BOOL r;

    winstation = GetProcessWindowStation();
    service_ok(winstation != NULL, "winstation = NULL\n");

    r = GetUserObjectInformationA(winstation, UOI_FLAGS, &flags, sizeof(flags), NULL);
    service_ok(r, "GetUserObjectInformation(UOI_NAME) failed: %u\n", GetLastError());
    service_ok(!(flags.dwFlags & WSF_VISIBLE), "winstation has flags %x\n", flags.dwFlags);
}