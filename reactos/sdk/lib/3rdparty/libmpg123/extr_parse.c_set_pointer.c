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
struct TYPE_3__ {scalar_t__ bitindex; scalar_t__ fsizeold; scalar_t__ bsbufold; scalar_t__ wordpointer; scalar_t__ ssize; scalar_t__ bsbuf; } ;
typedef  TYPE_1__ mpg123_handle ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,long) ; 

void set_pointer(mpg123_handle *fr, long backstep)
{
	fr->wordpointer = fr->bsbuf + fr->ssize - backstep;
	if (backstep)
	memcpy(fr->wordpointer,fr->bsbufold+fr->fsizeold-backstep,backstep);

	fr->bitindex = 0; 
}