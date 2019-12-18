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
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ vlc_css_term_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_features; int /*<<< orphan*/  i_style_flags; int /*<<< orphan*/  i_outline_width; } ;
typedef  TYPE_2__ text_style_t ;

/* Variables and functions */
 int /*<<< orphan*/  STYLE_HAS_FLAGS ; 
 int /*<<< orphan*/  STYLE_OUTLINE ; 
 scalar_t__ TYPE_PIXELS ; 

__attribute__((used)) static void OutlineWidth( vlc_css_term_t term, text_style_t *p_style )
{
    if( term.type >= TYPE_PIXELS )
    {
        p_style->i_outline_width = term.val;
        p_style->i_style_flags |= STYLE_OUTLINE;
        p_style->i_features |= STYLE_HAS_FLAGS;
    }
}