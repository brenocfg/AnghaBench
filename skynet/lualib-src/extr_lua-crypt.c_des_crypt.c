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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DES_FP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DES_IP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DES_ROUND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_UINT32 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  PUT_UINT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void 
des_crypt( const uint32_t SK[32], const uint8_t input[8], uint8_t output[8] ) {
	uint32_t X, Y, T;

	GET_UINT32( X, input, 0 );
	GET_UINT32( Y, input, 4 );

	DES_IP( X, Y );

	DES_ROUND( Y, X );  DES_ROUND( X, Y );
	DES_ROUND( Y, X );  DES_ROUND( X, Y );
	DES_ROUND( Y, X );  DES_ROUND( X, Y );
	DES_ROUND( Y, X );  DES_ROUND( X, Y );
	DES_ROUND( Y, X );  DES_ROUND( X, Y );
	DES_ROUND( Y, X );  DES_ROUND( X, Y );
	DES_ROUND( Y, X );  DES_ROUND( X, Y );
	DES_ROUND( Y, X );  DES_ROUND( X, Y );

	DES_FP( Y, X );

	PUT_UINT32( Y, output, 0 );
	PUT_UINT32( X, output, 4 );
}