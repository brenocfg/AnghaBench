#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* name; int (* parser ) (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **,TYPE_2__*) ;int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ condition_definition ;
struct TYPE_8__ {int /*<<< orphan*/ * asserts; int /*<<< orphan*/ * conditions; } ;
typedef  TYPE_2__ Unit ;
typedef  int /*<<< orphan*/  Condition ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 size_t ELEMENTSOF (TYPE_1__*) ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WHITESPACE ; 
 TYPE_1__* condition_definitions ; 
 int log_error_errno (int /*<<< orphan*/ ,char*,char const*) ; 
 char* startswith (char const*,char*) ; 
 scalar_t__ strspn (char const*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **,TYPE_2__*) ; 

__attribute__((used)) static int parse_condition(Unit *u, const char *line) {
        const char *p;
        Condition **target;

        if ((p = startswith(line, "Condition")))
                target = &u->conditions;
        else if ((p = startswith(line, "Assert")))
                target = &u->asserts;
        else
                return log_error_errno(SYNTHETIC_ERRNO(EINVAL), "Cannot parse \"%s\".", line);

        for (size_t i = 0; i < ELEMENTSOF(condition_definitions); i++) {
                const condition_definition *c = &condition_definitions[i];

                p = startswith(line, c->name);
                if (!p)
                        continue;
                p += strspn(p, WHITESPACE);
                if (*p != '=')
                        return log_error_errno(SYNTHETIC_ERRNO(EINVAL), "Expected \"=\" in \"%s\".", line);

                p += 1 + strspn(p + 1, WHITESPACE);

                return c->parser(NULL, "(stdin)", 0, NULL, 0, c->name, c->type, p, target, u);
        }

        return log_error_errno(SYNTHETIC_ERRNO(EINVAL), "Cannot parse \"%s\".", line);
}