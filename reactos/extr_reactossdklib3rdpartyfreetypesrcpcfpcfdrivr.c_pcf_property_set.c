#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char const* FT_Module ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  char const* FT_Bool ;

/* Variables and functions */
 int /*<<< orphan*/  FT_THROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_TRACE0 (char*) ; 
 int /*<<< orphan*/  FT_UNUSED (char const*) ; 
 int /*<<< orphan*/  Missing_Property ; 

__attribute__((used)) static FT_Error
  pcf_property_set( FT_Module    module,         /* PCF_Driver */
                    const char*  property_name,
                    const void*  value,
                    FT_Bool      value_is_string )
  {
#ifdef PCF_CONFIG_OPTION_LONG_FAMILY_NAMES

    FT_Error    error  = FT_Err_Ok;
    PCF_Driver  driver = (PCF_Driver)module;

#ifndef FT_CONFIG_OPTION_ENVIRONMENT_PROPERTIES
    FT_UNUSED( value_is_string );
#endif


    if ( !ft_strcmp( property_name, "no-long-family-names" ) )
    {
#ifdef FT_CONFIG_OPTION_ENVIRONMENT_PROPERTIES
      if ( value_is_string )
      {
        const char*  s   = (const char*)value;
        long         lfn = ft_strtol( s, NULL, 10 );


        if ( lfn == 0 )
          driver->no_long_family_names = 0;
        else if ( lfn == 1 )
          driver->no_long_family_names = 1;
        else
          return FT_THROW( Invalid_Argument );
      }
      else
#endif
      {
        FT_Bool*  no_long_family_names = (FT_Bool*)value;


        driver->no_long_family_names = *no_long_family_names;
      }

      return error;
    }

#else /* !PCF_CONFIG_OPTION_LONG_FAMILY_NAMES */

    FT_UNUSED( module );
    FT_UNUSED( value );
    FT_UNUSED( value_is_string );
#ifndef FT_DEBUG_LEVEL_TRACE
    FT_UNUSED( property_name );
#endif

#endif /* !PCF_CONFIG_OPTION_LONG_FAMILY_NAMES */

    FT_TRACE0(( "pcf_property_set: missing property `%s'\n",
                property_name ));
    return FT_THROW( Missing_Property );
  }