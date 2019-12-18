#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  polkit_registry; int /*<<< orphan*/  vc_cache; int /*<<< orphan*/  x11_cache; int /*<<< orphan*/  locale_cache; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  bus_verify_polkit_async_registry_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_free_locale (TYPE_1__*) ; 
 int /*<<< orphan*/  context_free_vconsole (TYPE_1__*) ; 
 int /*<<< orphan*/  context_free_x11 (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_bus_message_unref (int /*<<< orphan*/ ) ; 

void context_clear(Context *c) {
        context_free_locale(c);
        context_free_x11(c);
        context_free_vconsole(c);

        sd_bus_message_unref(c->locale_cache);
        sd_bus_message_unref(c->x11_cache);
        sd_bus_message_unref(c->vc_cache);

        bus_verify_polkit_async_registry_free(c->polkit_registry);
}