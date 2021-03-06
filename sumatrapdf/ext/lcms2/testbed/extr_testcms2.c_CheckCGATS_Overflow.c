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
typedef  int /*<<< orphan*/  junk ;
typedef  char* cmsUInt8Number ;
typedef  int cmsInt32Number ;
typedef  scalar_t__ cmsHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  cmsIT8Free (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ cmsIT8LoadFromMem (int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static
cmsInt32Number CheckCGATS_Overflow(void)
{
    cmsHANDLE handle;
    const cmsUInt8Number junk[] = { "@\nA 1.e2147483648\n" };

    handle = cmsIT8LoadFromMem(0, (const void*)junk, sizeof(junk));
    if (handle)
        cmsIT8Free(DbgThread(), handle);

    return 1;
}