#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ fccType; scalar_t__ fccComp; } ;
typedef  TYPE_1__* PACMDRVOPENDESCW ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ACMDRIVERDETAILS_FCCCOMP_UNDEFINED ; 
 scalar_t__ ACMDRIVERDETAILS_FCCTYPE_AUDIOCODEC ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static	DWORD	PCM_drvOpen(LPCSTR str, PACMDRVOPENDESCW adod)
{
    TRACE("(%p, %p)\n", str, adod);

    return (adod == NULL) ||
	(adod->fccType == ACMDRIVERDETAILS_FCCTYPE_AUDIOCODEC &&
	 adod->fccComp == ACMDRIVERDETAILS_FCCCOMP_UNDEFINED);
}