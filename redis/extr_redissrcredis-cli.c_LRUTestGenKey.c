#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lru_test_sample_size; } ;

/* Variables and functions */
 TYPE_1__ config ; 
 int /*<<< orphan*/  powerLawRand (int,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int /*<<< orphan*/ ) ; 

void LRUTestGenKey(char *buf, size_t buflen) {
    snprintf(buf, buflen, "lru:%lld",
        powerLawRand(1, config.lru_test_sample_size, 6.2));
}