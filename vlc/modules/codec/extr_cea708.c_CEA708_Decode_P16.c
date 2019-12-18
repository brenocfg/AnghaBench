#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {TYPE_2__* p_cw; int /*<<< orphan*/  b_text_waiting; } ;
typedef  TYPE_1__ cea708_t ;
struct TYPE_5__ {int /*<<< orphan*/  b_visible; int /*<<< orphan*/  b_defined; } ;

/* Variables and functions */
 int CEA708_STATUS_OK ; 
 int /*<<< orphan*/  CEA708_Window_Write (char*,TYPE_2__*) ; 

__attribute__((used)) static int CEA708_Decode_P16( uint16_t ucs2, cea708_t *p_cea708 )
{
    if( !p_cea708->p_cw->b_defined )
        return CEA708_STATUS_OK;

    uint8_t out[4] = { '?', 0, 0, 0 };

    /* adapted from codepoint conversion from strings.h */
    if( ucs2 <= 0x7F )
    {
        out[0] = ucs2;
    }
    else if( ucs2 <= 0x7FF )
    {
        out[0] = 0xC0 |  (ucs2 >>  6);
        out[1] = 0x80 |  (ucs2        & 0x3F);
    }
    else
    {
        out[0] = 0xE0 |  (ucs2 >> 12);
        out[1] = 0x80 | ((ucs2 >>  6) & 0x3F);
        out[2] = 0x80 |  (ucs2        & 0x3F);
    }

    CEA708_Window_Write( out, p_cea708->p_cw );

    p_cea708->b_text_waiting |= p_cea708->p_cw->b_visible;

    return CEA708_STATUS_OK;
}