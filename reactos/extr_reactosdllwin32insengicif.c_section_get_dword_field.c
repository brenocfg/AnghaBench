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
 int /*<<< orphan*/  TRUE ; 
 struct inf_value* inf_get_value (struct inf_section*,char const*) ; 
 int /*<<< orphan*/  value_get_dword_field (struct inf_value*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL section_get_dword_field(struct inf_section *inf_sec, const char *key, int field, DWORD *value, DWORD def)
{
    struct inf_value *inf_val;

    inf_val = inf_get_value(inf_sec, key);
    if (!inf_val)
    {
        *value = def;
        return TRUE;
    }

    return value_get_dword_field(inf_val, field, value, def);
}