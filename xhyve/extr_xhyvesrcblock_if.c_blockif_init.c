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
 int /*<<< orphan*/  EVF_SIGNAL ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  blockif_sigcont_handler ; 
 int /*<<< orphan*/  mevent_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
blockif_init(void)
{
	mevent_add(SIGCONT, EVF_SIGNAL, blockif_sigcont_handler, NULL);
	(void) signal(SIGCONT, SIG_IGN);
}