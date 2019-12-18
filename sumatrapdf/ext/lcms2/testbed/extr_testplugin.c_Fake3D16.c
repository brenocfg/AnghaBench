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
struct _cms_interp_struc {int dummy; } ;
typedef  scalar_t__ cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */

__attribute__((used)) static
void Fake3D16(cmsContext ContextID, register const cmsUInt16Number Input[],
              register cmsUInt16Number Output[],
              register const struct _cms_interp_struc* p)
{
       Output[0] =  0xFFFF - Input[2];
       Output[1] =  0xFFFF - Input[1];
       Output[2] =  0xFFFF - Input[0];
}