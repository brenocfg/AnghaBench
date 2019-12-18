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
struct string {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct conf {int /*<<< orphan*/  arg; } ;
struct command {int offset; } ;

/* Variables and functions */
 char* CONF_OK ; 
 int CONF_UNSET_NUM ; 
 struct string* array_top (int /*<<< orphan*/ *) ; 
 int nc_atoi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *
conf_set_num(struct conf *cf, struct command *cmd, void *conf)
{
    uint8_t *p;
    int num, *np;
    struct string *value;

    p = conf;
    np = (int *)(p + cmd->offset);

    if (*np != CONF_UNSET_NUM) {
        return "is a duplicate";
    }

    value = array_top(&cf->arg);

    num = nc_atoi(value->data, value->len);
    if (num < 0) {
        return "is not a number";
    }

    *np = num;

    return CONF_OK;
}