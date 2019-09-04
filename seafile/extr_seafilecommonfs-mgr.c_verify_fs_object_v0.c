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
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  SEAF_METADATA_TYPE_DIR 129 
#define  SEAF_METADATA_TYPE_FILE 128 
 int /*<<< orphan*/  TRUE ; 
 int seaf_metadata_type_from_data (char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,int) ; 
 int /*<<< orphan*/  verify_seafdir_v0 (char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_seafile_v0 (char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean
verify_fs_object_v0 (const char *obj_id,
                     uint8_t *data,
                     int len,
                     gboolean verify_id)
{
    gboolean ret = TRUE;

    int type = seaf_metadata_type_from_data (obj_id, data, len, FALSE);
    switch (type) {
    case SEAF_METADATA_TYPE_FILE:
        ret = verify_seafile_v0 (obj_id, data, len, verify_id);
        break;
    case SEAF_METADATA_TYPE_DIR:
        ret = verify_seafdir_v0 (obj_id, data, len, verify_id);
        break;
    default:
        seaf_warning ("Invalid meta data type: %d.\n", type);
        return FALSE;
    }

    return ret;
}