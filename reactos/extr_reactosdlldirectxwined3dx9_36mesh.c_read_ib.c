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
typedef  size_t WORD ;
typedef  size_t DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */

__attribute__((used)) static inline DWORD read_ib(void *index_buffer, BOOL indices_are_32bit,
                            DWORD index)
{
    if (indices_are_32bit)
    {
        DWORD *indices = index_buffer;
        return indices[index];
    }
    else
    {
        WORD *indices = index_buffer;
        return indices[index];
    }
}