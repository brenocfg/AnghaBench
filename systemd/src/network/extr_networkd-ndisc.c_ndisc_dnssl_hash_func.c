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
typedef  int /*<<< orphan*/  NDiscDNSSL ;

/* Variables and functions */
 int /*<<< orphan*/  NDISC_DNSSL_DOMAIN (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  siphash24_compress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct siphash*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ndisc_dnssl_hash_func(const NDiscDNSSL *x, struct siphash *state) {
        siphash24_compress(NDISC_DNSSL_DOMAIN(x), strlen(NDISC_DNSSL_DOMAIN(x)), state);
}