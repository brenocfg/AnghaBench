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

/* Variables and functions */
 int /*<<< orphan*/  object_path_is_valid (char const*) ; 
 int /*<<< orphan*/  validate_nul (char const*,size_t) ; 

__attribute__((used)) static bool validate_object_path(const char *s, size_t l) {

        if (!validate_nul(s, l))
                return false;

        if (!object_path_is_valid(s))
                return false;

        return true;
}