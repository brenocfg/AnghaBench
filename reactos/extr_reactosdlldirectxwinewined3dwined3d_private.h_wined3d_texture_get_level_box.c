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
struct wined3d_texture {int dummy; } ;
struct wined3d_box {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wined3d_box_set (struct wined3d_box*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_get_level_depth (struct wined3d_texture const*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_get_level_height (struct wined3d_texture const*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_get_level_width (struct wined3d_texture const*,unsigned int) ; 

__attribute__((used)) static inline void wined3d_texture_get_level_box(const struct wined3d_texture *texture,
        unsigned int level, struct wined3d_box *box)
{
    wined3d_box_set(box, 0, 0,
            wined3d_texture_get_level_width(texture, level),
            wined3d_texture_get_level_height(texture, level),
            0, wined3d_texture_get_level_depth(texture, level));
}