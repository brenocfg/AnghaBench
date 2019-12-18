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
typedef  int /*<<< orphan*/  data_t ;
typedef  int /*<<< orphan*/  actual ;
typedef  int /*<<< orphan*/  XXH64_canonical_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  UTIL_isRegularFile (char*) ; 
 scalar_t__ const XXH64_hashFromCanonical (int /*<<< orphan*/ *) ; 
 char* cat3 (char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 size_t fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  kStampName ; 
 scalar_t__ stamp_hash (int /*<<< orphan*/  const* const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int stamp_check(char const* dir, data_t const* const* data) {
    char* stamp = cat3(dir, "/", kStampName);
    uint64_t const expected = stamp_hash(data);
    XXH64_canonical_t actual;
    FILE* stampfile = NULL;
    int matches = 0;

    if (stamp == NULL)
        goto out;
    if (!UTIL_isRegularFile(stamp)) {
        fprintf(stderr, "stamp does not exist: recreating the data cache\n");
        goto out;
    }

    stampfile = fopen(stamp, "rb");
    if (stampfile == NULL) {
        fprintf(stderr, "could not open stamp: recreating the data cache\n");
        goto out;
    }

    size_t b;
    if ((b = fread(&actual, sizeof(actual), 1, stampfile)) != 1) {
        fprintf(stderr, "invalid stamp: recreating the data cache\n");
        goto out;
    }

    matches = (expected == XXH64_hashFromCanonical(&actual));
    if (matches)
        fprintf(stderr, "stamp matches: reusing the cached data\n");
    else
        fprintf(stderr, "stamp does not match: recreating the data cache\n");

out:
    free(stamp);
    if (stampfile != NULL)
        fclose(stampfile);
    return matches;
}