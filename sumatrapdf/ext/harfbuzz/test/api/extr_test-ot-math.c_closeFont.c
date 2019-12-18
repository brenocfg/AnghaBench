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

/* Variables and functions */
 int /*<<< orphan*/  FT_Done_Face (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ft_face ; 
 int /*<<< orphan*/ * hb_face ; 
 int /*<<< orphan*/  hb_face_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_font ; 
 int /*<<< orphan*/  hb_font_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
closeFont (void)
{
  hb_face_destroy (hb_face);
  hb_font_destroy (hb_font);
  FT_Done_Face (ft_face);
  hb_face = NULL;
  hb_font = NULL;
  ft_face = NULL;
}