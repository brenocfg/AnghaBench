#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  memory; } ;
struct TYPE_8__ {TYPE_1__* font; } ;
struct TYPE_7__ {struct TYPE_7__* family_name; scalar_t__ fnt_frame; } ;
typedef  int /*<<< orphan*/  FT_Stream ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  TYPE_1__* FNT_Font ;
typedef  TYPE_2__* FNT_Face ;

/* Variables and functions */
 TYPE_5__* FT_FACE (TYPE_2__*) ; 
 int /*<<< orphan*/  FT_FRAME_RELEASE (scalar_t__) ; 
 int /*<<< orphan*/  FT_FREE (TYPE_1__*) ; 

__attribute__((used)) static void
  fnt_font_done( FNT_Face face )
  {
    FT_Memory  memory = FT_FACE( face )->memory;
    FT_Stream  stream = FT_FACE( face )->stream;
    FNT_Font   font   = face->font;


    if ( !font )
      return;

    if ( font->fnt_frame )
      FT_FRAME_RELEASE( font->fnt_frame );
    FT_FREE( font->family_name );

    FT_FREE( font );
    face->font = NULL;
  }