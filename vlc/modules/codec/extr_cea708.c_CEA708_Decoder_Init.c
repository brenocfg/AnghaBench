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
struct TYPE_3__ {int b_text_waiting; scalar_t__ i_clock; int /*<<< orphan*/  suspended_deadline; int /*<<< orphan*/ * window; int /*<<< orphan*/ * p_cw; int /*<<< orphan*/  input_buffer; } ;
typedef  TYPE_1__ cea708_t ;

/* Variables and functions */
 size_t CEA708_WINDOWS_COUNT ; 
 int /*<<< orphan*/  CEA708_Window_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  cea708_input_buffer_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CEA708_Decoder_Init( cea708_t *p_cea708 )
{
    cea708_input_buffer_init( &p_cea708->input_buffer );
    for(size_t i=0; i<CEA708_WINDOWS_COUNT; i++)
        CEA708_Window_Init( &p_cea708->window[i] );
    p_cea708->p_cw = &p_cea708->window[0];
    p_cea708->suspended_deadline = VLC_TICK_INVALID;
    p_cea708->b_text_waiting = false;
    p_cea708->i_clock = 0;
}