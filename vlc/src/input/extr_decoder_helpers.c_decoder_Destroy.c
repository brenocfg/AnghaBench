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
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  decoder_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (int /*<<< orphan*/ *) ; 

void decoder_Destroy( decoder_t *p_dec )
{
    if (p_dec != NULL)
    {
        decoder_Clean( p_dec );
        vlc_object_delete(p_dec);
    }
}