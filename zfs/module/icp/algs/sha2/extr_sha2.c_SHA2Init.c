#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__* c64; } ;
struct TYPE_5__ {int* s32; int* s64; } ;
struct TYPE_7__ {TYPE_2__ count; scalar_t__ algotype; TYPE_1__ state; } ;
typedef  TYPE_3__ SHA2_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CE_PANIC ; 
#define  SHA256_HMAC_GEN_MECH_INFO_TYPE 138 
#define  SHA256_HMAC_MECH_INFO_TYPE 137 
#define  SHA256_MECH_INFO_TYPE 136 
#define  SHA384_HMAC_GEN_MECH_INFO_TYPE 135 
#define  SHA384_HMAC_MECH_INFO_TYPE 134 
#define  SHA384_MECH_INFO_TYPE 133 
#define  SHA512_224_MECH_INFO_TYPE 132 
#define  SHA512_256_MECH_INFO_TYPE 131 
#define  SHA512_HMAC_GEN_MECH_INFO_TYPE 130 
#define  SHA512_HMAC_MECH_INFO_TYPE 129 
#define  SHA512_MECH_INFO_TYPE 128 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 

void
SHA2Init(uint64_t mech, SHA2_CTX *ctx)
{

	switch (mech) {
	case SHA256_MECH_INFO_TYPE:
	case SHA256_HMAC_MECH_INFO_TYPE:
	case SHA256_HMAC_GEN_MECH_INFO_TYPE:
		ctx->state.s32[0] = 0x6a09e667U;
		ctx->state.s32[1] = 0xbb67ae85U;
		ctx->state.s32[2] = 0x3c6ef372U;
		ctx->state.s32[3] = 0xa54ff53aU;
		ctx->state.s32[4] = 0x510e527fU;
		ctx->state.s32[5] = 0x9b05688cU;
		ctx->state.s32[6] = 0x1f83d9abU;
		ctx->state.s32[7] = 0x5be0cd19U;
		break;
	case SHA384_MECH_INFO_TYPE:
	case SHA384_HMAC_MECH_INFO_TYPE:
	case SHA384_HMAC_GEN_MECH_INFO_TYPE:
		ctx->state.s64[0] = 0xcbbb9d5dc1059ed8ULL;
		ctx->state.s64[1] = 0x629a292a367cd507ULL;
		ctx->state.s64[2] = 0x9159015a3070dd17ULL;
		ctx->state.s64[3] = 0x152fecd8f70e5939ULL;
		ctx->state.s64[4] = 0x67332667ffc00b31ULL;
		ctx->state.s64[5] = 0x8eb44a8768581511ULL;
		ctx->state.s64[6] = 0xdb0c2e0d64f98fa7ULL;
		ctx->state.s64[7] = 0x47b5481dbefa4fa4ULL;
		break;
	case SHA512_MECH_INFO_TYPE:
	case SHA512_HMAC_MECH_INFO_TYPE:
	case SHA512_HMAC_GEN_MECH_INFO_TYPE:
		ctx->state.s64[0] = 0x6a09e667f3bcc908ULL;
		ctx->state.s64[1] = 0xbb67ae8584caa73bULL;
		ctx->state.s64[2] = 0x3c6ef372fe94f82bULL;
		ctx->state.s64[3] = 0xa54ff53a5f1d36f1ULL;
		ctx->state.s64[4] = 0x510e527fade682d1ULL;
		ctx->state.s64[5] = 0x9b05688c2b3e6c1fULL;
		ctx->state.s64[6] = 0x1f83d9abfb41bd6bULL;
		ctx->state.s64[7] = 0x5be0cd19137e2179ULL;
		break;
	case SHA512_224_MECH_INFO_TYPE:
		ctx->state.s64[0] = 0x8C3D37C819544DA2ULL;
		ctx->state.s64[1] = 0x73E1996689DCD4D6ULL;
		ctx->state.s64[2] = 0x1DFAB7AE32FF9C82ULL;
		ctx->state.s64[3] = 0x679DD514582F9FCFULL;
		ctx->state.s64[4] = 0x0F6D2B697BD44DA8ULL;
		ctx->state.s64[5] = 0x77E36F7304C48942ULL;
		ctx->state.s64[6] = 0x3F9D85A86A1D36C8ULL;
		ctx->state.s64[7] = 0x1112E6AD91D692A1ULL;
		break;
	case SHA512_256_MECH_INFO_TYPE:
		ctx->state.s64[0] = 0x22312194FC2BF72CULL;
		ctx->state.s64[1] = 0x9F555FA3C84C64C2ULL;
		ctx->state.s64[2] = 0x2393B86B6F53B151ULL;
		ctx->state.s64[3] = 0x963877195940EABDULL;
		ctx->state.s64[4] = 0x96283EE2A88EFFE3ULL;
		ctx->state.s64[5] = 0xBE5E1E2553863992ULL;
		ctx->state.s64[6] = 0x2B0199FC2C85B8AAULL;
		ctx->state.s64[7] = 0x0EB72DDC81C52CA2ULL;
		break;
#ifdef _KERNEL
	default:
		cmn_err(CE_PANIC,
		    "sha2_init: failed to find a supported algorithm: 0x%x",
		    (uint32_t)mech);

#endif /* _KERNEL */
	}

	ctx->algotype = (uint32_t)mech;
	ctx->count.c64[0] = ctx->count.c64[1] = 0;
}