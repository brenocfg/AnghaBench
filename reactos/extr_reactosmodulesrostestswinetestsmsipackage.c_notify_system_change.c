#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  szDescription; int /*<<< orphan*/  llSequenceNumber; int /*<<< orphan*/  dwRestorePtType; int /*<<< orphan*/  dwEventType; } ;
struct TYPE_6__ {int /*<<< orphan*/  llSequenceNumber; } ;
typedef  TYPE_1__ STATEMGRSTATUS ;
typedef  TYPE_2__ RESTOREPOINTINFOA ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  APPLICATION_INSTALL ; 
 int /*<<< orphan*/  lstrcpyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pSRSetRestorePointA (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static BOOL notify_system_change(DWORD event_type, STATEMGRSTATUS *status)
{
    RESTOREPOINTINFOA spec;

    spec.dwEventType = event_type;
    spec.dwRestorePtType = APPLICATION_INSTALL;
    spec.llSequenceNumber = status->llSequenceNumber;
    lstrcpyA(spec.szDescription, "msitest restore point");

    return pSRSetRestorePointA(&spec, status);
}