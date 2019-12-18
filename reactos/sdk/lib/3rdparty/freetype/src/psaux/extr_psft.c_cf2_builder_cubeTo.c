#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_18__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_17__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_16__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_23__ {scalar_t__ op; TYPE_5__ pt3; TYPE_4__ pt2; TYPE_3__ pt1; TYPE_2__ pt0; } ;
struct TYPE_22__ {TYPE_1__* decoder; } ;
struct TYPE_21__ {void** error; } ;
struct TYPE_20__ {int /*<<< orphan*/  path_begun; } ;
struct TYPE_15__ {TYPE_6__ builder; } ;
typedef  TYPE_6__ PS_Builder ;
typedef  void* FT_Error ;
typedef  TYPE_7__* CF2_OutlineCallbacks ;
typedef  TYPE_8__* CF2_Outline ;
typedef  TYPE_9__* CF2_CallbackParams ;

/* Variables and functions */
 scalar_t__ CF2_PathOpCubeTo ; 
 int /*<<< orphan*/  FT_ASSERT (int) ; 
 int /*<<< orphan*/  ps_builder_add_point (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* ps_builder_check_points (TYPE_6__*,int) ; 
 void* ps_builder_start_point (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  cf2_builder_cubeTo( CF2_OutlineCallbacks      callbacks,
                      const CF2_CallbackParams  params )
  {
    FT_Error  error;

    /* downcast the object pointer */
    CF2_Outline  outline = (CF2_Outline)callbacks;
    PS_Builder*  builder;


    FT_ASSERT( outline && outline->decoder );
    FT_ASSERT( params->op == CF2_PathOpCubeTo );

    builder = &outline->decoder->builder;

    if ( !builder->path_begun )
    {
      /* record the move before the line; also check points and set */
      /* `path_begun'                                               */
      error = ps_builder_start_point( builder,
                                      params->pt0.x,
                                      params->pt0.y );
      if ( error )
      {
        if ( !*callbacks->error )
          *callbacks->error =  error;
        return;
      }
    }

    /* prepare room for 3 points: 2 off-curve, 1 on-curve */
    error = ps_builder_check_points( builder, 3 );
    if ( error )
    {
      if ( !*callbacks->error )
        *callbacks->error =  error;
      return;
    }

    ps_builder_add_point( builder,
                          params->pt1.x,
                          params->pt1.y, 0 );
    ps_builder_add_point( builder,
                          params->pt2.x,
                          params->pt2.y, 0 );
    ps_builder_add_point( builder,
                          params->pt3.x,
                          params->pt3.y, 1 );
  }