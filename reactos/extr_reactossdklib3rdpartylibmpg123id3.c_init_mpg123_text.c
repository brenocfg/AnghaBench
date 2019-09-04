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
struct TYPE_3__ {scalar_t__* lang; scalar_t__* id; int /*<<< orphan*/  description; int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ mpg123_text ;

/* Variables and functions */
 int /*<<< orphan*/  mpg123_init_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_mpg123_text(mpg123_text *txt)
{
	mpg123_init_string(&txt->text);
	mpg123_init_string(&txt->description);
	txt->id[0] = 0;
	txt->id[1] = 0;
	txt->id[2] = 0;
	txt->id[3] = 0;
	txt->lang[0] = 0;
	txt->lang[1] = 0;
	txt->lang[2] = 0;
}