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
 int /*<<< orphan*/  co_cipher_ops ; 
 int /*<<< orphan*/  co_control_ops ; 
 int /*<<< orphan*/  co_ctx_ops ; 
 int /*<<< orphan*/  co_digest_ops ; 
 int /*<<< orphan*/  co_dual_cipher_mac_ops ; 
 int /*<<< orphan*/  co_dual_ops ; 
 int /*<<< orphan*/  co_key_ops ; 
 int /*<<< orphan*/  co_mac_ops ; 
 int /*<<< orphan*/  co_object_ops ; 
 int /*<<< orphan*/  co_provider_ops ; 
 int /*<<< orphan*/  co_random_ops ; 
 int /*<<< orphan*/  co_session_ops ; 
 int /*<<< orphan*/  co_sign_ops ; 
 int /*<<< orphan*/  co_verify_ops ; 

__attribute__((used)) static void
copy_ops_vector_v1(crypto_ops_t *src_ops, crypto_ops_t *dst_ops)
{
	KCF_SPI_COPY_OPS(src_ops, dst_ops, co_control_ops);
	KCF_SPI_COPY_OPS(src_ops, dst_ops, co_digest_ops);
	KCF_SPI_COPY_OPS(src_ops, dst_ops, co_cipher_ops);
	KCF_SPI_COPY_OPS(src_ops, dst_ops, co_mac_ops);
	KCF_SPI_COPY_OPS(src_ops, dst_ops, co_sign_ops);
	KCF_SPI_COPY_OPS(src_ops, dst_ops, co_verify_ops);
	KCF_SPI_COPY_OPS(src_ops, dst_ops, co_dual_ops);
	KCF_SPI_COPY_OPS(src_ops, dst_ops, co_dual_cipher_mac_ops);
	KCF_SPI_COPY_OPS(src_ops, dst_ops, co_random_ops);
	KCF_SPI_COPY_OPS(src_ops, dst_ops, co_session_ops);
	KCF_SPI_COPY_OPS(src_ops, dst_ops, co_object_ops);
	KCF_SPI_COPY_OPS(src_ops, dst_ops, co_key_ops);
	KCF_SPI_COPY_OPS(src_ops, dst_ops, co_provider_ops);
	KCF_SPI_COPY_OPS(src_ops, dst_ops, co_ctx_ops);
}