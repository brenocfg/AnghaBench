#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  increase_x_height; int /*<<< orphan*/  glyph_styles; } ;
struct TYPE_12__ {size_t fallback_style; size_t default_script; int /*<<< orphan*/  no_stem_darkening; int /*<<< orphan*/ * darken_params; int /*<<< orphan*/  warping; } ;
struct TYPE_11__ {size_t script; } ;
struct TYPE_10__ {int /*<<< orphan*/  map; int /*<<< orphan*/  face; } ;
struct TYPE_9__ {int /*<<< orphan*/  limit; int /*<<< orphan*/  face; } ;
typedef  size_t FT_UInt ;
typedef  TYPE_1__ FT_Prop_IncreaseXHeight ;
typedef  TYPE_2__ FT_Prop_GlyphToScriptMap ;
typedef  int /*<<< orphan*/  FT_Module ;
typedef  int /*<<< orphan*/  FT_Int ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  int /*<<< orphan*/  FT_Bool ;
typedef  TYPE_3__* AF_StyleClass ;
typedef  TYPE_4__* AF_Module ;
typedef  TYPE_5__* AF_FaceGlobals ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Err_Ok ; 
 int /*<<< orphan*/  FT_THROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_TRACE0 (char*) ; 
 int /*<<< orphan*/  Missing_Property ; 
 int /*<<< orphan*/  af_property_get_face_globals (int /*<<< orphan*/ ,TYPE_5__**,TYPE_4__*) ; 
 TYPE_3__** af_style_classes ; 
 int /*<<< orphan*/  ft_strcmp (char const*,char*) ; 

__attribute__((used)) static FT_Error
  af_property_get( FT_Module    ft_module,
                   const char*  property_name,
                   void*        value )
  {
    FT_Error   error          = FT_Err_Ok;
    AF_Module  module         = (AF_Module)ft_module;
    FT_UInt    fallback_style = module->fallback_style;
    FT_UInt    default_script = module->default_script;
#ifdef AF_CONFIG_OPTION_USE_WARPER
    FT_Bool    warping        = module->warping;
#endif


    if ( !ft_strcmp( property_name, "glyph-to-script-map" ) )
    {
      FT_Prop_GlyphToScriptMap*  prop = (FT_Prop_GlyphToScriptMap*)value;
      AF_FaceGlobals             globals;


      error = af_property_get_face_globals( prop->face, &globals, module );
      if ( !error )
        prop->map = globals->glyph_styles;

      return error;
    }
    else if ( !ft_strcmp( property_name, "fallback-script" ) )
    {
      FT_UInt*  val = (FT_UInt*)value;

      AF_StyleClass  style_class = af_style_classes[fallback_style];


      *val = style_class->script;

      return error;
    }
    else if ( !ft_strcmp( property_name, "default-script" ) )
    {
      FT_UInt*  val = (FT_UInt*)value;


      *val = default_script;

      return error;
    }
    else if ( !ft_strcmp( property_name, "increase-x-height" ) )
    {
      FT_Prop_IncreaseXHeight*  prop = (FT_Prop_IncreaseXHeight*)value;
      AF_FaceGlobals            globals;


      error = af_property_get_face_globals( prop->face, &globals, module );
      if ( !error )
        prop->limit = globals->increase_x_height;

      return error;
    }
#ifdef AF_CONFIG_OPTION_USE_WARPER
    else if ( !ft_strcmp( property_name, "warping" ) )
    {
      FT_Bool*  val = (FT_Bool*)value;


      *val = warping;

      return error;
    }
#endif /* AF_CONFIG_OPTION_USE_WARPER */
    else if ( !ft_strcmp( property_name, "darkening-parameters" ) )
    {
      FT_Int*  darken_params = module->darken_params;
      FT_Int*  val           = (FT_Int*)value;


      val[0] = darken_params[0];
      val[1] = darken_params[1];
      val[2] = darken_params[2];
      val[3] = darken_params[3];
      val[4] = darken_params[4];
      val[5] = darken_params[5];
      val[6] = darken_params[6];
      val[7] = darken_params[7];

      return error;
    }
    else if ( !ft_strcmp( property_name, "no-stem-darkening" ) )
    {
      FT_Bool   no_stem_darkening = module->no_stem_darkening;
      FT_Bool*  val               = (FT_Bool*)value;


      *val = no_stem_darkening;

      return error;
    }

    FT_TRACE0(( "af_property_get: missing property `%s'\n",
                property_name ));
    return FT_THROW( Missing_Property );
  }