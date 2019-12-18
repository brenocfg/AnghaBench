#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int gsize ;
typedef  scalar_t__ gboolean ;
struct TYPE_5__ {scalar_t__ disable_block_hash; } ;
struct TYPE_4__ {int len; char* block_buf; } ;
typedef  int /*<<< orphan*/  SeafileCrypt ;
typedef  int /*<<< orphan*/  GChecksum ;
typedef  TYPE_1__ CDCDescriptor ;

/* Variables and functions */
 int /*<<< orphan*/  G_CHECKSUM_SHA1 ; 
 int do_write_chunk (char const*,int,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  g_checksum_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_checksum_get_digest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * g_checksum_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_checksum_update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* gen_uuid () ; 
 TYPE_3__* seaf ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 
 int seafile_encrypt (char**,int*,char*,int,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 

int
seafile_write_chunk (const char *repo_id,
                     int version,
                     CDCDescriptor *chunk,
                     SeafileCrypt *crypt,
                     uint8_t *checksum,
                     gboolean write_data)
{
    GChecksum *ctx = g_checksum_new (G_CHECKSUM_SHA1);
    gsize len = 20;
    int ret = 0;

    /* Encrypt before write to disk if needed, and we don't encrypt
     * empty files. */
    if (crypt != NULL && chunk->len) {
        char *encrypted_buf = NULL;         /* encrypted output */
        int enc_len = -1;                /* encrypted length */

        ret = seafile_encrypt (&encrypted_buf, /* output */
                               &enc_len,      /* output len */
                               chunk->block_buf, /* input */
                               chunk->len,       /* input len */
                               crypt);
        if (ret != 0) {
            seaf_warning ("Error: failed to encrypt block\n");
            g_checksum_free (ctx);
            return -1;
        }

        if (seaf->disable_block_hash) {
            char *uuid = gen_uuid();
            g_checksum_update (ctx, (unsigned char *)uuid, strlen(uuid));
            g_free(uuid);
        } else {
            g_checksum_update (ctx, (unsigned char *)encrypted_buf, enc_len);
        }
        g_checksum_get_digest (ctx, checksum, &len);

        if (write_data)
            ret = do_write_chunk (repo_id, version, checksum, encrypted_buf, enc_len);
        g_free (encrypted_buf);
    } else {
        /* not a encrypted repo, go ahead */
        if (seaf->disable_block_hash) {
            char *uuid = gen_uuid();
            g_checksum_update (ctx, (unsigned char *)uuid, strlen(uuid));
            g_free(uuid);
        }
        else {
            g_checksum_update (ctx, (unsigned char *)chunk->block_buf, chunk->len);
        }
        g_checksum_get_digest (ctx, checksum, &len);

        if (write_data)
            ret = do_write_chunk (repo_id, version, checksum, chunk->block_buf, chunk->len);
    }

    g_checksum_free (ctx);

    return ret;
}