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
typedef  int /*<<< orphan*/  UdevRuleSubstituteType ;

/* Variables and functions */
 int /*<<< orphan*/  SUBST_TYPE_FORMAT ; 
 int /*<<< orphan*/  SUBST_TYPE_PLAIN ; 
 int /*<<< orphan*/  SUBST_TYPE_SUBSYS ; 
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ strchr (char const*,char) ; 

__attribute__((used)) static UdevRuleSubstituteType rule_get_substitution_type(const char *str) {
        assert(str);

        if (str[0] == '[')
                return SUBST_TYPE_SUBSYS;
        if (strchr(str, '%') || strchr(str, '$'))
                return SUBST_TYPE_FORMAT;
        return SUBST_TYPE_PLAIN;
}