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
 size_t _Locale_MAX_SIMPLE_NAME ; 
 size_t strcspn (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 char* strstr (char*,char const*) ; 

__attribute__((used)) static char const*__Extract_locale_name( const char *loc, const char *category, char *buf )
{
  char *expr;
  size_t len_name;

  if( loc[0]=='L' && loc[1]=='C' && loc[2]=='_') {
    expr = strstr( (char*)loc, category );
    if ( expr == NULL )
      return NULL; /* Category not found. */
    ++expr;
    len_name = strcspn( expr, ";" );
    len_name = len_name >= _Locale_MAX_SIMPLE_NAME ? _Locale_MAX_SIMPLE_NAME - 1 : len_name;
    strncpy( buf, expr, len_name );
    buf[len_name] = 0;
    return buf;
  }
  return loc;
}