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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int random_fd ; 
 int /*<<< orphan*/  random_path ; 
 int urandom_fd ; 
 int /*<<< orphan*/  urandom_path ; 

void
random_init(void)
{
	VERIFY((random_fd = open(random_path, O_RDONLY)) != -1);
	VERIFY((urandom_fd = open(urandom_path, O_RDONLY)) != -1);
}