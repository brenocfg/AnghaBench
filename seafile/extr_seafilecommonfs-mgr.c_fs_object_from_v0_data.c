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
typedef  int /*<<< orphan*/  SeafFSObject ;

/* Variables and functions */
 int SEAF_METADATA_TYPE_DIR ; 
 int SEAF_METADATA_TYPE_FILE ; 
 int parse_metadata_type_v0 (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ seaf_dir_from_v0_data (char const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  seaf_warning (char*,int) ; 
 scalar_t__ seafile_from_v0_data (char const*,int /*<<< orphan*/  const*,int) ; 

SeafFSObject *
fs_object_from_v0_data (const char *obj_id, const uint8_t *data, int len)
{
    int type = parse_metadata_type_v0 (data, len);

    if (type == SEAF_METADATA_TYPE_FILE)
        return (SeafFSObject *)seafile_from_v0_data (obj_id, data, len);
    else if (type == SEAF_METADATA_TYPE_DIR)
        return (SeafFSObject *)seaf_dir_from_v0_data (obj_id, data, len);
    else {
        seaf_warning ("Invalid object type %d.\n", type);
        return NULL;
    }
}