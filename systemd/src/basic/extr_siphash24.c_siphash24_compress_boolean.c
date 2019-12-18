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
 int /*<<< orphan*/  siphash24_compress (int*,int,struct siphash*) ; 

void siphash24_compress_boolean(bool in, struct siphash *state) {
        int i = in;

        siphash24_compress(&i, sizeof i, state);
}