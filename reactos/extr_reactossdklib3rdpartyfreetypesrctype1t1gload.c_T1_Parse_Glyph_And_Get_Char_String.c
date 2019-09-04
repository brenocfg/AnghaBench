#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {scalar_t__ length; scalar_t__ pointer; } ;
struct TYPE_25__ {int /*<<< orphan*/  (* t1_make_subfont ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* ps_decoder_init ) (TYPE_7__*,TYPE_6__*,int /*<<< orphan*/ ) ;TYPE_5__* t1_decoder_funcs; } ;
struct TYPE_24__ {int /*<<< orphan*/ * current_subfont; } ;
struct TYPE_18__ {scalar_t__ glyph; scalar_t__ metrics_only; int /*<<< orphan*/  face; } ;
struct TYPE_23__ {TYPE_1__ builder; int /*<<< orphan*/  font_offset; int /*<<< orphan*/  font_matrix; } ;
struct TYPE_22__ {scalar_t__ (* parse_charstrings ) (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;scalar_t__ (* parse_metrics ) (TYPE_6__*,int /*<<< orphan*/ *,size_t) ;} ;
struct TYPE_20__ {int /*<<< orphan*/  private_dict; scalar_t__* charstrings_len; scalar_t__* charstrings; int /*<<< orphan*/  font_offset; int /*<<< orphan*/  font_matrix; } ;
struct TYPE_21__ {TYPE_3__ type1; int /*<<< orphan*/  psaux; } ;
struct TYPE_19__ {int /*<<< orphan*/  hint; } ;
typedef  TYPE_2__* T1_GlyphSlot ;
typedef  TYPE_3__* T1_Font ;
typedef  TYPE_4__* T1_Face ;
typedef  TYPE_5__* T1_Decoder_Funcs ;
typedef  TYPE_6__* T1_Decoder ;
typedef  TYPE_7__ PS_Decoder ;
typedef  TYPE_8__* PSAux_Service ;
typedef  int /*<<< orphan*/  FT_ULong ;
typedef  size_t FT_UInt ;
typedef  scalar_t__ FT_Int ;
typedef  scalar_t__ FT_Error ;
typedef  TYPE_9__ FT_Data ;
typedef  int /*<<< orphan*/  FT_Byte ;
typedef  int /*<<< orphan*/  FT_Bool ;
typedef  int /*<<< orphan*/  CFF_SubFontRec ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FT_ERR_EQ (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ FT_Err_Ok ; 
 int /*<<< orphan*/  FT_FACE (TYPE_4__*) ; 
 int /*<<< orphan*/  Glyph_Too_Big ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ stub1 (TYPE_6__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub4 (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub5 (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

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