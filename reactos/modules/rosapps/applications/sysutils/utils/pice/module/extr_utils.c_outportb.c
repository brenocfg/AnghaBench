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
typedef  int /*<<< orphan*/  UCHAR ;
typedef  scalar_t__ PUCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_PORT_UCHAR (scalar_t__,int /*<<< orphan*/ ) ; 

void outportb(PUCHAR port,UCHAR data)
{
    WRITE_PORT_UCHAR((PUCHAR)port, data);
}