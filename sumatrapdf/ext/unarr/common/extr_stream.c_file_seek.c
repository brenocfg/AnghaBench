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
typedef  int /*<<< orphan*/  off_t ;
typedef  scalar_t__ off64_t ;

/* Variables and functions */
 scalar_t__ INT32_MAX ; 
 scalar_t__ INT32_MIN ; 
 scalar_t__ _fseeki64 (void*,scalar_t__,int) ; 
 scalar_t__ fseek (void*,long,int) ; 
 scalar_t__ fseeko (void*,scalar_t__,int) ; 

__attribute__((used)) static bool file_seek(void *data, off64_t offset, int origin)
{
#ifdef _MSC_VER
    return _fseeki64(data, offset, origin) == 0;
#else
#if _POSIX_C_SOURCE >= 200112L
    if (sizeof(off_t) == 8)
        return fseeko(data, offset, origin) == 0;
#endif
    if (offset > INT32_MAX || offset < INT32_MIN)
        return false;
    return fseek(data, (long)offset, origin) == 0;
#endif
}