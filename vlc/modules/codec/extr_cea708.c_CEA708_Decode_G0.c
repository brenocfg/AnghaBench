#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {TYPE_2__* p_cw; int /*<<< orphan*/  b_text_waiting; int /*<<< orphan*/  input_buffer; } ;
typedef  TYPE_1__ cea708_t ;
typedef  int /*<<< orphan*/  cea708_input_buffer_t ;
struct TYPE_6__ {int /*<<< orphan*/  b_visible; int /*<<< orphan*/  b_defined; } ;

/* Variables and functions */
 int CEA708_STATUS_OK ; 
 int CEA708_STATUS_OUTPUT ; 
 scalar_t__ CEA708_Window_BreaksSpace (TYPE_2__*) ; 
 int /*<<< orphan*/  CEA708_Window_Write (int*,TYPE_2__*) ; 
 int /*<<< orphan*/  POP_COMMAND () ; 

__attribute__((used)) static int CEA708_Decode_G0( uint8_t code, cea708_t *p_cea708 )
{
    cea708_input_buffer_t *ib = &p_cea708->input_buffer;
    POP_COMMAND();
    int i_ret = CEA708_STATUS_OK;

    if( !p_cea708->p_cw->b_defined )
        return i_ret;

    uint8_t utf8[4] = {code,0x00,0x00,0x00};

    if(code == 0x7F) // Music note
    {
        utf8[0] = 0xe2;
        utf8[1] = 0x99;
        utf8[2] = 0xaa;
    }

    CEA708_Window_Write( utf8, p_cea708->p_cw );

    if( code == 0x20 &&
        p_cea708->b_text_waiting &&
        CEA708_Window_BreaksSpace( p_cea708->p_cw ) )
    {
        i_ret |= CEA708_STATUS_OUTPUT;
    }


    p_cea708->b_text_waiting |= p_cea708->p_cw->b_visible;

    return i_ret;
}