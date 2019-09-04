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
struct wined3d_cs {int dummy; } ;
typedef  enum wined3d_cs_queue_id { ____Placeholder_wined3d_cs_queue_id } wined3d_cs_queue_id ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL wined3d_cs_st_check_space(struct wined3d_cs *cs, size_t size, enum wined3d_cs_queue_id queue_id)
{
    return TRUE;
}