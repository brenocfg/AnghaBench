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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_sign_ed25519 (char*,unsigned long long*,char*,int,unsigned char*) ; 
 int crypto_sign_ed25519_BYTES ; 
 int crypto_sign_ed25519_PUBLICKEYBYTES ; 
 int crypto_sign_ed25519_SECRETKEYBYTES ; 
 int /*<<< orphan*/  crypto_sign_ed25519_keypair (unsigned char*,unsigned char*) ; 
 int crypto_sign_ed25519_open (char*,unsigned long long*,char*,int,unsigned char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned long long fwrite (char*,int,unsigned long long,int /*<<< orphan*/ *) ; 
 unsigned char* hex_string_to_bin (char*) ; 
 int load_file (char*,char**) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(int argc, char *argv[])
{
    unsigned char pk[crypto_sign_ed25519_PUBLICKEYBYTES];
    unsigned char sk[crypto_sign_ed25519_SECRETKEYBYTES];

    if (argc == 2 && argv[1][0] == 'g') {
        crypto_sign_ed25519_keypair(pk, sk);
        printf("Public key:\n");
        int i;

        for (i = 0; i < crypto_sign_ed25519_PUBLICKEYBYTES; i++) {
            printf("%02hhX", pk[i]);
        }

        printf("\nSecret key:\n");

        for (i = 0; i < crypto_sign_ed25519_SECRETKEYBYTES; i++) {
            printf("%02hhX", sk[i]);
        }

        printf("\n");
    }

    if (argc == 5 && argv[1][0] == 's') {
        unsigned char *secret_key = hex_string_to_bin(argv[2]);
        char *data;
        int size = load_file(argv[3], &data);

        if (size < 0)
            goto fail;

        unsigned long long smlen;
        char *sm = malloc(size + crypto_sign_ed25519_BYTES * 2);
        crypto_sign_ed25519(sm, &smlen, data, size, secret_key);
        free(secret_key);

        if (smlen - size != crypto_sign_ed25519_BYTES)
            goto fail;

        FILE *f = fopen(argv[4], "wb");

        if (f == NULL)
            goto fail;

        memcpy(sm + smlen, sm, crypto_sign_ed25519_BYTES); // Move signature from beginning to end of file.

        if (fwrite(sm + (smlen - size), 1, smlen, f) != smlen)
            goto fail;

        fclose(f);
        printf("Signed successfully.\n");
    }

    if (argc == 4 && argv[1][0] == 'c') {
        unsigned char *public_key = hex_string_to_bin(argv[2]);
        char *data;
        int size = load_file(argv[3], &data);

        if (size < 0)
            goto fail;

        char *signe = malloc(size + crypto_sign_ed25519_BYTES);
        memcpy(signe, data + size - crypto_sign_ed25519_BYTES,
               crypto_sign_ed25519_BYTES); // Move signature from end to beginning of file.
        memcpy(signe + crypto_sign_ed25519_BYTES, data, size - crypto_sign_ed25519_BYTES);
        unsigned long long smlen;
        char *m = malloc(size);
        unsigned long long mlen;

        if (crypto_sign_ed25519_open(m, &mlen, signe, size, public_key) == -1) {
            printf("Failed checking sig.\n");
            goto fail;
        }

        printf("Checked successfully.\n");
    }

    return 0;

fail:
    printf("FAIL\n");
    return 1;
}