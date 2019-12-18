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

/* Variables and functions */
 char* g_malloc (int) ; 
 int /*<<< orphan*/  uuid_generate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_unparse_lower (int /*<<< orphan*/ ,char*) ; 

char* gen_uuid ()
{
    char *uuid_str = g_malloc (37);
    uuid_t uuid;

    uuid_generate (uuid);
    uuid_unparse_lower (uuid, uuid_str);

    return uuid_str;
}