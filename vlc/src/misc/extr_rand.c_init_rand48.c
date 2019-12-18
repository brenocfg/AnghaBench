#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int init; int /*<<< orphan*/  subi; } ;

/* Variables and functions */
 TYPE_1__ rand48 ; 
 int* subi ; 
 int /*<<< orphan*/  vlc_rand_bytes (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_rand48 (void)
{
    if (!rand48.init)
    {
        vlc_rand_bytes (rand48.subi, sizeof (rand48.subi));
        rand48.init = true;
#if 0 // short would be more than 16-bits ?
        for (unsigned i = 0; i < 3; i++)
            subi[i] &= 0xffff;
#endif
    }
}