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
typedef  int /*<<< orphan*/  uint8_t ;
struct string {int dummy; } ;
struct conf {int /*<<< orphan*/  arg; } ;
struct command {int offset; } ;

/* Variables and functions */
 char* CONF_OK ; 
 int CONF_UNSET_NUM ; 
 struct string* array_top (int /*<<< orphan*/ *) ; 
 scalar_t__ string_compare (struct string*,struct string*) ; 
 int /*<<< orphan*/  string_set_text (struct string*,char*) ; 

char *
conf_set_bool(struct conf *cf, struct command *cmd, void *conf)
{
    uint8_t *p;
    int *bp;
    struct string *value, true_str, false_str;

    p = conf;
    bp = (int *)(p + cmd->offset);

    if (*bp != CONF_UNSET_NUM) {
        return "is a duplicate";
    }

    value = array_top(&cf->arg);
    string_set_text(&true_str, "true");
    string_set_text(&false_str, "false");

    if (string_compare(value, &true_str) == 0) {
        *bp = 1;
    } else if (string_compare(value, &false_str) == 0) {
        *bp = 0;
    } else {
        return "is not \"true\" or \"false\"";
    }

    return CONF_OK;
}