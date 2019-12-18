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
typedef  char const siphash ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  siphash24_compress (char const*,int,char const*) ; 
 size_t strcspn (char const*,char*) ; 
 size_t strspn (char const*,char*) ; 

void path_hash_func(const char *q, struct siphash *state) {
        size_t n;

        assert(q);
        assert(state);

        /* Calculates a hash for a path in a way this duplicate inner slashes don't make a differences, and also
         * whether there's a trailing slash or not. This fits well with the semantics of path_compare(), which does
         * similar checks and also doesn't care for trailing slashes. Note that relative and absolute paths (i.e. those
         * which begin in a slash or not) will hash differently though. */

        n = strspn(q, "/");
        if (n > 0) { /* Eat up initial slashes, and add one "/" to the hash for all of them */
                siphash24_compress(q, 1, state);
                q += n;
        }

        for (;;) {
                /* Determine length of next component */
                n = strcspn(q, "/");
                if (n == 0) /* Reached the end? */
                        break;

                /* Add this component to the hash and skip over it */
                siphash24_compress(q, n, state);
                q += n;

                /* How many slashes follow this component? */
                n = strspn(q, "/");
                if (q[n] == 0) /* Is this a trailing slash? If so, we are at the end, and don't care about the slashes anymore */
                        break;

                /* We are not add the end yet. Hash exactly one slash for all of the ones we just encountered. */
                siphash24_compress(q, 1, state);
                q += n;
        }
}