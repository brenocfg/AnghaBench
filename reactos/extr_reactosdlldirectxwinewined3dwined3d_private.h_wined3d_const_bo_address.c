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
struct wined3d_const_bo_address {int dummy; } ;
struct wined3d_bo_address {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct wined3d_const_bo_address *wined3d_const_bo_address(struct wined3d_bo_address *data)
{
    return (struct wined3d_const_bo_address *)data;
}