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
struct TYPE_3__ {int /*<<< orphan*/  description; int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ mpg123_text ;

/* Variables and functions */
 int /*<<< orphan*/  mpg123_free_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_mpg123_text(mpg123_text *txt)
{
	mpg123_free_string(&txt->text);
	mpg123_free_string(&txt->description);
}