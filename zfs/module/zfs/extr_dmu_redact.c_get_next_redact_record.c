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
struct redact_record {int dummy; } ;
typedef  int /*<<< orphan*/  bqueue_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 struct redact_record* bqueue_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (struct redact_record*,int) ; 
 int /*<<< orphan*/  redact_record_before (struct redact_record*,struct redact_record*) ; 

__attribute__((used)) static struct redact_record *
get_next_redact_record(bqueue_t *bq, struct redact_record *prev)
{
	struct redact_record *next = bqueue_dequeue(bq);
	ASSERT(redact_record_before(prev, next));
	kmem_free(prev, sizeof (*prev));
	return (next);
}