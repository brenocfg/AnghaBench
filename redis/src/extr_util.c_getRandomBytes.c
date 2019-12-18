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
typedef  scalar_t__ uint64_t ;
struct timeval {long tv_sec; long tv_usec; } ;
typedef  int /*<<< orphan*/  seed ;
typedef  long pid_t ;
typedef  int /*<<< orphan*/  counter ;
typedef  int /*<<< orphan*/  SHA1_CTX ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 long getpid () ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,unsigned int) ; 

void getRandomBytes(unsigned char *p, size_t len) {
    /* Global state. */
    static int seed_initialized = 0;
    static unsigned char seed[20]; /* The SHA1 seed, from /dev/urandom. */
    static uint64_t counter = 0; /* The counter we hash with the seed. */

    if (!seed_initialized) {
        /* Initialize a seed and use SHA1 in counter mode, where we hash
         * the same seed with a progressive counter. For the goals of this
         * function we just need non-colliding strings, there are no
         * cryptographic security needs. */
        FILE *fp = fopen("/dev/urandom","r");
        if (fp == NULL || fread(seed,sizeof(seed),1,fp) != 1) {
            /* Revert to a weaker seed, and in this case reseed again
             * at every call.*/
            for (unsigned int j = 0; j < sizeof(seed); j++) {
                struct timeval tv;
                gettimeofday(&tv,NULL);
                pid_t pid = getpid();
                seed[j] = tv.tv_sec ^ tv.tv_usec ^ pid ^ (long)fp;
            }
        } else {
            seed_initialized = 1;
        }
        if (fp) fclose(fp);
    }

    while(len) {
        unsigned char digest[20];
        SHA1_CTX ctx;
        unsigned int copylen = len > 20 ? 20 : len;

        SHA1Init(&ctx);
        SHA1Update(&ctx, seed, sizeof(seed));
        SHA1Update(&ctx, (unsigned char*)&counter,sizeof(counter));
        SHA1Final(digest, &ctx);
        counter++;

        memcpy(p,digest,copylen);
        len -= copylen;
        p += copylen;
    }
}