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
typedef  double DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  assert (double) ; 

__attribute__((used)) static	inline DWORD	PCM_round(DWORD a, DWORD b, DWORD c)
{
    assert(c);
    /* to be sure, always return an entire number of c... */
    return ((double)a * (double)b + (double)c - 1) / (double)c;
}