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
 int /*<<< orphan*/  STYLE_FULLY_SET ; 
 int /*<<< orphan*/ * text_style_Create (int /*<<< orphan*/ ) ; 

text_style_t *text_style_New( void )
{
    return text_style_Create( STYLE_FULLY_SET );
}