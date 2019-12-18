#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ halfspeed; } ;
struct TYPE_5__ {int lay; int /*<<< orphan*/  ssize; int /*<<< orphan*/  bsbuf; int /*<<< orphan*/  ssave; TYPE_1__ p; } ;
typedef  TYPE_2__ mpg123_handle ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void halfspeed_prepare(mpg123_handle *fr)
{
	/* save for repetition */
	if(fr->p.halfspeed && fr->lay == 3)
	{
		debug("halfspeed - reusing old bsbuf ");
		memcpy (fr->ssave, fr->bsbuf, fr->ssize);
	}
}