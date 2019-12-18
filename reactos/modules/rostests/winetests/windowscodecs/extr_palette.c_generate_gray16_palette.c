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
typedef  int UINT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void generate_gray16_palette(DWORD *entries, UINT count)
{
    UINT i;

    assert(count == 16);

    for (i = 0; i < 16; i++)
    {
        entries[i] = 0xff000000;
        entries[i] |= (i << 20) | (i << 16) | (i << 12) | (i << 8) | (i << 4) | i;
    }
}