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
typedef  int /*<<< orphan*/  gint64 ;

/* Variables and functions */
 int /*<<< orphan*/  json_integer_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/ *,char const*) ; 

gint64
json_object_get_int_member (json_t *object, const char *key)
{
    json_t *integer = json_object_get (object, key);
    return json_integer_value (integer);
}