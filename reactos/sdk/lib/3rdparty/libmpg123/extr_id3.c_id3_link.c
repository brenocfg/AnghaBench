#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ fill; scalar_t__* p; } ;
struct TYPE_8__ {int /*<<< orphan*/  text; TYPE_1__ description; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ mpg123_text ;
struct TYPE_9__ {size_t texts; size_t comments; TYPE_2__* comment_list; int /*<<< orphan*/ * comment; int /*<<< orphan*/ * genre; int /*<<< orphan*/ * year; int /*<<< orphan*/ * artist; int /*<<< orphan*/ * album; int /*<<< orphan*/ * title; TYPE_2__* text; } ;
typedef  TYPE_3__ mpg123_id3v2 ;
struct TYPE_10__ {TYPE_3__ id3v2; } ;
typedef  TYPE_4__ mpg123_handle ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  null_id3_links (TYPE_4__*) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int) ; 

void id3_link(mpg123_handle *fr)
{
	size_t i;
	mpg123_id3v2 *v2 = &fr->id3v2;
	debug("linking ID3v2");
	null_id3_links(fr);
	for(i=0; i<v2->texts; ++i)
	{
		mpg123_text *entry = &v2->text[i];
		if     (!strncmp("TIT2", entry->id, 4)) v2->title  = &entry->text;
		else if(!strncmp("TALB", entry->id, 4)) v2->album  = &entry->text;
		else if(!strncmp("TPE1", entry->id, 4)) v2->artist = &entry->text;
		else if(!strncmp("TYER", entry->id, 4)) v2->year   = &entry->text;
		else if(!strncmp("TCON", entry->id, 4)) v2->genre  = &entry->text;
	}
	for(i=0; i<v2->comments; ++i)
	{
		mpg123_text *entry = &v2->comment_list[i];
		if(entry->description.fill == 0 || entry->description.p[0] == 0)
		v2->comment = &entry->text;
	}
	/* When no generic comment found, use the last non-generic one. */
	if(v2->comment == NULL && v2->comments > 0)
	v2->comment = &v2->comment_list[v2->comments-1].text;
}