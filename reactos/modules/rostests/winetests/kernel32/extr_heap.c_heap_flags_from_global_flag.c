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
typedef  int DWORD ;

/* Variables and functions */
 int FLG_HEAP_DISABLE_COALESCING ; 
 int FLG_HEAP_ENABLE_FREE_CHECK ; 
 int FLG_HEAP_ENABLE_TAIL_CHECK ; 
 int FLG_HEAP_PAGE_ALLOCS ; 
 int FLG_HEAP_VALIDATE_ALL ; 
 int FLG_HEAP_VALIDATE_PARAMETERS ; 
 int HEAP_DISABLE_COALESCE_ON_FREE ; 
 int HEAP_FREE_CHECKING_ENABLED ; 
 int HEAP_GROWABLE ; 
 int HEAP_PAGE_ALLOCS ; 
 int HEAP_TAIL_CHECKING_ENABLED ; 
 int HEAP_VALIDATE ; 
 int HEAP_VALIDATE_ALL ; 
 int HEAP_VALIDATE_PARAMS ; 

__attribute__((used)) static DWORD heap_flags_from_global_flag( DWORD flag )
{
    DWORD ret = 0;

    if (flag & FLG_HEAP_ENABLE_TAIL_CHECK)
        ret |= HEAP_TAIL_CHECKING_ENABLED;
    if (flag & FLG_HEAP_ENABLE_FREE_CHECK)
        ret |= HEAP_FREE_CHECKING_ENABLED;
    if (flag & FLG_HEAP_VALIDATE_PARAMETERS)
        ret |= HEAP_VALIDATE_PARAMS | HEAP_VALIDATE | HEAP_TAIL_CHECKING_ENABLED | HEAP_FREE_CHECKING_ENABLED;
    if (flag & FLG_HEAP_VALIDATE_ALL)
        ret |= HEAP_VALIDATE_ALL | HEAP_VALIDATE | HEAP_TAIL_CHECKING_ENABLED | HEAP_FREE_CHECKING_ENABLED;
    if (flag & FLG_HEAP_DISABLE_COALESCING)
        ret |= HEAP_DISABLE_COALESCE_ON_FREE;
    if (flag & FLG_HEAP_PAGE_ALLOCS)
        ret |= HEAP_PAGE_ALLOCS | HEAP_GROWABLE;
    return ret;
}