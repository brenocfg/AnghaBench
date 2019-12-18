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
typedef  int /*<<< orphan*/  services_discovery_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * input_item_NewCard (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  services_discovery_AddItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void AddDesktop(services_discovery_t *sd)
{
    input_item_t *item;

    item = input_item_NewCard ("screen://", _("Desktop"));
    if (item == NULL)
        return;

    services_discovery_AddItem(sd, item);
    input_item_Release (item);
}