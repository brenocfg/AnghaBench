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
typedef  int /*<<< orphan*/  UnitType ;

/* Variables and functions */
 int /*<<< orphan*/  UNIT_NAME_ANY ; 
 int /*<<< orphan*/  _UNIT_TYPE_INVALID ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  assert_se (char const*) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  unit_name_is_valid (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_type_from_string (char const*) ; 

UnitType unit_name_to_type(const char *n) {
        const char *e;

        assert(n);

        if (!unit_name_is_valid(n, UNIT_NAME_ANY))
                return _UNIT_TYPE_INVALID;

        assert_se(e = strrchr(n, '.'));

        return unit_type_from_string(e + 1);
}