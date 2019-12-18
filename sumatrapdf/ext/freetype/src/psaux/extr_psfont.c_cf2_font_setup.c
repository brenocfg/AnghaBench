#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_14__ ;
typedef  struct TYPE_26__   TYPE_11__ ;

/* Type definitions */
struct TYPE_30__ {int a; int d; int b; int c; } ;
struct TYPE_35__ {int tx; int ty; } ;
struct TYPE_28__ {void* usedBV; int /*<<< orphan*/  font; } ;
struct TYPE_36__ {scalar_t__ syntheticEmboldeningAmountX; scalar_t__ syntheticEmboldeningAmountY; scalar_t__ ppem; int renderingFlags; int stemDarkened; int unitsPerEm; scalar_t__ stdVW; scalar_t__ stdHW; int /*<<< orphan*/  blues; void* reverseWinding; void* darkened; int /*<<< orphan*/  darkenY; int /*<<< orphan*/  darkenX; int /*<<< orphan*/  darkenParams; TYPE_3__ outerTransform; TYPE_8__ innerTransform; TYPE_8__ currentTransform; void* hinted; int /*<<< orphan*/ * NDV; int /*<<< orphan*/  lenNDV; int /*<<< orphan*/  vsindex; TYPE_1__ blend; int /*<<< orphan*/  error; int /*<<< orphan*/  cffload; int /*<<< orphan*/  isT1; TYPE_7__* lastSubfont; TYPE_4__* decoder; } ;
struct TYPE_29__ {int /*<<< orphan*/  vsindex; } ;
struct TYPE_26__ {int /*<<< orphan*/  font; } ;
struct TYPE_34__ {TYPE_2__ private_dict; TYPE_11__ blend; } ;
struct TYPE_33__ {scalar_t__ dataCount; } ;
struct TYPE_32__ {int /*<<< orphan*/  (* load_private_dict ) (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* blend_check_vector ) (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_31__ {int /*<<< orphan*/  cff; } ;
struct TYPE_27__ {int /*<<< orphan*/  d; int /*<<< orphan*/  a; } ;
typedef  TYPE_4__ PS_Decoder ;
typedef  TYPE_5__* FT_Service_CFFLoad ;
typedef  int /*<<< orphan*/  FT_Fixed ;
typedef  int FT_Bool ;
typedef  TYPE_6__ CFF_VStoreRec ;
typedef  TYPE_7__* CFF_SubFont ;
typedef  int /*<<< orphan*/  CF2_UInt ;
typedef  TYPE_8__ CF2_Matrix ;
typedef  int CF2_Int ;
typedef  TYPE_9__* CF2_Font ;
typedef  scalar_t__ CF2_Fixed ;

/* Variables and functions */
 int CF2_FlagsDarkened ; 
 int CF2_FlagsHinted ; 
 void* FALSE ; 
 void* FT_BOOL (int) ; 
 void* FT_DivFix (int,scalar_t__) ; 
 int /*<<< orphan*/  FT_Err_Ok ; 
 scalar_t__ FT_MAX (scalar_t__,void*) ; 
 scalar_t__ MUL_INT32 (int,scalar_t__) ; 
 void* TRUE ; 
 int /*<<< orphan*/  cf2_blues_init (int /*<<< orphan*/ *,TYPE_9__*) ; 
 int /*<<< orphan*/  cf2_computeDarkening (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ cf2_fixedFracMul (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf2_getNormalizedVector (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ cf2_getPpemY (TYPE_4__*) ; 
 scalar_t__ cf2_getStdHW (TYPE_4__*) ; 
 scalar_t__ cf2_getStdVW (TYPE_4__*) ; 
 TYPE_7__* cf2_getSubfont (TYPE_4__*) ; 
 TYPE_6__* cf2_getVStore (TYPE_4__*) ; 
 int cf2_intToFixed (int) ; 
 TYPE_14__* fontMatrix ; 
 scalar_t__ ft_memcmp (TYPE_8__ const*,TYPE_8__*,int) ; 
 scalar_t__ stub1 (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
  cf2_font_setup( CF2_Font           font,
                  const CF2_Matrix*  transform )
  {
    /* pointer to parsed font object */
    PS_Decoder*  decoder = font->decoder;

    FT_Bool  needExtraSetup = FALSE;

    CFF_VStoreRec*  vstore;
    FT_Bool         hasVariations = FALSE;

    /* character space units */
    CF2_Fixed  boldenX = font->syntheticEmboldeningAmountX;
    CF2_Fixed  boldenY = font->syntheticEmboldeningAmountY;

    CFF_SubFont  subFont;
    CF2_Fixed    ppem;

    CF2_UInt   lenNormalizedV = 0;
    FT_Fixed*  normalizedV    = NULL;

    /* clear previous error */
    font->error = FT_Err_Ok;

    /* if a CID fontDict has changed, we need to recompute some cached */
    /* data                                                            */
    subFont = cf2_getSubfont( decoder );
    if ( font->lastSubfont != subFont )
    {
      font->lastSubfont = subFont;
      needExtraSetup    = TRUE;
    }

    if ( !font->isT1 )
    {
      FT_Service_CFFLoad  cffload = (FT_Service_CFFLoad)font->cffload;


      /* check for variation vectors */
      vstore        = cf2_getVStore( decoder );
      hasVariations = ( vstore->dataCount != 0 );

      if ( hasVariations )
      {
#ifdef TT_CONFIG_OPTION_GX_VAR_SUPPORT
        /* check whether Private DICT in this subfont needs to be reparsed */
        font->error = cf2_getNormalizedVector( decoder,
                                               &lenNormalizedV,
                                               &normalizedV );
        if ( font->error )
          return;

        if ( cffload->blend_check_vector( &subFont->blend,
                                          subFont->private_dict.vsindex,
                                          lenNormalizedV,
                                          normalizedV ) )
        {
          /* blend has changed, reparse */
          cffload->load_private_dict( decoder->cff,
                                      subFont,
                                      lenNormalizedV,
                                      normalizedV );
          needExtraSetup = TRUE;
        }
#endif

        /* copy from subfont */
        font->blend.font = subFont->blend.font;

        /* clear state of charstring blend */
        font->blend.usedBV = FALSE;

        /* initialize value for charstring */
        font->vsindex = subFont->private_dict.vsindex;

        /* store vector inputs for blends in charstring */
        font->lenNDV = lenNormalizedV;
        font->NDV    = normalizedV;
      }
    }

    /* if ppem has changed, we need to recompute some cached data         */
    /* note: because of CID font matrix concatenation, ppem and transform */
    /*       do not necessarily track.                                    */
    ppem = cf2_getPpemY( decoder );
    if ( font->ppem != ppem )
    {
      font->ppem     = ppem;
      needExtraSetup = TRUE;
    }

    /* copy hinted flag on each call */
    font->hinted = FT_BOOL( font->renderingFlags & CF2_FlagsHinted );

    /* determine if transform has changed;       */
    /* include Fontmatrix but ignore translation */
    if ( ft_memcmp( transform,
                    &font->currentTransform,
                    4 * sizeof ( CF2_Fixed ) ) != 0 )
    {
      /* save `key' information for `cache of one' matrix data; */
      /* save client transform, without the translation         */
      font->currentTransform    = *transform;
      font->currentTransform.tx =
      font->currentTransform.ty = cf2_intToFixed( 0 );

      /* TODO: FreeType transform is simple scalar; for now, use identity */
      /*       for outer                                                  */
      font->innerTransform   = *transform;
      font->outerTransform.a =
      font->outerTransform.d = cf2_intToFixed( 1 );
      font->outerTransform.b =
      font->outerTransform.c = cf2_intToFixed( 0 );

      needExtraSetup = TRUE;
    }

    /*
     * font->darkened is set to true if there is a stem darkening request or
     * the font is synthetic emboldened.
     * font->darkened controls whether to adjust blue zones, winding order,
     * and hinting.
     *
     */
    if ( font->stemDarkened != ( font->renderingFlags & CF2_FlagsDarkened ) )
    {
      font->stemDarkened =
        FT_BOOL( font->renderingFlags & CF2_FlagsDarkened );

      /* blue zones depend on darkened flag */
      needExtraSetup = TRUE;
    }

    /* recompute variables that are dependent on transform or FontDict or */
    /* darken flag                                                        */
    if ( needExtraSetup )
    {
      /* StdVW is found in the private dictionary;                       */
      /* recompute darkening amounts whenever private dictionary or      */
      /* transform change                                                */
      /* Note: a rendering flag turns darkening on or off, so we want to */
      /*       store the `on' amounts;                                   */
      /*       darkening amount is computed in character space           */
      /* TODO: testing size-dependent darkening here;                    */
      /*       what to do for rotations?                                 */

      CF2_Fixed  emRatio;
      CF2_Fixed  stdHW;
      CF2_Int    unitsPerEm = font->unitsPerEm;


      if ( unitsPerEm == 0 )
        unitsPerEm = 1000;

      ppem = FT_MAX( cf2_intToFixed( 4 ),
                     font->ppem ); /* use minimum ppem of 4 */

#if 0
      /* since vstem is measured in the x-direction, we use the `a' member */
      /* of the fontMatrix                                                 */
      emRatio = cf2_fixedFracMul( cf2_intToFixed( 1000 ), fontMatrix->a );
#endif

      /* Freetype does not preserve the fontMatrix when parsing; use */
      /* unitsPerEm instead.                                         */
      /* TODO: check precision of this                               */
      emRatio     = cf2_intToFixed( 1000 ) / unitsPerEm;
      font->stdVW = cf2_getStdVW( decoder );

      if ( font->stdVW <= 0 )
        font->stdVW = FT_DivFix( cf2_intToFixed( 75 ), emRatio );

      if ( boldenX > 0 )
      {
        /* Ensure that boldenX is at least 1 pixel for synthetic bold font */
        /* (similar to what Avalon does)                                   */
        boldenX = FT_MAX( boldenX,
                          FT_DivFix( cf2_intToFixed( unitsPerEm ), ppem ) );

        /* Synthetic emboldening adds at least 1 pixel to darkenX, while */
        /* stem darkening adds at most half pixel.  Since the purpose of */
        /* stem darkening (readability at small sizes) is met with       */
        /* synthetic emboldening, no need to add stem darkening for a    */
        /* synthetic bold font.                                          */
        cf2_computeDarkening( emRatio,
                              ppem,
                              font->stdVW,
                              &font->darkenX,
                              boldenX,
                              FALSE,
                              font->darkenParams );
      }
      else
        cf2_computeDarkening( emRatio,
                              ppem,
                              font->stdVW,
                              &font->darkenX,
                              0,
                              font->stemDarkened,
                              font->darkenParams );

#if 0
      /* since hstem is measured in the y-direction, we use the `d' member */
      /* of the fontMatrix                                                 */
      /* TODO: use the same units per em as above; check this              */
      emRatio = cf2_fixedFracMul( cf2_intToFixed( 1000 ), fontMatrix->d );
#endif

      /* set the default stem width, because it must be the same for all */
      /* family members;                                                 */
      /* choose a constant for StdHW that depends on font contrast       */
      stdHW = cf2_getStdHW( decoder );

      if ( stdHW > 0 && font->stdVW > MUL_INT32( 2, stdHW ) )
        font->stdHW = FT_DivFix( cf2_intToFixed( 75 ), emRatio );
      else
      {
        /* low contrast font gets less hstem darkening */
        font->stdHW = FT_DivFix( cf2_intToFixed( 110 ), emRatio );
      }

      cf2_computeDarkening( emRatio,
                            ppem,
                            font->stdHW,
                            &font->darkenY,
                            boldenY,
                            font->stemDarkened,
                            font->darkenParams );

      if ( font->darkenX != 0 || font->darkenY != 0 )
        font->darkened = TRUE;
      else
        font->darkened = FALSE;

      font->reverseWinding = FALSE; /* initial expectation is CCW */

      /* compute blue zones for this instance */
      cf2_blues_init( &font->blues, font );

    } /* needExtraSetup */
  }