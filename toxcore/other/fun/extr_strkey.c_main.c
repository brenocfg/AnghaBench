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

/* Variables and functions */
 int atoi (char*) ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int crypto_box_SECRETKEYBYTES ; 
 int /*<<< orphan*/  crypto_box_keypair (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  print_key (unsigned char*) ; 
 int /*<<< orphan*/  sscanf (char*,char*,unsigned char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 size_t strlen (char*) ; 

int main(int argc, char *argv[])
{
    unsigned char public_key[crypto_box_PUBLICKEYBYTES]; // null terminator
    unsigned char secret_key[crypto_box_SECRETKEYBYTES];
    int offset = 0;
    size_t len;
    unsigned char desired_bin[crypto_box_PUBLICKEYBYTES]; // null terminator

    if (argc == 3) {
        offset = atoi(argv[1]);
        char *desired_hex = argv[2];
        len = strlen(desired_hex);
        if (len % 2 != 0) {
            fprintf(stderr, "Desired key should have an even number of letters\n");
            exit(1);
        }
        size_t block_length = (offset < 0 ? 0 : offset) + len/2;
        if (block_length > crypto_box_PUBLICKEYBYTES) {
            fprintf(stderr, "The given key with the given offset exceed public key's length\n");
            exit(1);
        }

        // convert hex to bin
        char *pos = desired_hex;
        size_t i;
        for (i = 0; i < len; pos += 2) {
            sscanf(pos, "%2hhx", &desired_bin[i]);
            ++i;
        }
    } else {
        fprintf(stdout, "Usage: executable <byte offset> <desired hex string with even number of letters>\n");
        exit(1);
    }

    len /= 2;

#ifdef PRINT_TRIES_COUNT
    long long unsigned int tries = 0;
#endif

    if (offset < 0) {
        int found = 0;
        do {
#ifdef PRINT_TRIES_COUNT
            tries ++;
#endif
            crypto_box_keypair(public_key, secret_key);
            int i;
            for (i = 0; i <= crypto_box_PUBLICKEYBYTES - len; i ++) {
                if (memcmp(public_key + i, desired_bin, len) == 0) {
                    found = 1;
                    break;
                }
            }
        } while (!found);
    } else {
        unsigned char *p = public_key + offset;

        do {
#ifdef PRINT_TRIES_COUNT
	    tries ++;
#endif
            crypto_box_keypair(public_key, secret_key);
        } while (memcmp(p, desired_bin, len) != 0);
    }

    fprintf(stdout, "Public key:  ");
    print_key(public_key);
    fprintf(stdout, "\n");

    fprintf(stdout, "Private key: ");
    print_key(secret_key);
    fprintf(stdout, "\n");

#ifdef PRINT_TRIES_COUNT
	fprintf(stdout, "Found the key pair on %llu try.\n", tries);
#endif

    return 0;
}