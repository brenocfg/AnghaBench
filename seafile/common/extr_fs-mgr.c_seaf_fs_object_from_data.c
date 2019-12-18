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
typedef  int /*<<< orphan*/  SeafFSObject ;

/* Variables and functions */
 int /*<<< orphan*/ * fs_object_from_json (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * fs_object_from_v0_data (char const*,int /*<<< orphan*/ *,int) ; 

SeafFSObject *
seaf_fs_object_from_data (const char *obj_id,
                          uint8_t *data, int len,
                          gboolean is_json)
{
    if (is_json)
        return fs_object_from_json (obj_id, data, len);
    else
        return fs_object_from_v0_data (obj_id, data, len);
}