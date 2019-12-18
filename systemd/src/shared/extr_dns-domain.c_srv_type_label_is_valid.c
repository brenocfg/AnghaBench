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
 int /*<<< orphan*/  assert (char const*) ; 

__attribute__((used)) static bool srv_type_label_is_valid(const char *label, size_t n) {
        size_t k;

        assert(label);

        if (n < 2) /* Label needs to be at least 2 chars long */
                return false;

        if (label[0] != '_') /* First label char needs to be underscore */
                return false;

        /* Second char must be a letter */
        if (!(label[1] >= 'A' && label[1] <= 'Z') &&
            !(label[1] >= 'a' && label[1] <= 'z'))
                return false;

        /* Third and further chars must be alphanumeric or a hyphen */
        for (k = 2; k < n; k++) {
                if (!(label[k] >= 'A' && label[k] <= 'Z') &&
                    !(label[k] >= 'a' && label[k] <= 'z') &&
                    !(label[k] >= '0' && label[k] <= '9') &&
                    label[k] != '-')
                        return false;
        }

        return true;
}