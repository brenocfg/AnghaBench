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
struct device {int /*<<< orphan*/  item; scalar_t__ sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct device*) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  services_discovery_RemoveItem (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DestroyDevice (void *data)
{
    struct device *d = data;

    if (d->sd)
        services_discovery_RemoveItem (d->sd, d->item);
    input_item_Release (d->item);
    free (d);
}