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

__attribute__((used)) static unsigned hash_Ly(const char *str)
{
    unsigned hash = 0;

    for (; *str; str++)
        hash = hash * 1664525u + (unsigned char)(*str) + 1013904223u;

    return hash;
}