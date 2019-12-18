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
struct entry_item {int /*<<< orphan*/ * p_item; int /*<<< orphan*/ * p_entry; } ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ services_discovery_t ;
struct TYPE_6__ {int /*<<< orphan*/  entry_item_list; } ;
typedef  TYPE_2__ services_discovery_sys_t ;
typedef  int /*<<< orphan*/  netbios_ns_entry ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 struct entry_item* calloc (int,int) ; 
 int /*<<< orphan*/  input_item_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  services_discovery_AddItem (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_array_append_or_abort (int /*<<< orphan*/ *,struct entry_item*) ; 

__attribute__((used)) static void entry_item_append( services_discovery_t *p_sd,
                               netbios_ns_entry *p_entry,
                               input_item_t *p_item )
{
    services_discovery_sys_t *p_sys = p_sd->p_sys;
    struct entry_item *p_entry_item = calloc(1, sizeof(struct entry_item));

    if( !p_entry_item )
        return;
    p_entry_item->p_entry = p_entry;
    p_entry_item->p_item = p_item;
    input_item_Hold( p_item );
    vlc_array_append_or_abort( &p_sys->entry_item_list, p_entry_item );
    services_discovery_AddItem( p_sd, p_item );
}