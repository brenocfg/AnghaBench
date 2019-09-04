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
typedef  int* PBYTE ;
typedef  int DWORD ;

/* Variables and functions */

__attribute__((used)) static inline DWORD dtohl(DWORD in)
{
    PBYTE in_ptr = (PBYTE)&in;
    return in_ptr[0] | (in_ptr[1] << 8) | (in_ptr[2] << 16) | (in_ptr[3] << 24);
}