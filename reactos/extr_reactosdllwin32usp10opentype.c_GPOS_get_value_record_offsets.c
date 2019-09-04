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
typedef  int WORD ;
struct TYPE_7__ {int XPlaDevice; int YPlaDevice; int XAdvDevice; int YAdvDevice; scalar_t__ YAdvance; scalar_t__ XAdvance; scalar_t__ YPlacement; scalar_t__ XPlacement; } ;
struct TYPE_6__ {short x; short y; } ;
typedef  TYPE_1__ POINT ;
typedef  int /*<<< orphan*/  OT_DeviceTable ;
typedef  TYPE_2__ GPOS_ValueRecord ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 scalar_t__ GPOS_get_device_table_value (int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void GPOS_get_value_record_offsets(const BYTE *head, GPOS_ValueRecord *ValueRecord,
        WORD ValueFormat, unsigned int ppem, POINT *ptPlacement, POINT *ptAdvance)
{
    if (ValueFormat & 0x0001) ptPlacement->x += (short)ValueRecord->XPlacement;
    if (ValueFormat & 0x0002) ptPlacement->y += (short)ValueRecord->YPlacement;
    if (ValueFormat & 0x0004) ptAdvance->x += (short)ValueRecord->XAdvance;
    if (ValueFormat & 0x0008) ptAdvance->y += (short)ValueRecord->YAdvance;
    if (ValueFormat & 0x0010) ptPlacement->x += GPOS_get_device_table_value((const OT_DeviceTable*)(head + ValueRecord->XPlaDevice), ppem);
    if (ValueFormat & 0x0020) ptPlacement->y += GPOS_get_device_table_value((const OT_DeviceTable*)(head + ValueRecord->YPlaDevice), ppem);
    if (ValueFormat & 0x0040) ptAdvance->x += GPOS_get_device_table_value((const OT_DeviceTable*)(head + ValueRecord->XAdvDevice), ppem);
    if (ValueFormat & 0x0080) ptAdvance->y += GPOS_get_device_table_value((const OT_DeviceTable*)(head + ValueRecord->YAdvDevice), ppem);
    if (ValueFormat & 0xFF00) FIXME("Unhandled Value Format %x\n",ValueFormat&0xFF00);
}