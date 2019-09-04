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
struct inf_section {int dummy; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 struct inf_value* inf_get_value (struct inf_section*,char const*) ; 
 char* inf_value_get_value (struct inf_value*) ; 

__attribute__((used)) static BOOL section_get_dword(struct inf_section *inf_sec, const char *key, DWORD *value, DWORD def)
{
    struct inf_value *inf_val;
    char *str;

    inf_val = inf_get_value(inf_sec, key);
    if (!inf_val)
    {
        *value = def;
        return TRUE;
    }

    str = inf_value_get_value(inf_val);
    if (!str) return FALSE;

    *value = atoi(str);
    heap_free(str);

    return TRUE;
}