#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {size_t fsprg_seed_size; unsigned long long fss_start_usec; unsigned long long fss_interval_usec; scalar_t__* fsprg_seed; } ;
typedef  TYPE_1__ JournalFile ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 size_t FSPRG_RECOMMENDED_SEEDLEN ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__* malloc (size_t) ; 
 int sscanf (char const*,char*,unsigned long long*,unsigned long long*) ; 
 int unhexchar (char const) ; 

int journal_file_parse_verification_key(JournalFile *f, const char *key) {
        uint8_t *seed;
        size_t seed_size, c;
        const char *k;
        int r;
        unsigned long long start, interval;

        seed_size = FSPRG_RECOMMENDED_SEEDLEN;
        seed = malloc(seed_size);
        if (!seed)
                return -ENOMEM;

        k = key;
        for (c = 0; c < seed_size; c++) {
                int x, y;

                while (*k == '-')
                        k++;

                x = unhexchar(*k);
                if (x < 0) {
                        free(seed);
                        return -EINVAL;
                }
                k++;
                y = unhexchar(*k);
                if (y < 0) {
                        free(seed);
                        return -EINVAL;
                }
                k++;

                seed[c] = (uint8_t) (x * 16 + y);
        }

        if (*k != '/') {
                free(seed);
                return -EINVAL;
        }
        k++;

        r = sscanf(k, "%llx-%llx", &start, &interval);
        if (r != 2) {
                free(seed);
                return -EINVAL;
        }

        f->fsprg_seed = seed;
        f->fsprg_seed_size = seed_size;

        f->fss_start_usec = start * interval;
        f->fss_interval_usec = interval;

        return 0;
}