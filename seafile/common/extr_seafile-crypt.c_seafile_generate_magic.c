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
 int /*<<< orphan*/  g_string_append_printf (TYPE_1__*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  g_string_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* g_string_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rawdata_to_hex (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  seafile_derive_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*,unsigned char*,unsigned char*) ; 

void
seafile_generate_magic (int version, const char *repo_id,
                        const char *passwd,
                        const char *repo_salt,
                        char *magic)
{
    GString *buf = g_string_new (NULL);
    unsigned char key[32], iv[16];

    /* Compute a "magic" string from repo_id and passwd.
     * This is used to verify the password given by user before decrypting
     * data.
     */
    g_string_append_printf (buf, "%s%s", repo_id, passwd);

    seafile_derive_key (buf->str, buf->len, version, repo_salt, key, iv);

    g_string_free (buf, TRUE);
    rawdata_to_hex (key, magic, 32);
}