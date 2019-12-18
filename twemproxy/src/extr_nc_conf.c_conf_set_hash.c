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
struct string {scalar_t__ len; } ;
struct conf {int /*<<< orphan*/  arg; } ;
struct command {int offset; } ;
typedef  int hash_type_t ;

/* Variables and functions */
 char* CONF_OK ; 
 int CONF_UNSET_HASH ; 
 struct string* array_top (int /*<<< orphan*/ *) ; 
 struct string* hash_strings ; 
 scalar_t__ string_compare (struct string*,struct string*) ; 

char *
conf_set_hash(struct conf *cf, struct command *cmd, void *conf)
{
    uint8_t *p;
    hash_type_t *hp;
    struct string *value, *hash;

    p = conf;
    hp = (hash_type_t *)(p + cmd->offset);

    if (*hp != CONF_UNSET_HASH) {
        return "is a duplicate";
    }

    value = array_top(&cf->arg);

    for (hash = hash_strings; hash->len != 0; hash++) {
        if (string_compare(value, hash) != 0) {
            continue;
        }

        *hp = hash - hash_strings;

        return CONF_OK;
    }

    return "is not a valid hash";
}