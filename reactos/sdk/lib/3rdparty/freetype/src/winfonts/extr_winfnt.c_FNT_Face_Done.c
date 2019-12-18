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
struct TYPE_3__ {scalar_t__ num_fixed_sizes; int /*<<< orphan*/  available_sizes; } ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  TYPE_1__* FT_Face ;
typedef  int /*<<< orphan*/  FNT_Face ;

/* Variables and functions */
 int /*<<< orphan*/  FT_FACE_MEMORY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnt_font_done (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  FNT_Face_Done( FT_Face  fntface )       /* FNT_Face */
  {
    FNT_Face   face = (FNT_Face)fntface;
    FT_Memory  memory;


    if ( !face )
      return;

    memory = FT_FACE_MEMORY( face );

    fnt_font_done( face );

    FT_FREE( fntface->available_sizes );
    fntface->num_fixed_sizes = 0;
  }