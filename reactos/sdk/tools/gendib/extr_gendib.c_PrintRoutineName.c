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
struct TYPE_3__ {scalar_t__ RopCode; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__* PROPINFO ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Output (int /*<<< orphan*/ *,char*,unsigned int,...) ; 
 scalar_t__ ROPCODE_GENERIC ; 

__attribute__((used)) static void
PrintRoutineName(FILE *Out, unsigned Bpp, PROPINFO RopInfo)
{
    if (NULL != RopInfo && ROPCODE_GENERIC != RopInfo->RopCode)
    {
        Output(Out, "DIB_%uBPP_BitBlt_%s", Bpp, RopInfo->Name);
    }
    else
    {
        Output(Out, "DIB_%uBPP_BitBlt_Generic", Bpp);
    }
}