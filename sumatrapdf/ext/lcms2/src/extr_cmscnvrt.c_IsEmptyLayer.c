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
typedef  int /*<<< orphan*/  cmsVEC3 ;
typedef  int /*<<< orphan*/  cmsMAT3 ;
typedef  double cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int cmsBool ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  _cmsMAT3identity (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ fabs (double) ; 

__attribute__((used)) static
cmsBool IsEmptyLayer(cmsContext ContextID, cmsMAT3* m, cmsVEC3* off)
{
    cmsFloat64Number diff = 0;
    cmsMAT3 Ident;
    int i;

    if (m == NULL && off == NULL) return TRUE;  // NULL is allowed as an empty layer
    if (m == NULL && off != NULL) return FALSE; // This is an internal error

    _cmsMAT3identity(ContextID, &Ident);

    for (i=0; i < 3*3; i++)
        diff += fabs(((cmsFloat64Number*)m)[i] - ((cmsFloat64Number*)&Ident)[i]);

    for (i=0; i < 3; i++)
        diff += fabs(((cmsFloat64Number*)off)[i]);


    return (diff < 0.002);
}