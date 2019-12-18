#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG ;
typedef  int UCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  ApicId; } ;
struct TYPE_4__ {int SrcBusIrq; int DstApicInt; int /*<<< orphan*/  IrqType; int /*<<< orphan*/  DstApicId; scalar_t__ SrcBusId; scalar_t__ IrqFlag; int /*<<< orphan*/  Type; } ;
typedef  TYPE_1__ MP_CONFIGURATION_INTSRC ;

/* Variables and functions */
 int /*<<< orphan*/  HaliMPIntSrcInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  INT_EXTINT ; 
 int /*<<< orphan*/  INT_VECTORED ; 
 TYPE_2__* IOAPICMap ; 
 int /*<<< orphan*/  MPCTE_INTSRC ; 

__attribute__((used)) static VOID 
HaliConstructDefaultIOIrqMPTable(ULONG Type)
{
	MP_CONFIGURATION_INTSRC intsrc;
	UCHAR i;

	intsrc.Type = MPCTE_INTSRC;
	intsrc.IrqFlag = 0;			/* conforming */
	intsrc.SrcBusId = 0;
	intsrc.DstApicId = IOAPICMap[0].ApicId;

	intsrc.IrqType = INT_VECTORED;
	for (i = 0; i < 16; i++) {
		switch (Type) {
		case 2:
			if (i == 0 || i == 13)
				continue;	/* IRQ0 & IRQ13 not connected */
			/* Fall through */
		default:
			if (i == 2)
				continue;	/* IRQ2 is never connected */
		}

		intsrc.SrcBusIrq = i;
		intsrc.DstApicInt = i ? i : 2; /* IRQ0 to INTIN2 */
		HaliMPIntSrcInfo(&intsrc);
	}

	intsrc.IrqType = INT_EXTINT;
	intsrc.SrcBusIrq = 0;
	intsrc.DstApicInt = 0; /* 8259A to INTIN0 */
	HaliMPIntSrcInfo(&intsrc);
}