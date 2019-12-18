#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  size_t ssize_t ;

/* Variables and functions */

__attribute__((used)) static ssize_t Read (stream_t *access, void *buf, size_t len)
{
    char *in = access->p_sys, *out = buf;
    size_t i;

    for (i = 0; i < len && *in != '\0'; i++)
        *(out++) = *(in++);

    access->p_sys = in;
    return i;
}