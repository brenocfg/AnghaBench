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
typedef  unsigned char SeafileCrypt ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (unsigned char*) ; 
 int /*<<< orphan*/  hex_to_rawdata (char const*,unsigned char*,int) ; 
 int /*<<< orphan*/  rawdata_to_hex (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 
 unsigned char* seafile_crypt_new (int,unsigned char*,unsigned char*) ; 
 scalar_t__ seafile_decrypt (char**,int*,char*,int,unsigned char*) ; 
 int /*<<< orphan*/  seafile_derive_key (char const*,int /*<<< orphan*/ ,int,char const*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  seafile_encrypt (char**,int*,char*,int,unsigned char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int
seafile_update_random_key (const char *old_passwd, const char *old_random_key,
                           const char *new_passwd, char *new_random_key,
                           int enc_version, const char *repo_salt)
{
    unsigned char key[32], iv[16];
    unsigned char random_key_raw[48], *secret_key, *new_random_key_raw;
    int secret_key_len, random_key_len;
    SeafileCrypt *crypt;

    /* First, use old_passwd to decrypt secret key from old_random_key. */
    seafile_derive_key (old_passwd, strlen(old_passwd), enc_version,
                        repo_salt, key, iv);

    hex_to_rawdata (old_random_key, random_key_raw, 48);

    crypt = seafile_crypt_new (enc_version, key, iv);
    if (seafile_decrypt ((char **)&secret_key, &secret_key_len,
                         (char *)random_key_raw, 48,
                         crypt) < 0) {
        seaf_warning ("Failed to decrypt random key.\n");
        g_free (crypt);
        return -1;
    }
    g_free (crypt);

    /* Second, use new_passwd to encrypt secret key. */
    seafile_derive_key (new_passwd, strlen(new_passwd), enc_version,
                        repo_salt, key, iv);
    crypt = seafile_crypt_new (enc_version, key, iv);

    seafile_encrypt ((char **)&new_random_key_raw, &random_key_len,
                     (char *)secret_key, secret_key_len, crypt);

    rawdata_to_hex (new_random_key_raw, new_random_key, 48);

    g_free (secret_key);
    g_free (new_random_key_raw);
    g_free (crypt);

    return 0;
}