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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_fourcc_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static vlc_fourcc_t
var_InheritFourcc(vlc_object_t *obj, const char *name)
{
    char *var_value = var_InheritString(obj, name);
    if (!var_value)
        return 0;

    size_t var_len = strlen(var_value);
    if (var_len > 4)
    {
        free(var_value);
        return 0;
    }

    /* Pad with spaces if the string len is less than 4 */
    char value[] = "    ";
    strcpy(value, var_value);
    if (var_len != 4)
        value[var_len] = ' ';
    free(var_value);

    vlc_fourcc_t fourcc;
    memcpy(&fourcc, value, 4);
    return fourcc;
}