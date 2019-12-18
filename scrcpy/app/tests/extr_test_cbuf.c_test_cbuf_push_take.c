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
struct int_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cbuf_init (struct int_queue*) ; 
 int cbuf_push (struct int_queue*,int) ; 
 int cbuf_take (struct int_queue*,int*) ; 

__attribute__((used)) static void test_cbuf_push_take(void) {
    struct int_queue queue;
    cbuf_init(&queue);

    bool push1_ok = cbuf_push(&queue, 42);
    assert(push1_ok);

    bool push2_ok = cbuf_push(&queue, 35);
    assert(push2_ok);

    int item;

    bool take1_ok = cbuf_take(&queue, &item);
    assert(take1_ok);
    assert(item == 42);

    bool take2_ok = cbuf_take(&queue, &item);
    assert(take2_ok);
    assert(item == 35);
}