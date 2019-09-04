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
struct wined3d_format {int id; } ;
typedef  enum wined3d_format_id { ____Placeholder_wined3d_format_id } wined3d_format_id ;

/* Variables and functions */

__attribute__((used)) static void copy_format(struct wined3d_format *dst_format, const struct wined3d_format *src_format)
{
    enum wined3d_format_id id = dst_format->id;
    *dst_format = *src_format;
    dst_format->id = id;
}