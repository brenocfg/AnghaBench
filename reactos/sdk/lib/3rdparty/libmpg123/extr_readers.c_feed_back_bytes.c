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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ off_t ;
struct TYPE_5__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_6__ {TYPE_1__ rdat; } ;
typedef  TYPE_2__ mpg123_handle ;

/* Variables and functions */
 int READER_ERROR ; 
 scalar_t__ bc_seekback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ feed_skip_bytes (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static int feed_back_bytes(mpg123_handle *fr, off_t bytes)
{
	if(bytes >=0)
	return bc_seekback(&fr->rdat.buffer, (ssize_t)bytes) >= 0 ? 0 : READER_ERROR;
	else
	return feed_skip_bytes(fr, -bytes) >= 0 ? 0 : READER_ERROR;
}