#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* v; } ;
typedef  TYPE_2__ cmsMAT3 ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_5__ {int /*<<< orphan*/ * n; } ;

/* Variables and functions */
 int /*<<< orphan*/  CloseEnoughFloat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsMAT3identity (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static
cmsBool  isFloatMatrixIdentity(cmsContext ContextID, const cmsMAT3* a)
{
       cmsMAT3 Identity;
       int i, j;

       _cmsMAT3identity(ContextID, &Identity);

       for (i = 0; i < 3; i++)
              for (j = 0; j < 3; j++)
                     if (!CloseEnoughFloat(a->v[i].n[j], Identity.v[i].n[j])) return FALSE;

       return TRUE;
}