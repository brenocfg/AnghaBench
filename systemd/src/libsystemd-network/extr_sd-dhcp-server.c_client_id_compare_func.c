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
struct TYPE_4__ {int /*<<< orphan*/  length; scalar_t__ data; } ;
typedef  TYPE_1__ DHCPClientId ;

/* Variables and functions */
 int CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int memcmp (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

int client_id_compare_func(const DHCPClientId *a, const DHCPClientId *b) {
        int r;

        assert(!a->length || a->data);
        assert(!b->length || b->data);

        r = CMP(a->length, b->length);
        if (r != 0)
                return r;

        return memcmp(a->data, b->data, a->length);
}