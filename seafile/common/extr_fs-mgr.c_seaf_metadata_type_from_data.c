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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ gboolean ;

/* Variables and functions */
 int parse_metadata_type_json (char const*,int /*<<< orphan*/ *,int) ; 
 int parse_metadata_type_v0 (int /*<<< orphan*/ *,int) ; 

int
seaf_metadata_type_from_data (const char *obj_id,
                              uint8_t *data, int len, gboolean is_json)
{
    if (is_json)
        return parse_metadata_type_json (obj_id, data, len);
    else
        return parse_metadata_type_v0 (data, len);
}