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
typedef  int /*<<< orphan*/  JsonVariant ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_variant_unref (int /*<<< orphan*/ *) ; 

void json_variant_unref_many(JsonVariant **array, size_t n) {
        size_t i;

        assert(array || n == 0);

        for (i = 0; i < n; i++)
                json_variant_unref(array[i]);
}