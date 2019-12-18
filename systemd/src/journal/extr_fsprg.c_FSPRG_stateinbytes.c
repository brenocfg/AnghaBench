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

/* Variables and functions */
 int /*<<< orphan*/  VALIDATE_SECPAR (unsigned int) ; 

size_t FSPRG_stateinbytes(unsigned _secpar) {
        VALIDATE_SECPAR(_secpar);
        return 2 + 2 * _secpar / 8 + 8; /* to store header,n,x,epoch */
}