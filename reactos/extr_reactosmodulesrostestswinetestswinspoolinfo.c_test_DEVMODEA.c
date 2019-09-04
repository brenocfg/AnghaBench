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
struct TYPE_3__ {scalar_t__ dmDriverExtra; scalar_t__ dmDeviceName; scalar_t__ dmSize; int /*<<< orphan*/  dmFields; scalar_t__ dmDriverVersion; scalar_t__ dmSpecVersion; } ;
typedef  scalar_t__ LPCSTR ;
typedef  scalar_t__ LONG ;
typedef  TYPE_1__ DEVMODEA ;

/* Variables and functions */
 scalar_t__ CCHDEVICENAME ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strncmp (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_DEVMODEA(const DEVMODEA *dm, LONG dmSize, LPCSTR exp_prn_name)
{
    /* On NT3.51, some fields in DEVMODEA are empty/zero
      (dmDeviceName, dmSpecVersion, dmDriverVersion and dmDriverExtra)
       We skip the Tests on this Platform */
    if (dm->dmSpecVersion || dm->dmDriverVersion || dm->dmDriverExtra) {
    /* The 0-terminated Printername can be larger (MAX_PATH) than CCHDEVICENAME */
        ok(!strncmp(exp_prn_name, (LPCSTR)dm->dmDeviceName, CCHDEVICENAME -1) ||
           !strncmp(exp_prn_name, (LPCSTR)dm->dmDeviceName, CCHDEVICENAME -2), /* XP+ */
            "expected '%s', got '%s'\n", exp_prn_name, dm->dmDeviceName);
        ok(dm->dmSize + dm->dmDriverExtra == dmSize,
            "%u != %d\n", dm->dmSize + dm->dmDriverExtra, dmSize);
    }
    trace("dmFields %08x\n", dm->dmFields);
}