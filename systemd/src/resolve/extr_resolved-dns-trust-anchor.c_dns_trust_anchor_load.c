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
typedef  int /*<<< orphan*/  DnsTrustAnchor ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int dns_trust_anchor_add_builtin_negative (int /*<<< orphan*/ *) ; 
 int dns_trust_anchor_add_builtin_positive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dns_trust_anchor_dump (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dns_trust_anchor_load_files (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_trust_anchor_load_negative ; 
 int /*<<< orphan*/  dns_trust_anchor_load_positive ; 
 int log_error_errno (int,char*) ; 

int dns_trust_anchor_load(DnsTrustAnchor *d) {
        int r;

        assert(d);

        /* If loading things from disk fails, we don't consider this fatal */
        (void) dns_trust_anchor_load_files(d, ".positive", dns_trust_anchor_load_positive);
        (void) dns_trust_anchor_load_files(d, ".negative", dns_trust_anchor_load_negative);

        /* However, if the built-in DS fails, then we have a problem. */
        r = dns_trust_anchor_add_builtin_positive(d);
        if (r < 0)
                return log_error_errno(r, "Failed to add built-in positive trust anchor: %m");

        r = dns_trust_anchor_add_builtin_negative(d);
        if (r < 0)
                return log_error_errno(r, "Failed to add built-in negative trust anchor: %m");

        dns_trust_anchor_dump(d);

        return 0;
}