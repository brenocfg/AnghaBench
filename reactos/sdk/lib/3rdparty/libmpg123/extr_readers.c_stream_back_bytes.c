#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ off_t ;
struct TYPE_7__ {TYPE_1__* rd; } ;
typedef  TYPE_2__ mpg123_handle ;
struct TYPE_6__ {scalar_t__ (* tell ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int READER_ERROR ; 
 scalar_t__ stream_skip_bytes (TYPE_2__*,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 

__attribute__((used)) static int stream_back_bytes(mpg123_handle *fr, off_t bytes)
{
	off_t want = fr->rd->tell(fr)-bytes;
	if(want < 0) return READER_ERROR;
	if(stream_skip_bytes(fr,-bytes) != want) return READER_ERROR;

	return 0;
}