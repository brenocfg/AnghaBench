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
struct inf_value {char const* value; int /*<<< orphan*/  key; } ;
struct inf_section {int dummy; } ;
struct inf_file {int dummy; } ;

/* Variables and functions */
 struct inf_section* inf_get_section (struct inf_file*,char*) ; 
 scalar_t__ inf_section_next_value (struct inf_section*,struct inf_value**) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncasecmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static const char *get_substitution(struct inf_file *inf, const char *name, int len)
{
    struct inf_section *sec;
    struct inf_value *value = NULL;

    sec = inf_get_section(inf, "Strings");
    if (!sec) return NULL;

    while (inf_section_next_value(sec, &value))
    {
        if (strlen(value->key) == len && !strncasecmp(value->key, name, len))
            return value->value;
    }

    return NULL;
}