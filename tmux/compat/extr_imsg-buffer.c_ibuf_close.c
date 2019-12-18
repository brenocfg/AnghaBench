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
struct msgbuf {int dummy; } ;
struct ibuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibuf_enqueue (struct msgbuf*,struct ibuf*) ; 

void
ibuf_close(struct msgbuf *msgbuf, struct ibuf *buf)
{
	ibuf_enqueue(msgbuf, buf);
}