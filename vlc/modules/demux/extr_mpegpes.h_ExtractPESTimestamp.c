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
typedef  int /*<<< orphan*/  stime_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetPESTimestamp (int const*) ; 

__attribute__((used)) static inline bool ExtractPESTimestamp( const uint8_t *p_data, uint8_t i_flags, stime_t *ret )
{
    /* !warn broken muxers set incorrect flags. see #17773 and #19140 */
    /* check marker bits, and i_flags = b 0010, 0011 or 0001 */
    if((p_data[0] & 0xC1) != 0x01 ||
       (p_data[2] & 0x01) != 0x01 ||
       (p_data[4] & 0x01) != 0x01 ||
       (p_data[0] & 0x30) == 0 || /* at least needs one bit */
       (p_data[0] >> 5) > i_flags ) /* needs flags 1x => 1x or flags 01 => 01 */
        return false;


    *ret =  GetPESTimestamp( p_data );
    return true;
}