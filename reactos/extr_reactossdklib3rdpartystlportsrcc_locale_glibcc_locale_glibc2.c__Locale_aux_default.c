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

/* Variables and functions */
 char const* _C_name ; 
 char* getenv (char const*) ; 

__attribute__((used)) static const char *_Locale_aux_default( const char *LC, char *nm )
{
  char *name = getenv( "LC_ALL" );

  if ( name != NULL && *name != 0 ) {
    return name;
  }
  name = getenv( LC );
  if ( name != NULL && *name != 0 ) {
    return name;
  }
  name = getenv( "LANG" );
  if ( name != NULL && *name != 0 ) {
    return name;
  }

  return _C_name;
}