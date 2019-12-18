#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct reader_data {int flags; int (* r_lseek_handle ) (int /*<<< orphan*/ ,int,int) ;int (* lseek ) (int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  filept; int /*<<< orphan*/  iohandle; } ;
typedef  int off_t ;

/* Variables and functions */
 int READER_HANDLEIO ; 
 int stub1 (int /*<<< orphan*/ ,int,int) ; 
 int stub2 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static off_t io_seek(struct reader_data *rdat, off_t offset, int whence)
{
	if(rdat->flags & READER_HANDLEIO)
	{
		if(rdat->r_lseek_handle != NULL)
		{
			return rdat->r_lseek_handle(rdat->iohandle, offset, whence);
		}
		else return -1;
	}
	else
	return rdat->lseek(rdat->filept, offset, whence);
}