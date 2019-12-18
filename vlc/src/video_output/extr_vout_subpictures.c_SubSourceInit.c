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
struct TYPE_4__ {int /*<<< orphan*/ * sub; int /*<<< orphan*/ * sys; } ;
struct TYPE_5__ {TYPE_1__ owner; } ;
typedef  TYPE_2__ filter_t ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  spu_RegisterChannel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sub_cbs ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int SubSourceInit(filter_t *filter, void *data)
{
    spu_t *spu = data;
    ssize_t *channel = malloc(sizeof (ssize_t));
    if (unlikely(channel == NULL))
        return VLC_ENOMEM;

    *channel = spu_RegisterChannel(spu);
    filter->owner.sys = channel;
    filter->owner.sub = &sub_cbs;
    return VLC_SUCCESS;
}