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
struct keysym {scalar_t__ xsym; } ;

/* Variables and functions */

__attribute__((used)) static int cmpkey (const void *va, const void *vb)
{
    const struct keysym *ka = va, *kb = vb;

    if (ka->xsym > kb->xsym)
        return +1;
    if (ka->xsym < kb->xsym)
        return -1;
    return 0;
}