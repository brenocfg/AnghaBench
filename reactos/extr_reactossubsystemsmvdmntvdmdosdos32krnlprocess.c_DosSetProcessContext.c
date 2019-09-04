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
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_2__ {int /*<<< orphan*/  DiskTransferArea; int /*<<< orphan*/  CurrentPsp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAKELONG (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* Sda ; 

VOID DosSetProcessContext(WORD Segment)
{
    Sda->CurrentPsp = Segment;
    Sda->DiskTransferArea = MAKELONG(0x80, Segment);
}