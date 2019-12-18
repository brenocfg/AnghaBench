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
typedef  int /*<<< orphan*/  text_style_t ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  text_style_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

text_style_t *text_style_Duplicate( const text_style_t *p_src )
{
    if( !p_src )
        return NULL;

    text_style_t *p_dst = calloc( 1, sizeof(*p_dst) );
    if( p_dst )
        text_style_Copy( p_dst, p_src );
    return p_dst;
}