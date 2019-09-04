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
struct TYPE_3__ {int nReshowTime; int nAutoPopTime; int nInitialTime; } ;
typedef  TYPE_1__ TOOLTIPS_INFO ;
typedef  int LRESULT ;
typedef  int DWORD ;

/* Variables and functions */
#define  TTDT_AUTOMATIC 131 
#define  TTDT_AUTOPOP 130 
#define  TTDT_INITIAL 129 
#define  TTDT_RESHOW 128 
 int /*<<< orphan*/  WARN (char*,int) ; 

__attribute__((used)) static LRESULT
TOOLTIPS_GetDelayTime (const TOOLTIPS_INFO *infoPtr, DWORD duration)
{
    switch (duration) {
    case TTDT_RESHOW:
        return infoPtr->nReshowTime;

    case TTDT_AUTOPOP:
        return infoPtr->nAutoPopTime;

    case TTDT_INITIAL:
    case TTDT_AUTOMATIC: /* Apparently TTDT_AUTOMATIC returns TTDT_INITIAL */
        return infoPtr->nInitialTime;

    default:
        WARN("Invalid duration flag %x\n", duration);
	break;
    }

    return -1;
}