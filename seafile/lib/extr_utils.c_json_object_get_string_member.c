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
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/ *,char const*) ; 
 char const* json_string_value (int /*<<< orphan*/ *) ; 

const char *
json_object_get_string_member (json_t *object, const char *key)
{
    json_t *string = json_object_get (object, key);
    if (!string)
        return NULL;
    return json_string_value (string);
}