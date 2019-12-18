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
struct TYPE_4__ {scalar_t__ sy; } ;
typedef  TYPE_1__ cmsIT8 ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
typedef  scalar_t__ SYMBOL ;

/* Variables and functions */
 int /*<<< orphan*/  NoMeta (char const*) ; 
 int /*<<< orphan*/  SynError (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
cmsBool Check(cmsContext ContextID, cmsIT8* it8, SYMBOL sy, const char* Err)
{
        if (it8 -> sy != sy)
                return SynError(ContextID, it8, NoMeta(Err));
        return TRUE;
}