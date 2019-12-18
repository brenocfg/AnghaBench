#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int n_keys; int /*<<< orphan*/ * keys; } ;
typedef  TYPE_1__ DnsQuestion ;

/* Variables and functions */
 char const* dns_resource_key_name (int /*<<< orphan*/ ) ; 

const char *dns_question_first_name(DnsQuestion *q) {

        if (!q)
                return NULL;

        if (q->n_keys < 1)
                return NULL;

        return dns_resource_key_name(q->keys[0]);
}