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
typedef  int /*<<< orphan*/  cea708_t ;

/* Variables and functions */
 int /*<<< orphan*/  CEA708_Decoder_Reset (int /*<<< orphan*/ *) ; 

void CEA708_Decoder_Flush( cea708_t *p_cea708 )
{
    CEA708_Decoder_Reset( p_cea708 );
}