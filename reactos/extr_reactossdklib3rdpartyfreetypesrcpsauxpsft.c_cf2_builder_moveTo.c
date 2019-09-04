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
struct TYPE_10__ {scalar_t__ op; } ;
struct TYPE_9__ {TYPE_1__* decoder; } ;
struct TYPE_8__ {scalar_t__ path_begun; } ;
struct TYPE_7__ {TYPE_2__ builder; } ;
typedef  TYPE_2__ PS_Builder ;
typedef  int /*<<< orphan*/  CF2_OutlineCallbacks ;
typedef  TYPE_3__* CF2_Outline ;
typedef  TYPE_4__* CF2_CallbackParams ;

/* Variables and functions */
 scalar_t__ CF2_PathOpMoveTo ; 
 int /*<<< orphan*/  FT_ASSERT (int) ; 
 int /*<<< orphan*/  ps_builder_close_contour (TYPE_2__*) ; 

__attribute__((used)) static void
  cf2_builder_moveTo( CF2_OutlineCallbacks      callbacks,
                      const CF2_CallbackParams  params )
  {
    /* downcast the object pointer */
    CF2_Outline  outline = (CF2_Outline)callbacks;
    PS_Builder*  builder;

    (void)params;        /* only used in debug mode */


    FT_ASSERT( outline && outline->decoder );
    FT_ASSERT( params->op == CF2_PathOpMoveTo );

    builder = &outline->decoder->builder;

    /* note: two successive moves simply close the contour twice */
    ps_builder_close_contour( builder );
    builder->path_begun = 0;
  }