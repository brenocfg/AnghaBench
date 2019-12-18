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
typedef  int WORD ;
typedef  int* PBYTE ;

/* Variables and functions */

__attribute__((used)) static inline WORD htods(WORD in)
{
    WORD out;
    PBYTE out_ptr = (PBYTE)&out;
    out_ptr[0] = in; out_ptr[1] = in >> 8;
    return out;
}