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
struct TYPE_3__ {char* dwObj; scalar_t__ dwHow; } ;
typedef  TYPE_1__* LPCDIPROPHEADER ;

/* Variables and functions */
 scalar_t__ DIPH_BYID ; 
 scalar_t__ DIPH_BYOFFSET ; 
 scalar_t__ DIPH_DEVICE ; 
 int /*<<< orphan*/  TRACE (char*,char*) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dinput ; 

void _dump_DIPROPHEADER(LPCDIPROPHEADER diph) {
    if (TRACE_ON(dinput)) {
        TRACE("  - dwObj = 0x%08x\n", diph->dwObj);
        TRACE("  - dwHow = %s\n",
            ((diph->dwHow == DIPH_DEVICE) ? "DIPH_DEVICE" :
            ((diph->dwHow == DIPH_BYOFFSET) ? "DIPH_BYOFFSET" :
            ((diph->dwHow == DIPH_BYID)) ? "DIPH_BYID" : "unknown")));
    }
}