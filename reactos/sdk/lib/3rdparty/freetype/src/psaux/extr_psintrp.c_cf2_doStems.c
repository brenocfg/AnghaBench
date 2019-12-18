#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ width_only; int /*<<< orphan*/  flex_state; } ;
struct TYPE_7__ {TYPE_3__* decoder; scalar_t__ isT1; } ;
struct TYPE_6__ {scalar_t__ minDS; scalar_t__ maxDS; int /*<<< orphan*/  used; void* max; void* min; } ;
typedef  scalar_t__ FT_Bool ;
typedef  int CF2_UInt ;
typedef  TYPE_1__ CF2_StemHintRec ;
typedef  int /*<<< orphan*/  CF2_Stack ;
typedef  TYPE_2__* CF2_Font ;
typedef  void* CF2_Fixed ;
typedef  int /*<<< orphan*/  CF2_ArrStack ;

/* Variables and functions */
 void* ADD_INT32 (void*,void*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FT_ERROR (char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  cf2_arrstack_push (int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* cf2_getNominalWidthX (TYPE_3__*) ; 
 int /*<<< orphan*/  cf2_stack_clear (int /*<<< orphan*/ ) ; 
 int cf2_stack_count (int /*<<< orphan*/ ) ; 
 void* cf2_stack_getReal (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
  cf2_doStems( const CF2_Font  font,
               CF2_Stack       opStack,
               CF2_ArrStack    stemHintArray,
               CF2_Fixed*      width,
               FT_Bool*        haveWidth,
               CF2_Fixed       hintOffset )
  {
    CF2_UInt  i;
    CF2_UInt  count       = cf2_stack_count( opStack );
    FT_Bool   hasWidthArg = (FT_Bool)( count & 1 );

    /* variable accumulates delta values from operand stack */
    CF2_Fixed  position = hintOffset;

    if ( font->isT1 && !font->decoder->flex_state && !*haveWidth )
      FT_ERROR(( "cf2_doStems (Type 1 mode):"
                 " No width. Use hsbw/sbw as first op\n" ));

    if ( !font->isT1 && hasWidthArg && !*haveWidth )
      *width = ADD_INT32( cf2_stack_getReal( opStack, 0 ),
                          cf2_getNominalWidthX( font->decoder ) );

    if ( font->decoder->width_only )
      goto exit;

    for ( i = hasWidthArg ? 1 : 0; i < count; i += 2 )
    {
      /* construct a CF2_StemHint and push it onto the list */
      CF2_StemHintRec  stemhint;


      stemhint.min =
      position     = ADD_INT32( position,
                                cf2_stack_getReal( opStack, i ) );
      stemhint.max =
      position     = ADD_INT32( position,
                                cf2_stack_getReal( opStack, i + 1 ) );

      stemhint.used  = FALSE;
      stemhint.maxDS =
      stemhint.minDS = 0;

      cf2_arrstack_push( stemHintArray, &stemhint ); /* defer error check */
    }

    cf2_stack_clear( opStack );

  exit:
    /* cf2_doStems must define a width (may be default) */
    *haveWidth = TRUE;
  }