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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct vlc_res {int dummy; } ;
struct TYPE_2__ {struct vlc_res* resources; } ;

/* Variables and functions */
 TYPE_1__* vlc_internals (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct vlc_res **vlc_obj_res(vlc_object_t *obj)
{
    return &vlc_internals(obj)->resources;
}