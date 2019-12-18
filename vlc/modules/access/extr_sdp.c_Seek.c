#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {char* p_sys; scalar_t__ psz_location; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 scalar_t__ SIZE_MAX ; 
 int VLC_SUCCESS ; 
 int strnlen (scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int Seek (stream_t *access, uint64_t position)
{
#if (UINT64_MAX > SIZE_MAX)
    if (unlikely(position > SIZE_MAX))
        position = SIZE_MAX;
#endif
    access->p_sys = (char *)access->psz_location
                    + strnlen(access->psz_location, position);
    return VLC_SUCCESS;
}