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
typedef  int /*<<< orphan*/  mpg123_handle ;

/* Variables and functions */
 scalar_t__ NOQUIET ; 
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static int check_balloc(mpg123_handle *fr, unsigned int *balloc, unsigned int *end)
{
	unsigned int *ba;
	for(ba=balloc; ba != end; ++ba)
	if(*ba == 15)
	{
		if(NOQUIET) error("Illegal bit allocation value.");
		return -1;
	}

	return 0;
}