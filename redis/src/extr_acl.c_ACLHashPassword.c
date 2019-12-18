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
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  SHA256_CTX ;

/* Variables and functions */
 int HASH_PASSWORD_LEN ; 
 int SHA256_BLOCK_SIZE ; 
 int /*<<< orphan*/  sdsnewlen (char*,int) ; 
 int /*<<< orphan*/  sha256_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  sha256_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha256_update (int /*<<< orphan*/ *,unsigned char*,size_t) ; 

sds ACLHashPassword(unsigned char *cleartext, size_t len) {
    SHA256_CTX ctx;
    unsigned char hash[SHA256_BLOCK_SIZE];
    char hex[HASH_PASSWORD_LEN];
    char *cset = "0123456789abcdef";

    sha256_init(&ctx);
    sha256_update(&ctx,(unsigned char*)cleartext,len);
    sha256_final(&ctx,hash);

    for (int j = 0; j < SHA256_BLOCK_SIZE; j++) {
        hex[j*2] = cset[((hash[j]&0xF0)>>4)];
        hex[j*2+1] = cset[(hash[j]&0xF)];
    }
    return sdsnewlen(hex,HASH_PASSWORD_LEN);
}