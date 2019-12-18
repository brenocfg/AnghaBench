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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  scan_coderate_t ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertDelDrInnerFec (int) ; 
 int /*<<< orphan*/  SCAN_CODERATE_AUTO ; 

__attribute__((used)) static scan_coderate_t ConvertDelDrCodeRate( uint8_t v )
{
    if( v > 0x04 )
        return SCAN_CODERATE_AUTO;
    else
        return ConvertDelDrInnerFec( v + 1 );
}