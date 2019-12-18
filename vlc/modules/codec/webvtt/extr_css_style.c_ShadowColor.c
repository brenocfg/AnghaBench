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
typedef  int /*<<< orphan*/  vlc_css_term_t ;
struct TYPE_3__ {int /*<<< orphan*/  i_features; int /*<<< orphan*/  i_shadow_alpha; int /*<<< orphan*/  i_shadow_color; } ;
typedef  TYPE_1__ text_style_t ;

/* Variables and functions */
 int /*<<< orphan*/  Color (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STYLE_HAS_SHADOW_ALPHA ; 
 int /*<<< orphan*/  STYLE_HAS_SHADOW_COLOR ; 

__attribute__((used)) static void ShadowColor( vlc_css_term_t term, text_style_t *p_style )
{
    Color( term, &p_style->i_shadow_color, &p_style->i_shadow_alpha,
           &p_style->i_features, STYLE_HAS_SHADOW_COLOR, STYLE_HAS_SHADOW_ALPHA );
}