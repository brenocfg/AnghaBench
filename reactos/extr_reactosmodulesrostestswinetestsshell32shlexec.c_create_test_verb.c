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
 int /*<<< orphan*/  create_test_verb_dde (char const*,char const*,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_association_description () ; 

__attribute__((used)) static void create_test_verb(const char* classname, const char* verb,
                             int rawcmd, const char* cmdtail)
{
    create_test_verb_dde(classname, verb, rawcmd, cmdtail, NULL, NULL,
                         NULL, NULL);
    reset_association_description();
}