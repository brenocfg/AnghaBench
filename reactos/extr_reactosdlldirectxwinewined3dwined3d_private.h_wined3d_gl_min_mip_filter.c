#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum wined3d_texture_filter_type { ____Placeholder_wined3d_texture_filter_type } wined3d_texture_filter_type ;
struct TYPE_2__ {int /*<<< orphan*/ * mip; } ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 TYPE_1__* minMipLookup ; 

__attribute__((used)) static inline GLenum wined3d_gl_min_mip_filter(enum wined3d_texture_filter_type min_filter,
        enum wined3d_texture_filter_type mip_filter)
{
    return minMipLookup[min_filter].mip[mip_filter];
}