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
struct TYPE_2__ {scalar_t__ p_sys; } ;
typedef  TYPE_1__ filter_t ;
typedef  int /*<<< orphan*/  SRC_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  src_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close (vlc_object_t *obj)
{
    filter_t *filter = (filter_t *)obj;
    SRC_STATE *s = (SRC_STATE *)filter->p_sys;

    src_delete (s);
}