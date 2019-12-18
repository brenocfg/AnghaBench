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

/* Variables and functions */
 int /*<<< orphan*/  Debug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Eia608Cursor (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static bool Eia608ParseCommand0x17( eia608_t *h, uint8_t d2 )
{
    switch( d2 )
    {
    case 0x21:  /* Tab offset 1 */
    case 0x22:  /* Tab offset 2 */
    case 0x23:  /* Tab offset 3 */
        Debug(printf("[TO%d]", d2 - 0x20));
        Eia608Cursor( h, d2 - 0x20 );
        break;
    }
    return false;
}