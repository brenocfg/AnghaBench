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
typedef  int /*<<< orphan*/  UnitNameMangle ;

/* Variables and functions */
 int unit_name_mangle_with_suffix (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char**) ; 

__attribute__((used)) static inline int unit_name_mangle(const char *name, UnitNameMangle flags, char **ret) {
        return unit_name_mangle_with_suffix(name, NULL, flags, ".service", ret);
}