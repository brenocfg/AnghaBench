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
 int /*<<< orphan*/  const* _JSON_VARIANT_MAGIC_MAX ; 

__attribute__((used)) static bool json_variant_is_magic(const JsonVariant *v) {
        if (!v)
                return false;

        return v < _JSON_VARIANT_MAGIC_MAX;
}