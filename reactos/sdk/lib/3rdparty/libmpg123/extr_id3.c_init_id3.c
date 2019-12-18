#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * picture; scalar_t__ pictures; int /*<<< orphan*/ * extra; scalar_t__ extras; int /*<<< orphan*/ * text; scalar_t__ texts; int /*<<< orphan*/ * comment_list; scalar_t__ comments; scalar_t__ version; } ;
struct TYPE_6__ {TYPE_1__ id3v2; } ;
typedef  TYPE_2__ mpg123_handle ;

/* Variables and functions */
 int /*<<< orphan*/  null_id3_links (TYPE_2__*) ; 

void init_id3(mpg123_handle *fr)
{
	fr->id3v2.version = 0; /* nothing there */
	null_id3_links(fr);
	fr->id3v2.comments     = 0;
	fr->id3v2.comment_list = NULL;
	fr->id3v2.texts    = 0;
	fr->id3v2.text     = NULL;
	fr->id3v2.extras   = 0;
	fr->id3v2.extra    = NULL;
	fr->id3v2.pictures   = 0;
	fr->id3v2.picture    = NULL;
}