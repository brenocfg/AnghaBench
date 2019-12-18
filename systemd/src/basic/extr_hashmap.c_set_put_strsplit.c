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
typedef  char const Set ;
typedef  int /*<<< orphan*/  ExtractFlags ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int extract_first_word (char const**,char**,char const*,int /*<<< orphan*/ ) ; 
 int set_consume (char const*,char*) ; 

int set_put_strsplit(Set *s, const char *v, const char *separators, ExtractFlags flags) {
        const char *p = v;
        int r;

        assert(s);
        assert(v);

        for (;;) {
                char *word;

                r = extract_first_word(&p, &word, separators, flags);
                if (r <= 0)
                        return r;

                r = set_consume(s, word);
                if (r < 0)
                        return r;
        }
}