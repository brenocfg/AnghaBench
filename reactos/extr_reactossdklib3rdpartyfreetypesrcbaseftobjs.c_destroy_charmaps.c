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
struct TYPE_3__ {size_t num_charmaps; int /*<<< orphan*/ ** charmaps; } ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  size_t FT_Int ;
typedef  TYPE_1__* FT_Face ;
typedef  int /*<<< orphan*/  FT_CMap ;

/* Variables and functions */
 int /*<<< orphan*/  FT_CMAP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FT_FREE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ft_cmap_done_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  destroy_charmaps( FT_Face    face,
                    FT_Memory  memory )
  {
    FT_Int  n;


    if ( !face )
      return;

    for ( n = 0; n < face->num_charmaps; n++ )
    {
      FT_CMap  cmap = FT_CMAP( face->charmaps[n] );


      ft_cmap_done_internal( cmap );

      face->charmaps[n] = NULL;
    }

    FT_FREE( face->charmaps );
    face->num_charmaps = 0;
  }