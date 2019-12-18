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
struct siphash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_LABEL_MAX ; 
 int /*<<< orphan*/  ascii_strlower_n (char*,int) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int dns_label_unescape (char const**,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siphash24_compress (char*,int,struct siphash*) ; 
 int /*<<< orphan*/  siphash24_compress_byte (int /*<<< orphan*/ ,struct siphash*) ; 
 int /*<<< orphan*/  string_hash_func (char*,struct siphash*) ; 

void dns_name_hash_func(const char *p, struct siphash *state) {
        int r;

        assert(p);

        for (;;) {
                char label[DNS_LABEL_MAX+1];

                r = dns_label_unescape(&p, label, sizeof label, 0);
                if (r < 0)
                        break;
                if (r == 0)
                        break;

                ascii_strlower_n(label, r);
                siphash24_compress(label, r, state);
                siphash24_compress_byte(0, state); /* make sure foobar and foo.bar result in different hashes */
        }

        /* enforce that all names are terminated by the empty label */
        string_hash_func("", state);
}