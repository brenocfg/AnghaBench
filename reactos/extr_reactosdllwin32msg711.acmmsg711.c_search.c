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

/* Variables and functions */

__attribute__((used)) static short
search(
    int		val,	        /* changed from "short" *drago* */
    const short	*table,
    int		size)	        /* changed from "short" *drago* */
{
    int		i;	/* changed from "short" *drago* */

    for (i = 0; i < size; i++) {
        if (val <= *table++)
            return (i);
    }
    return (size);
}