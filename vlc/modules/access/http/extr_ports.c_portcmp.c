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

__attribute__((used)) static int portcmp(const void *key, const void *entry)
{
    const unsigned *port = key;
    const unsigned short *blocked_port = entry;

    return ((int)*port) - ((int)*blocked_port);
}