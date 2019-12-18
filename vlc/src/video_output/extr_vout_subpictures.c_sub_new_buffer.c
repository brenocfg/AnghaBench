#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  i_channel; } ;
typedef  TYPE_2__ subpicture_t ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_7__ {scalar_t__ sys; } ;
struct TYPE_9__ {TYPE_1__ owner; } ;
typedef  TYPE_3__ filter_t ;

/* Variables and functions */
 TYPE_2__* subpicture_New (int /*<<< orphan*/ *) ; 

__attribute__((used)) static subpicture_t *sub_new_buffer(filter_t *filter)
{
    ssize_t channel = *(ssize_t *)filter->owner.sys;

    subpicture_t *subpicture = subpicture_New(NULL);
    if (subpicture)
        subpicture->i_channel = channel;
    return subpicture;
}