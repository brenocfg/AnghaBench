#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int n_ref; struct TYPE_4__* parent; scalar_t__ is_embedded; } ;
typedef  TYPE_1__ JsonVariant ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  json_variant_is_regular (TYPE_1__*) ; 

__attribute__((used)) static bool json_single_ref(JsonVariant *v) {

        /* Checks whether the caller is the single owner of the object, i.e. can get away with changing it */

        if (!json_variant_is_regular(v))
                return false;

        if (v->is_embedded)
                return json_single_ref(v->parent);

        assert(v->n_ref > 0);
        return v->n_ref == 1;
}