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
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int MAX_MEMORY_FOR_ALLOC ; 
 int UINT_MAX ; 
 void* _cmsMallocZero (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
void* _cmsCallocDefaultFn(cmsContext ContextID, cmsUInt32Number num, cmsUInt32Number size)
{
    cmsUInt32Number Total = num * size;

    // Preserve calloc behaviour
    if (Total == 0) return NULL;

    // Safe check for overflow.
    if (num >= UINT_MAX / size) return NULL;

    // Check for overflow
    if (Total < num || Total < size) {
        return NULL;
    }

    if (Total > MAX_MEMORY_FOR_ALLOC) return NULL;  // Never alloc over 512Mb

    return _cmsMallocZero(ContextID, Total);
}