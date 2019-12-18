#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_5__ {TYPE_2__* sys; } ;
struct TYPE_6__ {TYPE_1__ owner; } ;
typedef  TYPE_2__ filter_t ;

/* Variables and functions */
 int /*<<< orphan*/ * filter_NewPicture (TYPE_2__*) ; 

__attribute__((used)) static picture_t *new_frame( filter_t *p_filter )
{
    filter_t *p_this = p_filter->owner.sys;
    // the last filter of the internal chain gets its pictures from the original
    // filter source
    return filter_NewPicture( p_this );
}