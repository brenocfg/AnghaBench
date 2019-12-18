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
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  submit_bio (int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static inline void
vdev_submit_bio_impl(struct bio *bio)
{
#ifdef HAVE_1ARG_SUBMIT_BIO
	submit_bio(bio);
#else
	submit_bio(0, bio);
#endif
}