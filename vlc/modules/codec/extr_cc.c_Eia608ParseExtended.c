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
typedef  int /*<<< orphan*/  eia608_t ;
typedef  int /*<<< orphan*/  eia608_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIA608_STATUS_CHANGED ; 
 int /*<<< orphan*/  Eia608Cursor (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Eia608Write (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static eia608_status_t Eia608ParseExtended( eia608_t *h, uint8_t d1, uint8_t d2 )
{
    assert( d2 >= 0x20 && d2 <= 0x3f );
    assert( d1 == 0x12 || d1 == 0x13 );
    if( d1 == 0x12 )
        d2 += 0x70; /* We use charaters 0x90-0xaf */
    else
        d2 += 0x90; /* We use charaters 0xb0-0xcf */

    Debug(printf("[EXT %x->'%c']", d2, d2));
    /* The extended characters replace the previous one with a more
     * advanced one */
    Eia608Cursor( h, -1 );
    Eia608Write( h, d2 );
    return EIA608_STATUS_CHANGED;
}