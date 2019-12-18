#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ n_ref; struct TYPE_7__* parent; scalar_t__ is_embedded; } ;
typedef  TYPE_1__ JsonVariant ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  json_variant_free_inner (TYPE_1__*) ; 
 int /*<<< orphan*/  json_variant_is_regular (TYPE_1__*) ; 

JsonVariant *json_variant_unref(JsonVariant *v) {
        if (!v)
                return NULL;
        if (!json_variant_is_regular(v))
                return NULL;

        if (v->is_embedded)
                json_variant_unref(v->parent);
        else {
                assert(v->n_ref > 0);
                v->n_ref--;

                if (v->n_ref == 0) {
                        json_variant_free_inner(v);
                        free(v);
                }
        }

        return NULL;
}