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

/* Variables and functions */
 int GetDWBE (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int MpgaCheckSync( const uint8_t *p_peek )
{
    uint32_t h = GetDWBE( p_peek );

    if( ((( h >> 21 )&0x07FF) != 0x07FF )   /* header sync */
        || (((h >> 19)&0x03) == 1 )         /* valid version ID ? */
        || (((h >> 17)&0x03) == 0 )         /* valid layer ?*/
        || (((h >> 12)&0x0F) == 0x0F )      /* valid bitrate ?*/
        || (((h >> 10) & 0x03) == 0x03 )    /* valide sampling freq ? */
        || ((h & 0x03) == 0x02 ))           /* valid emphasis ? */
    {
        return false;
    }
    return true;
}