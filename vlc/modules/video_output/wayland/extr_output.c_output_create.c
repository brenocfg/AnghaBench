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
typedef  int uint32_t ;
struct wl_registry {int dummy; } ;
struct output_list {int /*<<< orphan*/  outputs; int /*<<< orphan*/  owner; } ;
struct output_data {int name; int version; int /*<<< orphan*/  node; int /*<<< orphan*/ * wl_output; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct output_data*) ; 
 struct output_data* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_output_add_listener (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct output_data*) ; 
 int /*<<< orphan*/  wl_output_cbs ; 
 int /*<<< orphan*/  wl_output_interface ; 
 int /*<<< orphan*/ * wl_registry_bind (struct wl_registry*,int,int /*<<< orphan*/ *,int) ; 

int output_create(struct output_list *ol, struct wl_registry *registry,
                  uint32_t name, uint32_t version)
{
    if (unlikely(ol == NULL))
        return -1;

    struct output_data *od = malloc(sizeof (*od));
    if (unlikely(od == NULL))
        return -1;

    if (version > 3)
        version = 3;

    od->wl_output = wl_registry_bind(registry, name, &wl_output_interface,
                                     version);
    if (unlikely(od->wl_output == NULL))
    {
        free(od);
        return -1;
    }

    od->owner = ol->owner;
    od->name = name;
    od->version = version;

    wl_output_add_listener(od->wl_output, &wl_output_cbs, od);
    wl_list_insert(&ol->outputs, &od->node);
    return 0;
}