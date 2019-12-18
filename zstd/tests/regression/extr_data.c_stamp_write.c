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
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  data_t ;
typedef  int /*<<< orphan*/  XXH64_canonical_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  XXH64_canonicalFromHash (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* cat3 (char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kStampName ; 
 int /*<<< orphan*/  stamp_hash (int /*<<< orphan*/  const* const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int
stamp_write(char const* dir, data_t const* const* data, int const data_err) {
    char* stamp = cat3(dir, "/", kStampName);
    FILE* stampfile = NULL;
    int err = EIO;

    if (stamp == NULL)
        return ENOMEM;

    if (data_err != 0) {
        err = data_err;
        goto out;
    }
    XXH64_canonical_t hash;

    XXH64_canonicalFromHash(&hash, stamp_hash(data));

    stampfile = fopen(stamp, "wb");
    if (stampfile == NULL)
        goto out;
    if (fwrite(&hash, sizeof(hash), 1, stampfile) != 1)
        goto out;
    err = 0;
    fprintf(stderr, "stamped new data cache\n");
out:
    if (err != 0)
        /* Ignore errors. */
        unlink(stamp);
    free(stamp);
    if (stampfile != NULL)
        fclose(stampfile);
    return err;
}