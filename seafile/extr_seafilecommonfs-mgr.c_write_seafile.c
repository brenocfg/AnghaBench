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
typedef  void guint8 ;
struct TYPE_3__ {int /*<<< orphan*/  obj_store; } ;
typedef  TYPE_1__ SeafFSManager ;
typedef  int /*<<< orphan*/  CDCFileDescriptor ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 void* create_seafile_json (int,int /*<<< orphan*/ *,int*,char*) ; 
 void* create_seafile_v0 (int /*<<< orphan*/ *,int*,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  g_free (void*) ; 
 int /*<<< orphan*/  hex_to_rawdata (char*,unsigned char*,int) ; 
 scalar_t__ seaf_compress (void*,int,void**,int*) ; 
 scalar_t__ seaf_obj_store_write_obj (int /*<<< orphan*/ ,char const*,int,char*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,char*) ; 

__attribute__((used)) static int
write_seafile (SeafFSManager *fs_mgr,
               const char *repo_id,
               int version,
               CDCFileDescriptor *cdc,
               unsigned char *obj_sha1)
{
    int ret = 0;
    char seafile_id[41];
    void *ondisk;
    int ondisk_size;

    if (version > 0) {
        ondisk = create_seafile_json (version, cdc, &ondisk_size, seafile_id);

        guint8 *compressed;
        int outlen;

        if (seaf_compress (ondisk, ondisk_size, &compressed, &outlen) < 0) {
            seaf_warning ("Failed to compress seafile obj %s:%s.\n",
                          repo_id, seafile_id);
            ret = -1;
            free (ondisk);
            goto out;
        }

        if (seaf_obj_store_write_obj (fs_mgr->obj_store, repo_id, version, seafile_id,
                                      compressed, outlen, FALSE) < 0)
            ret = -1;
        g_free (compressed);
        free (ondisk);
    } else {
        ondisk = create_seafile_v0 (cdc, &ondisk_size, seafile_id);

        if (seaf_obj_store_write_obj (fs_mgr->obj_store, repo_id, version, seafile_id,
                                      ondisk, ondisk_size, FALSE) < 0)
            ret = -1;
        g_free (ondisk);
    }

out:
    if (ret == 0)
        hex_to_rawdata (seafile_id, obj_sha1, 20);

    return ret;
}