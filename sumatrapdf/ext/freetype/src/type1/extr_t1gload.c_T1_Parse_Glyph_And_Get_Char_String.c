#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_9__ ;
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_1__ ;
typedef  struct TYPE_37__   TYPE_17__ ;
typedef  struct TYPE_36__   TYPE_16__ ;
typedef  struct TYPE_35__   TYPE_15__ ;
typedef  struct TYPE_34__   TYPE_14__ ;
typedef  struct TYPE_33__   TYPE_13__ ;
typedef  struct TYPE_32__   TYPE_12__ ;
typedef  struct TYPE_31__   TYPE_11__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
struct TYPE_45__ {int /*<<< orphan*/  private_dict; scalar_t__* charstrings_len; scalar_t__* charstrings; int /*<<< orphan*/  font_offset; int /*<<< orphan*/  font_matrix; } ;
struct TYPE_39__ {TYPE_1__* internal; } ;
struct TYPE_46__ {TYPE_8__ type1; TYPE_2__ root; int /*<<< orphan*/  psaux; } ;
struct TYPE_44__ {int /*<<< orphan*/  hint; } ;
struct TYPE_42__ {void* y; void* x; } ;
struct TYPE_41__ {void* x; } ;
struct TYPE_43__ {TYPE_5__ advance; TYPE_4__ left_bearing; scalar_t__ glyph; scalar_t__ metrics_only; int /*<<< orphan*/  face; } ;
struct TYPE_40__ {scalar_t__ (* get_glyph_metrics ) (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_15__*) ;scalar_t__ (* get_glyph_data ) (int /*<<< orphan*/ ,size_t,TYPE_17__*) ;} ;
struct TYPE_38__ {TYPE_16__* incremental_interface; } ;
struct TYPE_37__ {scalar_t__ length; scalar_t__ pointer; } ;
struct TYPE_36__ {int /*<<< orphan*/  object; TYPE_3__* funcs; } ;
struct TYPE_35__ {void* advance_v; void* advance; void* bearing_x; scalar_t__ bearing_y; } ;
struct TYPE_34__ {int /*<<< orphan*/  (* t1_make_subfont ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* ps_decoder_init ) (TYPE_13__*,TYPE_11__*,int /*<<< orphan*/ ) ;TYPE_10__* t1_decoder_funcs; } ;
struct TYPE_33__ {int /*<<< orphan*/ * current_subfont; } ;
struct TYPE_32__ {scalar_t__ hinting_engine; } ;
struct TYPE_31__ {TYPE_6__ builder; int /*<<< orphan*/  font_offset; int /*<<< orphan*/  font_matrix; } ;
struct TYPE_30__ {scalar_t__ (* parse_charstrings ) (TYPE_13__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;scalar_t__ (* parse_metrics ) (TYPE_11__*,int /*<<< orphan*/ *,size_t) ;scalar_t__ (* parse_charstrings_old ) (TYPE_11__*,int /*<<< orphan*/ *,size_t) ;} ;
typedef  TYPE_7__* T1_GlyphSlot ;
typedef  TYPE_8__* T1_Font ;
typedef  TYPE_9__* T1_Face ;
typedef  TYPE_10__* T1_Decoder_Funcs ;
typedef  TYPE_11__* T1_Decoder ;
typedef  TYPE_12__* PS_Driver ;
typedef  TYPE_13__ PS_Decoder ;
typedef  TYPE_14__* PSAux_Service ;
typedef  int /*<<< orphan*/  FT_ULong ;
typedef  size_t FT_UInt ;
typedef  scalar_t__ FT_Int ;
typedef  TYPE_15__ FT_Incremental_MetricsRec ;
typedef  TYPE_16__ FT_Incremental_InterfaceRec ;
typedef  scalar_t__ FT_Error ;
typedef  TYPE_17__ FT_Data ;
typedef  int /*<<< orphan*/  FT_Byte ;
typedef  int /*<<< orphan*/  FT_Bool ;
typedef  int /*<<< orphan*/  CFF_SubFontRec ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 void* FIXED_TO_INT (void*) ; 
 scalar_t__ FT_ERR_EQ (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ FT_Err_Ok ; 
 int /*<<< orphan*/  FT_FACE (TYPE_9__*) ; 
 int /*<<< orphan*/  FT_FACE_DRIVER (TYPE_9__*) ; 
 scalar_t__ FT_HINTING_FREETYPE ; 
 int /*<<< orphan*/  Glyph_Too_Big ; 
 void* INT_TO_FIXED (void*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,size_t,TYPE_17__*) ; 
 scalar_t__ stub2 (TYPE_11__*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ stub3 (TYPE_11__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  stub4 (TYPE_13__*,TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub6 (TYPE_13__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub7 (TYPE_13__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub8 (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_15__*) ; 

__attribute__((used)) static FT_Error
  T1_Parse_Glyph_And_Get_Char_String( T1_Decoder  decoder,
                                      FT_UInt     glyph_index,
                                      FT_Data*    char_string,
                                      FT_Bool*    force_scaling )
  {
    T1_Face   face  = (T1_Face)decoder->builder.face;
    T1_Font   type1 = &face->type1;
    FT_Error  error = FT_Err_Ok;

    PSAux_Service           psaux         = (PSAux_Service)face->psaux;
    const T1_Decoder_Funcs  decoder_funcs = psaux->t1_decoder_funcs;
    PS_Decoder              psdecoder;

#ifdef FT_CONFIG_OPTION_INCREMENTAL
    FT_Incremental_InterfaceRec *inc =
                      face->root.internal->incremental_interface;
#endif

#ifdef T1_CONFIG_OPTION_OLD_ENGINE
    PS_Driver  driver = (PS_Driver)FT_FACE_DRIVER( face );
#endif


    decoder->font_matrix = type1->font_matrix;
    decoder->font_offset = type1->font_offset;

#ifdef FT_CONFIG_OPTION_INCREMENTAL

    /* For incremental fonts get the character data using the */
    /* callback function.                                     */
    if ( inc )
      error = inc->funcs->get_glyph_data( inc->object,
                                          glyph_index, char_string );
    else

#endif /* FT_CONFIG_OPTION_INCREMENTAL */

    /* For ordinary fonts get the character data stored in the face record. */
    {
      char_string->pointer = type1->charstrings[glyph_index];
      char_string->length  = (FT_Int)type1->charstrings_len[glyph_index];
    }

    if ( !error )
    {
      /* choose which renderer to use */
#ifdef T1_CONFIG_OPTION_OLD_ENGINE
      if ( driver->hinting_engine == FT_HINTING_FREETYPE ||
           decoder->builder.metrics_only                 )
        error = decoder_funcs->parse_charstrings_old(
                  decoder,
                  (FT_Byte*)char_string->pointer,
                  (FT_UInt)char_string->length );
#else
      if ( decoder->builder.metrics_only )
        error = decoder_funcs->parse_metrics(
                  decoder,
                  (FT_Byte*)char_string->pointer,
                  (FT_UInt)char_string->length );
#endif
      else
      {
        CFF_SubFontRec  subfont;


        psaux->ps_decoder_init( &psdecoder, decoder, TRUE );

        psaux->t1_make_subfont( FT_FACE( face ),
                                &face->type1.private_dict, &subfont );
        psdecoder.current_subfont = &subfont;

        error = decoder_funcs->parse_charstrings(
                  &psdecoder,
                  (FT_Byte*)char_string->pointer,
                  (FT_ULong)char_string->length );

        /* Adobe's engine uses 16.16 numbers everywhere;              */
        /* as a consequence, glyphs larger than 2000ppem get rejected */
        if ( FT_ERR_EQ( error, Glyph_Too_Big ) )
        {
          /* this time, we retry unhinted and scale up the glyph later on */
          /* (the engine uses and sets the hardcoded value 0x10000 / 64 = */
          /* 0x400 for both `x_scale' and `y_scale' in this case)         */
          ((T1_GlyphSlot)decoder->builder.glyph)->hint = FALSE;

          *force_scaling = TRUE;

          error = decoder_funcs->parse_charstrings(
                    &psdecoder,
                    (FT_Byte*)char_string->pointer,
                    (FT_ULong)char_string->length );
        }
      }
    }

#ifdef FT_CONFIG_OPTION_INCREMENTAL

    /* Incremental fonts can optionally override the metrics. */
    if ( !error && inc && inc->funcs->get_glyph_metrics )
    {
      FT_Incremental_MetricsRec  metrics;


      metrics.bearing_x = FIXED_TO_INT( decoder->builder.left_bearing.x );
      metrics.bearing_y = 0;
      metrics.advance   = FIXED_TO_INT( decoder->builder.advance.x );
      metrics.advance_v = FIXED_TO_INT( decoder->builder.advance.y );

      error = inc->funcs->get_glyph_metrics( inc->object,
                                             glyph_index, FALSE, &metrics );

      decoder->builder.left_bearing.x = INT_TO_FIXED( metrics.bearing_x );
      decoder->builder.advance.x      = INT_TO_FIXED( metrics.advance );
      decoder->builder.advance.y      = INT_TO_FIXED( metrics.advance_v );
    }

#endif /* FT_CONFIG_OPTION_INCREMENTAL */

    return error;
  }