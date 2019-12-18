#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ GString ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ g_strcmp0 (char*,char const*) ; 
 int /*<<< orphan*/  g_string_append_printf (TYPE_1__*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  g_string_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* g_string_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rawdata_to_hex (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  seaf_warning (char*,int) ; 
 int /*<<< orphan*/  seafile_derive_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*,unsigned char*,unsigned char*) ; 

int
seafile_verify_repo_passwd (const char *repo_id,
                            const char *passwd,
                            const char *magic,
                            int version,
                            const char *repo_salt)
{
    GString *buf = g_string_new (NULL);
    unsigned char key[32], iv[16];
    char hex[65];

    if (version != 1 && version != 2 && version != 3) {
        seaf_warning ("Unsupported enc_version %d.\n", version);
        return -1;
    }

    /* Recompute the magic and compare it with the one comes with the repo. */
    g_string_append_printf (buf, "%s%s", repo_id, passwd);

    seafile_derive_key (buf->str, buf->len, version, repo_salt, key, iv);

    g_string_free (buf, TRUE);

    if (version >= 2)
        rawdata_to_hex (key, hex, 32);
    else
        rawdata_to_hex (key, hex, 16);

    if (g_strcmp0 (hex, magic) == 0)
        return 0;
    else
        return -1;
}