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
struct TYPE_2__ {char* msg; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHMC_NOERR ; 
 TYPE_1__ chmc_err ; 

void chmcerr_clean(void) {
	chmc_err.code = CHMC_NOERR;
	chmc_err.msg[0] = '\0';
}