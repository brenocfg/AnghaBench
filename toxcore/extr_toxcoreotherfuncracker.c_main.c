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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_scalarmult_curve25519_base (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* hex_string_to_bin (char*) ; 
 scalar_t__ memcmp (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,unsigned char*,int) ; 
 int /*<<< orphan*/  print_key (scalar_t__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  randombytes (scalar_t__*,int) ; 
 int strlen (char*) ; 

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: ./cracker public_key(or beginning of one in hex format)\n");
        return 0;
    }

    long long unsigned int num_tries = 0;

    uint32_t len = strlen(argv[1]) / 2;
    unsigned char *key = hex_string_to_bin(argv[1]);
    uint8_t pub_key[32], priv_key[32], c_key[32];

    if (len > 32)
        len = 32;

    memcpy(c_key, key, len);
    free(key);
    randombytes(priv_key, 32);

    while (1) {
        crypto_scalarmult_curve25519_base(pub_key, priv_key);
        uint32_t i;

        if (memcmp(c_key, pub_key, len) == 0)
            break;

        for (i = 32; i != 0; --i) {
            priv_key[i - 1] += 1;

            if (priv_key[i - 1] != 0)
                break;
        }

        ++num_tries;
    }

    printf("Public key:\n");
    print_key(pub_key);
    printf("\nPrivate key:\n");
    print_key(priv_key);
    printf("\n %llu keys tried\n", num_tries);
    return 0;
}