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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  Bookmark ;

/* Variables and functions */
 int /*<<< orphan*/ * FGets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ParseHostLine (char*,int /*<<< orphan*/ *) ; 

int
GetNextBookmark(FILE *fp, Bookmark *bmp)
{
	char line[512];

	while (FGets(line, sizeof(line), fp) != NULL) {
		if (ParseHostLine(line, bmp) >= 0)
			return (0);
	}
	return (-1);
}