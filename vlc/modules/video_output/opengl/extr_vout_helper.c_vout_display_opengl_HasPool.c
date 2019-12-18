#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* prgm; } ;
typedef  TYPE_2__ vout_display_opengl_t ;
struct TYPE_7__ {int /*<<< orphan*/ * pf_get_pool; } ;
typedef  TYPE_3__ opengl_tex_converter_t ;
struct TYPE_5__ {TYPE_3__* tc; } ;

/* Variables and functions */

bool vout_display_opengl_HasPool(const vout_display_opengl_t *vgl)
{
    opengl_tex_converter_t *tc = vgl->prgm->tc;
    return tc->pf_get_pool != NULL;
}