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
struct _cmstransform_struct {int dummy; } ;
typedef  int cmsUInt8Number ;
typedef  size_t cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */

__attribute__((used)) static
void TrancendentalTransform(cmsContext ContextID, struct _cmstransform_struct * CMM,
                              const void* InputBuffer,
                              void* OutputBuffer,
                              cmsUInt32Number Size,
                              cmsUInt32Number Stride)
{
    cmsUInt32Number i;

    for (i=0; i < Size; i++)
    {
        ((cmsUInt8Number*) OutputBuffer)[i] = 0x42;
    }

}