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
typedef  unsigned long long ulong_t ;
typedef  int uint8_t ;
typedef  void* uint64_t ;
typedef  void* uint32_t ;

/* Variables and functions */
 void* htonl (unsigned long long) ; 

__attribute__((used)) static void
encode_adata_len(ulong_t auth_data_len, uint8_t *encoded, size_t *encoded_len)
{
#ifdef UNALIGNED_POINTERS_PERMITTED
	uint32_t	*lencoded_ptr;
#ifdef _LP64
	uint64_t	*llencoded_ptr;
#endif
#endif	/* UNALIGNED_POINTERS_PERMITTED */

	if (auth_data_len < ((1ULL<<16) - (1ULL<<8))) {
		/* 0 < a < (2^16-2^8) */
		*encoded_len = 2;
		encoded[0] = (auth_data_len & 0xff00) >> 8;
		encoded[1] = auth_data_len & 0xff;

	} else if ((auth_data_len >= ((1ULL<<16) - (1ULL<<8))) &&
	    (auth_data_len < (1ULL << 31))) {
		/* (2^16-2^8) <= a < 2^32 */
		*encoded_len = 6;
		encoded[0] = 0xff;
		encoded[1] = 0xfe;
#ifdef UNALIGNED_POINTERS_PERMITTED
		lencoded_ptr = (uint32_t *)&encoded[2];
		*lencoded_ptr = htonl(auth_data_len);
#else
		encoded[2] = (auth_data_len & 0xff000000) >> 24;
		encoded[3] = (auth_data_len & 0xff0000) >> 16;
		encoded[4] = (auth_data_len & 0xff00) >> 8;
		encoded[5] = auth_data_len & 0xff;
#endif	/* UNALIGNED_POINTERS_PERMITTED */

#ifdef _LP64
	} else {
		/* 2^32 <= a < 2^64 */
		*encoded_len = 10;
		encoded[0] = 0xff;
		encoded[1] = 0xff;
#ifdef UNALIGNED_POINTERS_PERMITTED
		llencoded_ptr = (uint64_t *)&encoded[2];
		*llencoded_ptr = htonl(auth_data_len);
#else
		encoded[2] = (auth_data_len & 0xff00000000000000) >> 56;
		encoded[3] = (auth_data_len & 0xff000000000000) >> 48;
		encoded[4] = (auth_data_len & 0xff0000000000) >> 40;
		encoded[5] = (auth_data_len & 0xff00000000) >> 32;
		encoded[6] = (auth_data_len & 0xff000000) >> 24;
		encoded[7] = (auth_data_len & 0xff0000) >> 16;
		encoded[8] = (auth_data_len & 0xff00) >> 8;
		encoded[9] = auth_data_len & 0xff;
#endif	/* UNALIGNED_POINTERS_PERMITTED */
#endif	/* _LP64 */
	}
}