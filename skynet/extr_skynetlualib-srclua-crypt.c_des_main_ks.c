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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int Y ;
typedef  size_t X ;

/* Variables and functions */
 int /*<<< orphan*/  GET_UINT32 (int,int /*<<< orphan*/  const*,int) ; 
 int* LHs ; 
 int* RHs ; 

__attribute__((used)) static void 
des_main_ks( uint32_t SK[32], const uint8_t key[8] ) {
	int i;
	uint32_t X, Y, T;

	GET_UINT32( X, key, 0 );
	GET_UINT32( Y, key, 4 );

	/* Permuted Choice 1 */

	T =  ((Y >>  4) ^ X) & 0x0F0F0F0F;  X ^= T; Y ^= (T <<  4);
	T =  ((Y	  ) ^ X) & 0x10101010;  X ^= T; Y ^= (T	  );

	X =   (LHs[ (X	  ) & 0xF] << 3) | (LHs[ (X >>  8) & 0xF ] << 2)
		| (LHs[ (X >> 16) & 0xF] << 1) | (LHs[ (X >> 24) & 0xF ]	 )
		| (LHs[ (X >>  5) & 0xF] << 7) | (LHs[ (X >> 13) & 0xF ] << 6)
		| (LHs[ (X >> 21) & 0xF] << 5) | (LHs[ (X >> 29) & 0xF ] << 4);

	Y =   (RHs[ (Y >>  1) & 0xF] << 3) | (RHs[ (Y >>  9) & 0xF ] << 2)
		| (RHs[ (Y >> 17) & 0xF] << 1) | (RHs[ (Y >> 25) & 0xF ]	 )
		| (RHs[ (Y >>  4) & 0xF] << 7) | (RHs[ (Y >> 12) & 0xF ] << 6)
		| (RHs[ (Y >> 20) & 0xF] << 5) | (RHs[ (Y >> 28) & 0xF ] << 4);

	X &= 0x0FFFFFFF;
	Y &= 0x0FFFFFFF;

	/* calculate subkeys */

	for( i = 0; i < 16; i++ )
	{
		if( i < 2 || i == 8 || i == 15 )
		{
			X = ((X <<  1) | (X >> 27)) & 0x0FFFFFFF;
			Y = ((Y <<  1) | (Y >> 27)) & 0x0FFFFFFF;
		}
		else
		{
			X = ((X <<  2) | (X >> 26)) & 0x0FFFFFFF;
			Y = ((Y <<  2) | (Y >> 26)) & 0x0FFFFFFF;
		}

		*SK++ =   ((X <<  4) & 0x24000000) | ((X << 28) & 0x10000000)
				| ((X << 14) & 0x08000000) | ((X << 18) & 0x02080000)
				| ((X <<  6) & 0x01000000) | ((X <<  9) & 0x00200000)
				| ((X >>  1) & 0x00100000) | ((X << 10) & 0x00040000)
				| ((X <<  2) & 0x00020000) | ((X >> 10) & 0x00010000)
				| ((Y >> 13) & 0x00002000) | ((Y >>  4) & 0x00001000)
				| ((Y <<  6) & 0x00000800) | ((Y >>  1) & 0x00000400)
				| ((Y >> 14) & 0x00000200) | ((Y	  ) & 0x00000100)
				| ((Y >>  5) & 0x00000020) | ((Y >> 10) & 0x00000010)
				| ((Y >>  3) & 0x00000008) | ((Y >> 18) & 0x00000004)
				| ((Y >> 26) & 0x00000002) | ((Y >> 24) & 0x00000001);

		*SK++ =   ((X << 15) & 0x20000000) | ((X << 17) & 0x10000000)
				| ((X << 10) & 0x08000000) | ((X << 22) & 0x04000000)
				| ((X >>  2) & 0x02000000) | ((X <<  1) & 0x01000000)
				| ((X << 16) & 0x00200000) | ((X << 11) & 0x00100000)
				| ((X <<  3) & 0x00080000) | ((X >>  6) & 0x00040000)
				| ((X << 15) & 0x00020000) | ((X >>  4) & 0x00010000)
				| ((Y >>  2) & 0x00002000) | ((Y <<  8) & 0x00001000)
				| ((Y >> 14) & 0x00000808) | ((Y >>  9) & 0x00000400)
				| ((Y	  ) & 0x00000200) | ((Y <<  7) & 0x00000100)
				| ((Y >>  7) & 0x00000020) | ((Y >>  3) & 0x00000011)
				| ((Y <<  2) & 0x00000004) | ((Y >> 21) & 0x00000002);
	}
}