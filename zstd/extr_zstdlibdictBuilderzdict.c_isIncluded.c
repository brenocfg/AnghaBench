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

__attribute__((used)) static int isIncluded(const void* in, const void* container, size_t length)
{
    const char* const ip = (const char*) in;
    const char* const into = (const char*) container;
    size_t u;

    for (u=0; u<length; u++) {  /* works because end of buffer is a noisy guard band */
        if (ip[u] != into[u]) break;
    }

    return u==length;
}