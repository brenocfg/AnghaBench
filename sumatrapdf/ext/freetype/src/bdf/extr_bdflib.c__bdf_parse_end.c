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
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Err_Ok ; 
 int /*<<< orphan*/  FT_UNUSED (void*) ; 

__attribute__((used)) static FT_Error
  _bdf_parse_end( char*          line,
                  unsigned long  linelen,
                  unsigned long  lineno,
                  void*          call_data,
                  void*          client_data )
  {
    /* a no-op; we ignore everything after `ENDFONT' */

    FT_UNUSED( line );
    FT_UNUSED( linelen );
    FT_UNUSED( lineno );
    FT_UNUSED( call_data );
    FT_UNUSED( client_data );

    return FT_Err_Ok;
  }