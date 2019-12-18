#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ type; } ;
struct TYPE_9__ {TYPE_2__* manager; TYPE_1__* network; } ;
struct TYPE_8__ {TYPE_4__ duid; } ;
struct TYPE_7__ {TYPE_4__ duid; } ;
typedef  TYPE_3__ Link ;
typedef  TYPE_4__ DUID ;

/* Variables and functions */
 scalar_t__ _DUID_TYPE_INVALID ; 

DUID* link_get_duid(Link *link) {
        if (link->network->duid.type != _DUID_TYPE_INVALID)
                return &link->network->duid;
        else
                return &link->manager->duid;
}