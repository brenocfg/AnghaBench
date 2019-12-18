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
typedef  int /*<<< orphan*/  sd_id128_t ;

/* Variables and functions */
 int /*<<< orphan*/  siphash24_compress (int /*<<< orphan*/  const*,int,struct siphash*) ; 

void id128_hash_func(const sd_id128_t *p, struct siphash *state) {
        siphash24_compress(p, sizeof(sd_id128_t), state);
}