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
struct inf_value {int dummy; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  copy_string (char**,char const*) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 char* inf_value_get_value (struct inf_value*) ; 
 char* next_part (char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL value_get_str_field(struct inf_value *inf_val, int field, char **value, const char *def)
{
    char *line, *str, *next;
    int i = 0;

    line = inf_value_get_value(inf_val);
    if (!line) return FALSE;

    str = line;
    do
    {
        i++;
        next = next_part(&str, TRUE);

        if (field == i)
        {
            BOOL ret = copy_string(value, str);
            heap_free(line);
            return ret;
        }

        str = next;
    } while (str);

    return copy_string(value, def);
}