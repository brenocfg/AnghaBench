#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  json_t ;
typedef  int /*<<< orphan*/  guint8 ;
struct TYPE_3__ {int block_nr; int /*<<< orphan*/ * blk_sha1s; int /*<<< orphan*/  file_size; } ;
typedef  TYPE_1__ CDCFileDescriptor ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_SORT_KEYS ; 
 int /*<<< orphan*/  SEAF_METADATA_TYPE_FILE ; 
 int /*<<< orphan*/  calculate_sha1 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * json_array () ; 
 int /*<<< orphan*/  json_array_append_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object () ; 
 int /*<<< orphan*/  json_object_set_int_member (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_set_new (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_string (char*) ; 
 int /*<<< orphan*/  rawdata_to_hex (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  seafile_version_from_repo_version (int) ; 
 int strlen (char*) ; 

void
seaf_fs_manager_calculate_seafile_id_json (int repo_version,
                                           CDCFileDescriptor *cdc,
                                           guint8 *file_id_sha1)
{
    json_t *object, *block_id_array;

    object = json_object ();

    json_object_set_int_member (object, "type", SEAF_METADATA_TYPE_FILE);
    json_object_set_int_member (object, "version",
                                seafile_version_from_repo_version(repo_version));

    json_object_set_int_member (object, "size", cdc->file_size);

    block_id_array = json_array ();
    int i;
    uint8_t *ptr = cdc->blk_sha1s;
    char block_id[41];
    for (i = 0; i < cdc->block_nr; ++i) {
        rawdata_to_hex (ptr, block_id, 20);
        json_array_append_new (block_id_array, json_string(block_id));
        ptr += 20;
    }
    json_object_set_new (object, "block_ids", block_id_array);

    char *data = json_dumps (object, JSON_SORT_KEYS);
    int ondisk_size = strlen(data);

    /* The seafile object id is sha1 hash of the json object. */
    calculate_sha1 (file_id_sha1, data, ondisk_size);

    json_decref (object);
    free (data);
}