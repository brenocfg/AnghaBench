#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ pos; scalar_t__ fileoff; } ;
struct TYPE_5__ {TYPE_4__ buffer; scalar_t__ filepos; } ;
struct TYPE_6__ {TYPE_1__ rdat; } ;
typedef  TYPE_2__ mpg123_handle ;

/* Variables and functions */
 int /*<<< orphan*/  bc_forget (TYPE_4__*) ; 

__attribute__((used)) static void buffered_forget(mpg123_handle *fr)
{
	bc_forget(&fr->rdat.buffer);
	fr->rdat.filepos = fr->rdat.buffer.fileoff + fr->rdat.buffer.pos;
}