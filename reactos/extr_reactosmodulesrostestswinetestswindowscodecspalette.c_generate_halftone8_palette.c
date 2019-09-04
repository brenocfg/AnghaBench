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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void generate_halftone8_palette(DWORD *entries, UINT count, BOOL add_transparent)
{
    UINT i;

    if (add_transparent)
        ok(count == 17, "expected 17, got %u\n", count);
    else
        ok(count == 16, "expected 16, got %u\n", count);

    for (i = 0; i < 8; i++)
    {
        entries[i] = 0xff000000;
        if (i & 1) entries[i] |= 0xff;
        if (i & 2) entries[i] |= 0xff00;
        if (i & 4) entries[i] |= 0xff0000;
    }

    for (i = 8; i < 16; i++)
    {
        static const DWORD halftone[8] = { 0xc0c0c0, 0x808080, 0x800000, 0x008000,
                                           0x000080, 0x808000, 0x800080, 0x008080 };
        entries[i] = 0xff000000;
        entries[i] |= halftone[i-8];
    }

    if (add_transparent)
        entries[i] = 0;
}