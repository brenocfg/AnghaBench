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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ CEA708_OPACITY_TRANSLUCENT ; 
 scalar_t__ CEA708_OPACITY_TRANSPARENT ; 
 int STYLE_ALPHA_OPAQUE ; 
 scalar_t__ STYLE_ALPHA_TRANSPARENT ; 

__attribute__((used)) static uint8_t CEA708AlphaConvert( uint8_t c )
{
    if( c == CEA708_OPACITY_TRANSLUCENT )
        return STYLE_ALPHA_OPAQUE / 2;
    else if( c == CEA708_OPACITY_TRANSPARENT )
        return STYLE_ALPHA_TRANSPARENT;
    else
        return STYLE_ALPHA_OPAQUE;
}