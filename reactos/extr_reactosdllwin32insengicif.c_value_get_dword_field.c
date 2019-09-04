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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  value_get_str_field (struct inf_value*,int,char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL value_get_dword_field(struct inf_value *inf_val, int field, DWORD *value, DWORD def)
{
    char *value_str;
    BOOL ret;

    ret = value_get_str_field(inf_val, field, &value_str, NULL);
    if (!ret) return FALSE;
    if (!value_str)
    {
        *value = def;
        return TRUE;
    }

    *value = atoi(value_str);
    heap_free(value_str);

    return TRUE;
}