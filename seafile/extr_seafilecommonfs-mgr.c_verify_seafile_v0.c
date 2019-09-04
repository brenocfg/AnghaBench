#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int gsize ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_2__ {int /*<<< orphan*/  block_ids; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ SeafileOndisk ;
typedef  int /*<<< orphan*/  GChecksum ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  G_CHECKSUM_SHA1 ; 
 scalar_t__ SEAF_METADATA_TYPE_FILE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_checksum_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_checksum_get_digest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * g_checksum_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_checksum_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rawdata_to_hex (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  seaf_warning (char*,...) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static gboolean
verify_seafile_v0 (const char *id, const void *data, int len, gboolean verify_id)
{
    const SeafileOndisk *ondisk = data;
    GChecksum *ctx;
    uint8_t sha1[20];
    gsize cs_len = 20;
    char check_id[41];

    if (len < sizeof(SeafileOndisk)) {
        seaf_warning ("[fs mgr] Corrupt seafile object %s.\n", id);
        return FALSE;
    }

    if (ntohl(ondisk->type) != SEAF_METADATA_TYPE_FILE) {
        seaf_warning ("[fd mgr] %s is not a file.\n", id);
        return FALSE;
    }

    int id_list_length = len - sizeof(SeafileOndisk);
    if (id_list_length % 20 != 0) {
        seaf_warning ("[fs mgr] Bad seafile id list length %d.\n", id_list_length);
        return FALSE;
    }

    if (!verify_id)
        return TRUE;

    ctx = g_checksum_new (G_CHECKSUM_SHA1);
    g_checksum_update (ctx, ondisk->block_ids, len - sizeof(SeafileOndisk));
    g_checksum_get_digest (ctx, sha1, &cs_len);
    g_checksum_free (ctx);

    rawdata_to_hex (sha1, check_id, 20);

    if (strcmp (check_id, id) == 0)
        return TRUE;
    else
        return FALSE;
}