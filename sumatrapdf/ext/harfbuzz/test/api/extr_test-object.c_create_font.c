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
typedef  void hb_font_t ;
typedef  int /*<<< orphan*/  hb_face_t ;

/* Variables and functions */
 scalar_t__ create_face () ; 
 int /*<<< orphan*/  hb_face_destroy (int /*<<< orphan*/ *) ; 
 void* hb_font_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
create_font (void)
{
  hb_face_t *face = (hb_face_t *) create_face ();
  hb_font_t *font = hb_font_create (face);
  hb_face_destroy (face);
  return font;
}