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
struct TYPE_4__ {int /*<<< orphan*/ * co_nostore_key_ops; } ;
typedef  TYPE_1__ crypto_ops_t ;
typedef  int /*<<< orphan*/  crypto_nostore_key_ops_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/ * kmem_alloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
allocate_ops_v3(crypto_ops_t *src, crypto_ops_t *dst)
{
	if (src->co_nostore_key_ops != NULL)
		dst->co_nostore_key_ops =
		    kmem_alloc(sizeof (crypto_nostore_key_ops_t), KM_SLEEP);
}