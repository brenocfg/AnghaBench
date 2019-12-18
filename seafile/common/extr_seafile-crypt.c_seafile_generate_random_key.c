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
typedef  int /*<<< orphan*/  secret_key ;
typedef  unsigned char SeafileCrypt ;

/* Variables and functions */
 int /*<<< orphan*/  GNUTLS_RND_RANDOM ; 
 int RAND_bytes (unsigned char*,int) ; 
 int /*<<< orphan*/  g_free (unsigned char*) ; 
 scalar_t__ gnutls_rnd (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  rawdata_to_hex (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 
 unsigned char* seafile_crypt_new (int,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  seafile_derive_key (char const*,int /*<<< orphan*/ ,int,char const*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  seafile_encrypt (char**,int*,char*,int,unsigned char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int
seafile_generate_random_key (const char *passwd,
                             int version,
                             const char *repo_salt,
                             char *random_key)
{
    SeafileCrypt *crypt;
    unsigned char secret_key[32], *rand_key;
    int outlen;
    unsigned char key[32], iv[16];

#ifdef USE_GPL_CRYPTO
    if (gnutls_rnd (GNUTLS_RND_RANDOM, secret_key, sizeof(secret_key)) < 0) {
        seaf_warning ("Failed to generate secret key for repo encryption.\n");
        return -1;
    }
#else
    if (RAND_bytes (secret_key, sizeof(secret_key)) != 1) {
        seaf_warning ("Failed to generate secret key for repo encryption.\n");
        return -1;
    }
#endif

    seafile_derive_key (passwd, strlen(passwd), version, repo_salt, key, iv);

    crypt = seafile_crypt_new (version, key, iv);

    seafile_encrypt ((char **)&rand_key, &outlen,
                     (char *)secret_key, sizeof(secret_key), crypt);

    rawdata_to_hex (rand_key, random_key, 48);

    g_free (crypt);
    g_free (rand_key);

    return 0;
}