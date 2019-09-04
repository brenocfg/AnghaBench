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
struct global_queue {int dummy; } ;

/* Variables and functions */
 struct global_queue* Q ; 
 int /*<<< orphan*/  SPIN_INIT (struct global_queue*) ; 
 int /*<<< orphan*/  memset (struct global_queue*,int /*<<< orphan*/ ,int) ; 
 struct global_queue* skynet_malloc (int) ; 

void 
skynet_mq_init() {
	struct global_queue *q = skynet_malloc(sizeof(*q));
	memset(q,0,sizeof(*q));
	SPIN_INIT(q);
	Q=q;
}