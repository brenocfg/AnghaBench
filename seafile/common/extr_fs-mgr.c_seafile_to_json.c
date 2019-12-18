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
typedef  int /*<<< orphan*/  json_t ;
typedef  int /*<<< orphan*/  guint8 ;
struct TYPE_3__ {int n_blocks; int /*<<< orphan*/  file_id; int /*<<< orphan*/ * blk_sha1s; int /*<<< orphan*/  file_size; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ Seafile ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_SORT_KEYS ; 
 int /*<<< orphan*/  SEAF_METADATA_TYPE_FILE ; 
 int /*<<< orphan*/  calculate_sha1 (unsigned char*,char*,int) ; 
 int /*<<< orphan*/ * json_array () ; 
 int /*<<< orphan*/  json_array_append_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object () ; 
 int /*<<< orphan*/  json_object_set_int_member (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_set_new (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rawdata_to_hex (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static guint8 *
seafile_to_json (Seafile *file, int *len)
{
    json_t *object, *block_id_array;

    object = json_object ();

    json_object_set_int_member (object, "type", SEAF_METADATA_TYPE_FILE);
    json_object_set_int_member (object, "version", file->version);

    json_object_set_int_member (object, "size", file->file_size);

    block_id_array = json_array ();
    int i;
    for (i = 0; i < file->n_blocks; ++i) {
        json_array_append_new (block_id_array, json_string(file->blk_sha1s[i]));
    }
    json_object_set_new (object, "block_ids", block_id_array);

    char *data = json_dumps (object, JSON_SORT_KEYS);
    *len = strlen(data);

    unsigned char sha1[20];
    calculate_sha1 (sha1, data, *len);
    rawdata_to_hex (sha1, file->file_id, 20);

    json_decref (object);
    return (guint8 *)data;
}