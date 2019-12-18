#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * window; } ;
typedef  TYPE_1__ cea708_t ;

/* Variables and functions */
 int /*<<< orphan*/  CEA708_Decoder_Init (TYPE_1__*) ; 
 size_t CEA708_WINDOWS_COUNT ; 
 int /*<<< orphan*/  CEA708_Window_Reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CEA708_Decoder_Reset( cea708_t *p_cea708 )
{
    for(size_t i=0; i<CEA708_WINDOWS_COUNT; i++)
        CEA708_Window_Reset( &p_cea708->window[i] );
    CEA708_Decoder_Init( p_cea708 );
}