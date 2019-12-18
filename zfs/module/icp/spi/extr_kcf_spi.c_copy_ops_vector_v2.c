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
typedef  int /*<<< orphan*/  crypto_ops_t ;

/* Variables and functions */
 int /*<<< orphan*/  KCF_SPI_COPY_OPS (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  co_mech_ops ; 

__attribute__((used)) static void
copy_ops_vector_v2(crypto_ops_t *src_ops, crypto_ops_t *dst_ops)
{
	KCF_SPI_COPY_OPS(src_ops, dst_ops, co_mech_ops);
}