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
typedef  int gsize ;
typedef  int /*<<< orphan*/  GChecksum ;

/* Variables and functions */
 int /*<<< orphan*/  G_CHECKSUM_SHA1 ; 
 int /*<<< orphan*/  g_checksum_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_checksum_get_digest (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 int /*<<< orphan*/ * g_checksum_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_checksum_update (int /*<<< orphan*/ *,void const*,unsigned long) ; 

__attribute__((used)) static void hash_sha1_file(const void *buf, unsigned long len,
                           const char *type, unsigned char *sha1)
{
    GChecksum *c;
    gsize cs_len = 20;

    /* Sha1.. */
    c = g_checksum_new (G_CHECKSUM_SHA1);
    g_checksum_update(c, buf, len);
    g_checksum_get_digest (c, sha1, &cs_len);
    g_checksum_free (c);
}