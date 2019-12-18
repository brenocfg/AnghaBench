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
typedef  int const uint64_t ;
typedef  int /*<<< orphan*/  list ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char const* const) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static uint64_t qsv_params_get_value(const char *const *text,
                                     const int *list,
                                     size_t size, char *sel)
{
    size_t result = 0;

    if (unlikely(!sel))
        return list[0];

    size /= sizeof(list[0]);
    for (size_t i = 0; i < size; i++)
        if (!strcmp(sel, text[i])) {
            result = i;
            break;
        }

    // sel comes from var_InheritString and must be freed.
    free(sel);
    // Returns the found item, or the default/first one if not found.
    return list[result];
}