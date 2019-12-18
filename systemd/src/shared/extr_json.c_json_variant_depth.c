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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  depth; } ;
typedef  TYPE_1__ JsonVariant ;

/* Variables and functions */
 TYPE_1__* json_variant_dereference (TYPE_1__*) ; 
 int /*<<< orphan*/  json_variant_is_regular (TYPE_1__*) ; 

__attribute__((used)) static uint16_t json_variant_depth(JsonVariant *v) {

        v = json_variant_dereference(v);
        if (!v)
                return 0;

        if (!json_variant_is_regular(v))
                return 0;

        return v->depth;
}