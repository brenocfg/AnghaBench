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
 int /*<<< orphan*/  free_comment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_extra (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_picture (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_text (int /*<<< orphan*/ *) ; 

void exit_id3(mpg123_handle *fr)
{
	free_picture(fr);
	free_comment(fr);
	free_extra(fr);
	free_text(fr);
}