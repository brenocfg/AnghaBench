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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ uuid_parse (char const*,int /*<<< orphan*/ ) ; 

gboolean
is_uuid_valid (const char *uuid_str)
{
    uuid_t uuid;

    if (!uuid_str)
        return FALSE;

    if (uuid_parse (uuid_str, uuid) < 0)
        return FALSE;
    return TRUE;
}