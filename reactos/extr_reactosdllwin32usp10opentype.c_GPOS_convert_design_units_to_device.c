#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  lfWidth; } ;
struct TYPE_6__ {int tmAscent; int tmDescent; int tmInternalLeading; } ;
struct TYPE_7__ {scalar_t__ otmEMSquare; TYPE_1__ otmTextMetrics; } ;
typedef  TYPE_2__ OUTLINETEXTMETRICW ;
typedef  TYPE_3__ LOGFONTW ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  TRACE (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void GPOS_convert_design_units_to_device(const OUTLINETEXTMETRICW *otm, const LOGFONTW *logfont,
        int desX, int desY, double *devX, double *devY)
{
    int emHeight = otm->otmTextMetrics.tmAscent + otm->otmTextMetrics.tmDescent - otm->otmTextMetrics.tmInternalLeading;

    TRACE("emHeight %i lfWidth %i\n",emHeight, logfont->lfWidth);
    *devX = (desX * emHeight) / (double)otm->otmEMSquare;
    *devY = (desY * emHeight) / (double)otm->otmEMSquare;
    if (logfont->lfWidth)
        FIXME("Font with lfWidth set not handled properly.\n");
}