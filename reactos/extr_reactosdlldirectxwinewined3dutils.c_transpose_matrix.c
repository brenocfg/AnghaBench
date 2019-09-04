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
struct wined3d_matrix {int /*<<< orphan*/  _11; } ;

/* Variables and functions */

void transpose_matrix(struct wined3d_matrix *out, const struct wined3d_matrix *m)
{
    struct wined3d_matrix temp;
    unsigned int i, j;

    for (i = 0; i < 4; ++i)
        for (j = 0; j < 4; ++j)
            (&temp._11)[4 * j + i] = (&m->_11)[4 * i + j];

    *out = temp;
}