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
 int /*<<< orphan*/  F_ULOCK ; 
 int /*<<< orphan*/  lockf (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unlockfp(int *fd_lock) {
        if (*fd_lock < 0)
                return;
        lockf(*fd_lock, F_ULOCK, 0);
        *fd_lock = -1;
}