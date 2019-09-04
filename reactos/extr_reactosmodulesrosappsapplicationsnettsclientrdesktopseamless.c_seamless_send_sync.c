#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  seamless_rdp; } ;
typedef  TYPE_1__ RDPCLIENT ;

/* Variables and functions */
 unsigned int seamless_send (TYPE_1__*,char*,char*) ; 

unsigned int
seamless_send_sync(RDPCLIENT * This)
{
	if (!This->seamless_rdp)
		return (unsigned int) -1;

	return seamless_send(This, "SYNC", "");
}