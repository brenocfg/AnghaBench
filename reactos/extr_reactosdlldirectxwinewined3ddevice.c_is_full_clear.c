#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wined3d_texture {unsigned int level_count; } ;
struct TYPE_4__ {scalar_t__ left; scalar_t__ top; unsigned int right; unsigned int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned int wined3d_texture_get_level_height (struct wined3d_texture const*,unsigned int) ; 
 unsigned int wined3d_texture_get_level_width (struct wined3d_texture const*,unsigned int) ; 

__attribute__((used)) static BOOL is_full_clear(const struct wined3d_texture *texture, unsigned int sub_resource_idx,
        const RECT *draw_rect, const RECT *clear_rect)
{
    unsigned int width, height, level;

    level = sub_resource_idx % texture->level_count;
    width = wined3d_texture_get_level_width(texture, level);
    height = wined3d_texture_get_level_height(texture, level);

    /* partial draw rect */
    if (draw_rect->left || draw_rect->top || draw_rect->right < width || draw_rect->bottom < height)
        return FALSE;

    /* partial clear rect */
    if (clear_rect && (clear_rect->left > 0 || clear_rect->top > 0
            || clear_rect->right < width || clear_rect->bottom < height))
        return FALSE;

    return TRUE;
}