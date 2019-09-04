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
struct JitterBuffer {struct JitterBuffer* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct JitterBuffer*) ; 
 int /*<<< orphan*/  jbuf_clear (struct JitterBuffer*) ; 

__attribute__((used)) static void jbuf_free(struct JitterBuffer *q)
{
    if (!q) return;

    jbuf_clear(q);
    free(q->queue);
    free(q);
}