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
typedef  int /*<<< orphan*/  numprocs ;
typedef  int ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  DosQuerySysInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  QSV_NUMPROCESSORS ; 

unsigned vlc_GetCPUCount (void)
{
    ULONG numprocs = 1;

    DosQuerySysInfo(QSV_NUMPROCESSORS, QSV_NUMPROCESSORS,
                    &numprocs, sizeof(numprocs));

    return numprocs;
}