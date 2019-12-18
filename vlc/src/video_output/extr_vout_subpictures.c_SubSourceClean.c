#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  spu_t ;
struct TYPE_4__ {int /*<<< orphan*/ * sys; } ;
struct TYPE_5__ {TYPE_1__ owner; } ;
typedef  TYPE_2__ filter_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_ClearChannel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int SubSourceClean(filter_t *filter, void *data)
{
    spu_t *spu = data;
    ssize_t *channel = filter->owner.sys;

    spu_ClearChannel(spu, *channel);
    free(channel);
    return VLC_SUCCESS;
}