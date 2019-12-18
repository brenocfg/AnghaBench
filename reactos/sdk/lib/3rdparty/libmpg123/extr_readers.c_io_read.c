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
struct reader_data {int flags; int (* r_read_handle ) (int /*<<< orphan*/ ,void*,size_t) ;int (* read ) (int /*<<< orphan*/ ,void*,size_t) ;int /*<<< orphan*/  filept; int /*<<< orphan*/  iohandle; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int READER_HANDLEIO ; 
 int stub1 (int /*<<< orphan*/ ,void*,size_t) ; 
 int stub2 (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static ssize_t io_read(struct reader_data *rdat, void *buf, size_t count)
{
	if(rdat->flags & READER_HANDLEIO)
	{
		if(rdat->r_read_handle != NULL)
		{
			return rdat->r_read_handle(rdat->iohandle, buf, count);
		}
		else return -1;
	}
	else
	return rdat->read(rdat->filept, buf, count);
}