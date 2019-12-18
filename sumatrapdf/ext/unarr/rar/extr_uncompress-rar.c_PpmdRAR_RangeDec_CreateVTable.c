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
struct TYPE_2__ {int /*<<< orphan*/  DecodeBit; int /*<<< orphan*/  Decode; int /*<<< orphan*/  GetThreshold; } ;
struct CPpmdRAR_RangeDec {int /*<<< orphan*/ * Stream; TYPE_1__ super; } ;
typedef  int /*<<< orphan*/  IByteIn ;

/* Variables and functions */
 int /*<<< orphan*/  Range_DecodeBit_RAR ; 
 int /*<<< orphan*/  Range_Decode_RAR ; 
 int /*<<< orphan*/  Range_GetThreshold ; 

__attribute__((used)) static void PpmdRAR_RangeDec_CreateVTable(struct CPpmdRAR_RangeDec *p, IByteIn *stream)
{
    p->super.GetThreshold = Range_GetThreshold;
    p->super.Decode = Range_Decode_RAR;
    p->super.DecodeBit = Range_DecodeBit_RAR;
    p->Stream = stream;
}