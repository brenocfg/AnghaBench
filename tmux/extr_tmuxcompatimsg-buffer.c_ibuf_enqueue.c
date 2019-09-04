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
struct msgbuf {int /*<<< orphan*/  queued; int /*<<< orphan*/  bufs; } ;
struct ibuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ibuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 

__attribute__((used)) static void
ibuf_enqueue(struct msgbuf *msgbuf, struct ibuf *buf)
{
	TAILQ_INSERT_TAIL(&msgbuf->bufs, buf, entry);
	msgbuf->queued++;
}