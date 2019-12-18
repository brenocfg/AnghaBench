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
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  Seafile ;

/* Variables and functions */
 int /*<<< orphan*/ * seafile_from_json (char const*,void*,int) ; 
 int /*<<< orphan*/ * seafile_from_v0_data (char const*,void*,int) ; 

__attribute__((used)) static Seafile *
seafile_from_data (const char *id, void *data, int len, gboolean is_json)
{
    if (is_json)
        return seafile_from_json (id, data, len);
    else
        return seafile_from_v0_data (id, data, len);
}