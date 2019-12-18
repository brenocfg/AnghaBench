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
typedef  char uint8_t ;
typedef  char uint16_t ;
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 int /*<<< orphan*/  bo_addle_u16 (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static void bo_addle_str16_nosize( bo_t *bo, const char *str )
{
    for( ;; )
    {
        uint16_t c = (uint8_t)*str++;
        bo_addle_u16( bo, c );
        if( c == '\0' ) break;
    }
}