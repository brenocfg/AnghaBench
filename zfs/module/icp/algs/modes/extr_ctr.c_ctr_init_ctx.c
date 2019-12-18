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
typedef  int ulong_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned long long uint64_t ;
typedef  int /*<<< orphan*/  uchar_t ;
struct TYPE_3__ {int /*<<< orphan*/  ctr_flags; int /*<<< orphan*/ * ctr_cb; int /*<<< orphan*/ * ctr_lastp; void* ctr_upper_mask; void* ctr_lower_mask; } ;
typedef  TYPE_1__ ctr_ctx_t ;

/* Variables and functions */
 int CRYPTO_MECHANISM_PARAM_INVALID ; 
 int CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  CTR_MODE ; 
 unsigned long long UINT64_MAX ; 
 void* htonll (unsigned long long) ; 

int
ctr_init_ctx(ctr_ctx_t *ctr_ctx, ulong_t count, uint8_t *cb,
    void (*copy_block)(uint8_t *, uint8_t *))
{
	uint64_t upper_mask = 0;
	uint64_t lower_mask = 0;

	if (count == 0 || count > 128) {
		return (CRYPTO_MECHANISM_PARAM_INVALID);
	}
	/* upper 64 bits of the mask */
	if (count >= 64) {
		count -= 64;
		upper_mask = (count == 64) ? UINT64_MAX : (1ULL << count) - 1;
		lower_mask = UINT64_MAX;
	} else {
		/* now the lower 63 bits */
		lower_mask = (1ULL << count) - 1;
	}
	ctr_ctx->ctr_lower_mask = htonll(lower_mask);
	ctr_ctx->ctr_upper_mask = htonll(upper_mask);

	copy_block(cb, (uchar_t *)ctr_ctx->ctr_cb);
	ctr_ctx->ctr_lastp = (uint8_t *)&ctr_ctx->ctr_cb[0];
	ctr_ctx->ctr_flags |= CTR_MODE;
	return (CRYPTO_SUCCESS);
}