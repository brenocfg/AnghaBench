#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* current_token; struct TYPE_8__* tokens; } ;
typedef  TYPE_1__ UdevRuleToken ;
typedef  TYPE_1__ UdevRuleLine ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_APPEND (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static void rule_line_append_token(UdevRuleLine *rule_line, UdevRuleToken *token) {
        assert(rule_line);
        assert(token);

        if (rule_line->current_token)
                LIST_APPEND(tokens, rule_line->current_token, token);
        else
                LIST_APPEND(tokens, rule_line->tokens, token);

        rule_line->current_token = token;
}