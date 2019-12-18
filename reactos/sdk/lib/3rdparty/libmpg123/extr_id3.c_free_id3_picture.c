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
typedef  int /*<<< orphan*/  mpg123_picture ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_mpg123_picture (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_id3_picture(mpg123_picture **list, size_t *size)
{
	size_t i;
	for(i=0; i<*size; ++i) free_mpg123_picture(&((*list)[i]));

	free(*list);
	*list = NULL;
	*size = 0;
}