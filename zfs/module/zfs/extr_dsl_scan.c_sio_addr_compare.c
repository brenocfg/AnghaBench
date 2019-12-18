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
typedef  int /*<<< orphan*/  scan_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIO_GET_OFFSET (int /*<<< orphan*/  const*) ; 
 int TREE_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sio_addr_compare(const void *x, const void *y)
{
	const scan_io_t *a = x, *b = y;

	return (TREE_CMP(SIO_GET_OFFSET(a), SIO_GET_OFFSET(b)));
}