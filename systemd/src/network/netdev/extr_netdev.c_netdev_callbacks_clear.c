#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  link; } ;
typedef  TYPE_1__ netdev_join_callback ;
struct TYPE_8__ {TYPE_1__* callbacks; } ;
typedef  TYPE_2__ NetDev ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  callbacks ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  link_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netdev_callbacks_clear(NetDev *netdev) {
        netdev_join_callback *callback;

        if (!netdev)
                return;

        while ((callback = netdev->callbacks)) {
                LIST_REMOVE(callbacks, netdev->callbacks, callback);
                link_unref(callback->link);
                free(callback);
        }
}