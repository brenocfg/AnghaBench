#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  description; int /*<<< orphan*/  mime_type; } ;
typedef  TYPE_1__ mpg123_picture ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpg123_free_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_mpg123_picture(mpg123_picture * pic)
{
	mpg123_free_string(&pic->mime_type);
	mpg123_free_string(&pic->description);
	if (pic->data != NULL)
		free(pic->data);
}