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
 int /*<<< orphan*/  init_mpg123_picture (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * safe_realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static mpg123_picture *add_id3_picture(mpg123_picture **list, size_t *size)
{
	mpg123_picture *x = safe_realloc(*list, sizeof(mpg123_picture)*(*size+1));
	if(x == NULL) return NULL; /* bad */

	*list  = x;
	*size += 1;
	init_mpg123_picture(&((*list)[*size-1]));

	return &((*list)[*size-1]); /* Return pointer to the added picture. */
}