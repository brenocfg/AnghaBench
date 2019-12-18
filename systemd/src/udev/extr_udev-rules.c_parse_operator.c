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
typedef  int /*<<< orphan*/  UdevRuleOperatorType ;

/* Variables and functions */
 int /*<<< orphan*/  OP_ADD ; 
 int /*<<< orphan*/  OP_ASSIGN ; 
 int /*<<< orphan*/  OP_ASSIGN_FINAL ; 
 int /*<<< orphan*/  OP_MATCH ; 
 int /*<<< orphan*/  OP_NOMATCH ; 
 int /*<<< orphan*/  OP_REMOVE ; 
 int /*<<< orphan*/  _OP_TYPE_INVALID ; 
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ startswith (char const*,char*) ; 

__attribute__((used)) static UdevRuleOperatorType parse_operator(const char *op) {
        assert(op);

        if (startswith(op, "=="))
                return OP_MATCH;
        if (startswith(op, "!="))
                return OP_NOMATCH;
        if (startswith(op, "+="))
                return OP_ADD;
        if (startswith(op, "-="))
                return OP_REMOVE;
        if (startswith(op, "="))
                return OP_ASSIGN;
        if (startswith(op, ":="))
                return OP_ASSIGN_FINAL;

        return _OP_TYPE_INVALID;
}