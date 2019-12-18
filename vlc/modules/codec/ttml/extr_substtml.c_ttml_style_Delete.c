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
struct TYPE_4__ {int /*<<< orphan*/  font_style; } ;
typedef  TYPE_1__ ttml_style_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  text_style_Delete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ttml_style_Delete( ttml_style_t* p_ttml_style )
{
    text_style_Delete( p_ttml_style->font_style );
    free( p_ttml_style );
}