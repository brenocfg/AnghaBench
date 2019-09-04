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
typedef  int /*<<< orphan*/  guchar ;
typedef  int gsize ;
typedef  int /*<<< orphan*/  gint64 ;
typedef  int /*<<< orphan*/  ctime_n ;
struct TYPE_3__ {int /*<<< orphan*/  commit_id; int /*<<< orphan*/  ctime; scalar_t__ desc; scalar_t__ creator_name; scalar_t__ creator_id; scalar_t__ root_id; } ;
typedef  TYPE_1__ SeafCommit ;
typedef  int /*<<< orphan*/  GChecksum ;

/* Variables and functions */
 int /*<<< orphan*/  G_CHECKSUM_SHA1 ; 
 int /*<<< orphan*/  g_checksum_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_checksum_get_digest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * g_checksum_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_checksum_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hton64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rawdata_to_hex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int strlen (scalar_t__) ; 

__attribute__((used)) static void compute_commit_id (SeafCommit* commit)
{
    GChecksum *ctx = g_checksum_new(G_CHECKSUM_SHA1);
    uint8_t sha1[20];    
    gint64 ctime_n;

    g_checksum_update (ctx, (guchar *)commit->root_id, 41);
    g_checksum_update (ctx, (guchar *)commit->creator_id, 41);
    if (commit->creator_name)
        g_checksum_update (ctx, (guchar *)commit->creator_name, strlen(commit->creator_name)+1);
    g_checksum_update (ctx, (guchar *)commit->desc, strlen(commit->desc)+1);

    /* convert to network byte order */
    ctime_n = hton64 (commit->ctime);
    g_checksum_update (ctx, (guchar *)&ctime_n, sizeof(ctime_n));

    gsize len = 20;
    g_checksum_get_digest (ctx, sha1, &len);
    
    rawdata_to_hex (sha1, commit->commit_id, 20);
    g_checksum_free (ctx);
}