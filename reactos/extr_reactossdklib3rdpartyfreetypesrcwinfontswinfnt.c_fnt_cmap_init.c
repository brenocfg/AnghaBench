#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {void* first; void* count; } ;
struct TYPE_9__ {TYPE_2__* font; } ;
struct TYPE_7__ {void* last_char; scalar_t__ first_char; } ;
struct TYPE_8__ {TYPE_1__ header; } ;
typedef  void* FT_UInt32 ;
typedef  int /*<<< orphan*/  FT_Pointer ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  TYPE_2__* FNT_Font ;
typedef  TYPE_3__* FNT_Face ;
typedef  TYPE_4__* FNT_CMap ;

/* Variables and functions */
 int /*<<< orphan*/  FT_CMAP_FACE (TYPE_4__*) ; 
 int /*<<< orphan*/  FT_UNUSED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Error
  fnt_cmap_init( FNT_CMap    cmap,
                 FT_Pointer  pointer )
  {
    FNT_Face  face = (FNT_Face)FT_CMAP_FACE( cmap );
    FNT_Font  font = face->font;

    FT_UNUSED( pointer );


    cmap->first = (FT_UInt32)  font->header.first_char;
    cmap->count = (FT_UInt32)( font->header.last_char - cmap->first + 1 );

    return 0;
  }