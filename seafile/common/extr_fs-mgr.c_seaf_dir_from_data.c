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
typedef  int /*<<< orphan*/  SeafDir ;

/* Variables and functions */
 int /*<<< orphan*/ * seaf_dir_from_json (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * seaf_dir_from_v0_data (char const*,int /*<<< orphan*/ *,int) ; 

SeafDir *
seaf_dir_from_data (const char *dir_id, uint8_t *data, int len,
                    gboolean is_json)
{
    if (is_json)
        return seaf_dir_from_json (dir_id, data, len);
    else
        return seaf_dir_from_v0_data (dir_id, data, len);
}