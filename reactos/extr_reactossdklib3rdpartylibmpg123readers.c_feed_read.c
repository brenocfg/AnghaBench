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
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_5__ {TYPE_1__ rdat; } ;
typedef  TYPE_2__ mpg123_handle ;

/* Variables and functions */
 scalar_t__ READER_ERROR ; 
 scalar_t__ bc_give (int /*<<< orphan*/ *,unsigned char*,scalar_t__) ; 

__attribute__((used)) static ssize_t feed_read(mpg123_handle *fr, unsigned char *out, ssize_t count)
{
	ssize_t gotcount = bc_give(&fr->rdat.buffer, out, count);
	if(gotcount >= 0 && gotcount != count) return READER_ERROR;
	else return gotcount;
}