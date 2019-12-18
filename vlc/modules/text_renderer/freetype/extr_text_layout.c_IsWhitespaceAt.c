#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* p_code_points; scalar_t__* p_types; } ;
typedef  TYPE_1__ paragraph_t ;

/* Variables and functions */
 scalar_t__ FRIBIDI_TYPE_WS ; 

__attribute__((used)) static inline bool IsWhitespaceAt( paragraph_t *p_paragraph, size_t i )
{
    return ( p_paragraph->p_code_points[ i ] == ' '
#ifdef HAVE_FRIBIDI
            || p_paragraph->p_types[ i ] == FRIBIDI_TYPE_WS
#endif
    );
}