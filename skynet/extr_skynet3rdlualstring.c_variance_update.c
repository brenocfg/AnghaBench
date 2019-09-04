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
struct variance {double count; double mean; double m2; } ;

/* Variables and functions */

__attribute__((used)) static void
variance_update(struct variance *v, int newValue_) {
	double newValue = (double)newValue_;
	++v->count;
	double delta = newValue - v->mean;
	v->mean += delta / v->count;
	double delta2 = newValue - v->mean;
	v->m2 += delta * delta2;
}