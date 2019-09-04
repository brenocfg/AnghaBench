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
struct swaynag_instance {int /*<<< orphan*/ * fd; int /*<<< orphan*/ * client; scalar_t__ detailed; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 

void swaynag_show(struct swaynag_instance *swaynag) {
	if (swaynag->detailed && swaynag->client != NULL) {
		close(swaynag->fd[1]);
	}
}