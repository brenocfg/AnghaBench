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
struct ttyfd {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int read (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int
ttyread(struct ttyfd *tf)
{
	unsigned char rb;

	if (read(tf->fd, &rb, 1) == 1)
		return (rb);
	else
		return (-1);
}