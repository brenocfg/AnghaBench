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
typedef  int /*<<< orphan*/  repo_salt_bin ;

/* Variables and functions */
 int /*<<< orphan*/  GNUTLS_RND_RANDOM ; 
 int RAND_bytes (unsigned char*,int) ; 
 int gnutls_rnd (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  rawdata_to_hex (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 

int
seafile_generate_repo_salt (char *repo_salt)
{
    unsigned char repo_salt_bin[32];

#ifdef USE_GPL_CRYPTO
    int rc = gnutls_rnd (GNUTLS_RND_RANDOM, repo_salt_bin, sizeof(repo_salt_bin));
#else
    int rc = RAND_bytes (repo_salt_bin, sizeof(repo_salt_bin));
#endif
    if (rc != 1) {
        seaf_warning ("Failed to generate salt for repo encryption.\n");
        return -1;
    }

    rawdata_to_hex (repo_salt_bin, repo_salt, 32);

    return 0;
}