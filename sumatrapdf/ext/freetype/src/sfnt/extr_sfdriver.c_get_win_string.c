#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ (* char_type_func ) (scalar_t__) ;
struct TYPE_6__ {scalar_t__ cursor; } ;
struct TYPE_5__ {int stringLength; char* string; scalar_t__ stringOffset; } ;
typedef  TYPE_1__* TT_Name ;
typedef  int FT_UInt ;
typedef  char FT_String ;
typedef  TYPE_2__* FT_Stream ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  scalar_t__ FT_Char ;
typedef  scalar_t__ FT_Bool ;

/* Variables and functions */
 scalar_t__ FT_ALLOC (char*,int) ; 
 int /*<<< orphan*/  FT_Err_Ok ; 
 scalar_t__ FT_FRAME_ENTER (int) ; 
 int /*<<< orphan*/  FT_FRAME_EXIT () ; 
 int /*<<< orphan*/  FT_FREE (char*) ; 
 scalar_t__ FT_STREAM_SEEK (scalar_t__) ; 
 int /*<<< orphan*/  FT_TRACE0 (char*) ; 
 int /*<<< orphan*/  FT_UNUSED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char*
  get_win_string( FT_Memory       memory,
                  FT_Stream       stream,
                  TT_Name         entry,
                  char_type_func  char_type,
                  FT_Bool         report_invalid_characters )
  {
    FT_Error  error = FT_Err_Ok;

    char*       result = NULL;
    FT_String*  r;
    FT_Char*    p;
    FT_UInt     len;

    FT_UNUSED( error );


    if ( FT_ALLOC( result, entry->stringLength / 2 + 1 ) )
      return NULL;

    if ( FT_STREAM_SEEK( entry->stringOffset ) ||
         FT_FRAME_ENTER( entry->stringLength ) )
      goto get_win_string_error;

    r = (FT_String*)result;
    p = (FT_Char*)stream->cursor;

    for ( len = entry->stringLength / 2; len > 0; len--, p += 2 )
    {
      if ( p[0] == 0 && char_type( p[1] ) )
        *r++ = p[1];
      else
      {
        if ( report_invalid_characters )
          FT_TRACE0(( "get_win_string:"
                      " Character 0x%X invalid in PS name string\n",
                      ((unsigned)p[0])*256 + (unsigned)p[1] ));
        break;
      }
    }
    if ( !len )
      *r = '\0';

    FT_FRAME_EXIT();

    if ( !len )
      return result;

  get_win_string_error:
    FT_FREE( result );

    entry->stringLength = 0;
    entry->stringOffset = 0;
    FT_FREE( entry->string );

    return NULL;
  }