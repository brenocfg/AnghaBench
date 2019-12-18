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
 scalar_t__ isprint (char) ; 
 int /*<<< orphan*/  printf (char*,char) ; 

__attribute__((used)) static int
zil_prt_rec_write_cb(void *data, size_t len, void *unused)
{
	char *cdata = data;

	for (size_t i = 0; i < len; i++) {
		if (isprint(*cdata))
			(void) printf("%c ", *cdata);
		else
			(void) printf("%2X", *cdata);
		cdata++;
	}
	return (0);
}