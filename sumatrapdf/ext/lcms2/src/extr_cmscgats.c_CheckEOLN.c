#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ sy; } ;
typedef  TYPE_1__ cmsIT8 ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  Check (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InSymbol (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ SEOLN ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
cmsBool CheckEOLN(cmsContext ContextID, cmsIT8* it8)
{
        if (!Check(ContextID, it8, SEOLN, "Expected separator")) return FALSE;
        while (it8 -> sy == SEOLN)
                        InSymbol(ContextID, it8);
        return TRUE;

}