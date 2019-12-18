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
struct TYPE_4__ {int /*<<< orphan*/ * comment; int /*<<< orphan*/ * genre; int /*<<< orphan*/ * year; int /*<<< orphan*/ * album; int /*<<< orphan*/ * artist; int /*<<< orphan*/ * title; } ;
struct TYPE_5__ {TYPE_1__ id3v2; } ;
typedef  TYPE_2__ mpg123_handle ;

/* Variables and functions */

__attribute__((used)) static void null_id3_links(mpg123_handle *fr)
{
	fr->id3v2.title  = NULL;
	fr->id3v2.artist = NULL;
	fr->id3v2.album  = NULL;
	fr->id3v2.year   = NULL;
	fr->id3v2.genre  = NULL;
	fr->id3v2.comment = NULL;
}