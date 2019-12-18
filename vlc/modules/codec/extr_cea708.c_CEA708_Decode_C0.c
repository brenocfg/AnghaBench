#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_10__ {int b_text_waiting; TYPE_3__* p_cw; int /*<<< orphan*/  input_buffer; } ;
typedef  TYPE_2__ cea708_t ;
typedef  int /*<<< orphan*/  cea708_input_buffer_t ;
struct TYPE_9__ {int /*<<< orphan*/  print_direction; } ;
struct TYPE_11__ {int /*<<< orphan*/  b_defined; int /*<<< orphan*/  b_visible; TYPE_1__ style; int /*<<< orphan*/  row; int /*<<< orphan*/  col; } ;

/* Variables and functions */
#define  CEA708_C0_BS 135 
#define  CEA708_C0_CR 134 
#define  CEA708_C0_ETX 133 
#define  CEA708_C0_EXT1 132 
#define  CEA708_C0_FF 131 
#define  CEA708_C0_HCR 130 
#define  CEA708_C0_NUL 129 
#define  CEA708_C0_P16 128 
 int CEA708_Decode_G2G3 (int,TYPE_2__*) ; 
 int CEA708_Decode_P16 (int,TYPE_2__*) ; 
 int CEA708_STATUS_OK ; 
 int CEA708_STATUS_OUTPUT ; 
 int CEA708_STATUS_STARVING ; 
 int /*<<< orphan*/  CEA708_WA_DIRECTION_RTL ; 
 int /*<<< orphan*/  CEA708_Window_Backward (TYPE_3__*) ; 
 int /*<<< orphan*/  CEA708_Window_CarriageReturn (TYPE_3__*) ; 
 int /*<<< orphan*/  CEA708_Window_ClearText (TYPE_3__*) ; 
 int /*<<< orphan*/  Debug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POP_ARGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POP_COMMAND () ; 
 int /*<<< orphan*/  REQUIRE_ARGS_AND_POP_COMMAND (int) ; 
 int cea708_input_buffer_get (int /*<<< orphan*/ *) ; 
 int cea708_input_buffer_peek (int /*<<< orphan*/ *,int) ; 
 int cea708_input_buffer_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int CEA708_Decode_C0( uint8_t code, cea708_t *p_cea708 )
{
    uint8_t v, i;
    uint16_t u16;
    cea708_input_buffer_t *ib = &p_cea708->input_buffer;
    int i_ret = CEA708_STATUS_OK;

    switch( code )
    {
        case CEA708_C0_NUL:
            POP_COMMAND();
            break;
        case CEA708_C0_ETX:
            POP_COMMAND();
            if( p_cea708->b_text_waiting )
            {
                i_ret |= CEA708_STATUS_OUTPUT;
                p_cea708->b_text_waiting = false;
            }
            break;
        case CEA708_C0_BS:
            POP_COMMAND();
            if( !p_cea708->p_cw->b_defined )
                break;
            CEA708_Window_Backward( p_cea708->p_cw );
            p_cea708->b_text_waiting = true;
            break;
        case CEA708_C0_FF:
            POP_COMMAND();
            if( !p_cea708->p_cw->b_defined )
                break;
            CEA708_Window_ClearText( p_cea708->p_cw );
            p_cea708->p_cw->col = 0;
            p_cea708->p_cw->row = 0;
            p_cea708->b_text_waiting = true;
            break;
        case CEA708_C0_CR:
            POP_COMMAND();
            if( !p_cea708->p_cw->b_defined )
                break;
            if( p_cea708->p_cw->style.print_direction <= CEA708_WA_DIRECTION_RTL )
            {
                CEA708_Window_CarriageReturn( p_cea708->p_cw );
                if( p_cea708->p_cw->b_visible )
                    i_ret |= CEA708_STATUS_OUTPUT;
            }
            break;
        case CEA708_C0_HCR:
            POP_COMMAND();
            if( !p_cea708->p_cw->b_defined )
                break;
            if( p_cea708->p_cw->style.print_direction > CEA708_WA_DIRECTION_RTL )
            {
                CEA708_Window_CarriageReturn( p_cea708->p_cw );
                if( p_cea708->p_cw->b_visible )
                    i_ret |= CEA708_STATUS_OUTPUT;
            }
            break;
        case CEA708_C0_EXT1: /* Special extended table case */
            if( cea708_input_buffer_size( ib ) >= 2 )
            {
                v = cea708_input_buffer_peek( ib, 1 );
                /* C2 extended code set */
                if( v < 0x20 )
                {
                    if( v > 0x17 )
                        i = 3;
                    else if( v > 0x0f )
                        i = 2;
                    else if( v > 0x07 )
                        i = 1;
                    else
                        i = 0;
                    if( cea708_input_buffer_size( ib ) < 2 + i )
                        return CEA708_STATUS_STARVING;
                    POP_COMMAND();
                    POP_ARGS(1 + i);
                }
                /* C3 extended code set */
                else if( v > 0x7f && v < 0xa0 )
                {
                    if( v > 0x87 )
                        i = 5;
                    else
                        i = 4;
                    if( cea708_input_buffer_size( ib ) < 2 + i )
                        return CEA708_STATUS_STARVING;
                    POP_COMMAND();
                    POP_ARGS(1 + i);
                }
                else
                {
                    POP_COMMAND();
                    v = cea708_input_buffer_get( ib );
                    if( p_cea708->p_cw->b_defined )
                        i_ret |= CEA708_Decode_G2G3( v, p_cea708 );
                }
            }
            else return CEA708_STATUS_STARVING;
            break;
        case CEA708_C0_P16:
            REQUIRE_ARGS_AND_POP_COMMAND(2);
            u16 = cea708_input_buffer_get( ib ) << 8;
            u16 |= cea708_input_buffer_get( ib );
            i_ret |= CEA708_Decode_P16( u16, p_cea708 );
            Debug(printf("[P16 %x]", u16));
            break;
        default:
            POP_COMMAND();
            Debug(printf("[UNK %2.2x]", code));
            break;
    }
    Debug(printf("[C0 %x]", code));
    return i_ret;
}