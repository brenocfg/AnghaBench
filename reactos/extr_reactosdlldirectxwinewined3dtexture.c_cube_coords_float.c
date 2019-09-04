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
struct wined3d_rect_f {float l; float t; float r; float b; } ;
typedef  float UINT ;
struct TYPE_3__ {float left; float top; float right; float bottom; } ;
typedef  TYPE_1__ RECT ;

/* Variables and functions */

__attribute__((used)) static inline void cube_coords_float(const RECT *r, UINT w, UINT h, struct wined3d_rect_f *f)
{
    f->l = ((r->left * 2.0f) / w) - 1.0f;
    f->t = ((r->top * 2.0f) / h) - 1.0f;
    f->r = ((r->right * 2.0f) / w) - 1.0f;
    f->b = ((r->bottom * 2.0f) / h) - 1.0f;
}