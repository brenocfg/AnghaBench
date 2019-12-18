#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_1__* AFM_Stream ;

/* Variables and functions */
 int AFM_GETC () ; 
 scalar_t__ AFM_IS_EOF (int) ; 
 scalar_t__ AFM_IS_NEWLINE (int) ; 
 scalar_t__ AFM_IS_SEP (int) ; 
 scalar_t__ AFM_IS_SPACE (int) ; 
 scalar_t__ AFM_STATUS_EOC (TYPE_1__*) ; 
 char* AFM_STREAM_KEY_BEGIN (TYPE_1__*) ; 
 int /*<<< orphan*/  AFM_STREAM_STATUS_EOC ; 
 int /*<<< orphan*/  AFM_STREAM_STATUS_EOF ; 
 int /*<<< orphan*/  AFM_STREAM_STATUS_EOL ; 
 int /*<<< orphan*/  afm_stream_skip_spaces (TYPE_1__*) ; 

__attribute__((used)) static char*
  afm_stream_read_one( AFM_Stream  stream )
  {
    char*  str;


    afm_stream_skip_spaces( stream );
    if ( AFM_STATUS_EOC( stream ) )
      return NULL;

    str = AFM_STREAM_KEY_BEGIN( stream );

    while ( 1 )
    {
      int  ch = AFM_GETC();


      if ( AFM_IS_SPACE( ch ) )
        break;
      else if ( AFM_IS_NEWLINE( ch ) )
      {
        stream->status = AFM_STREAM_STATUS_EOL;
        break;
      }
      else if ( AFM_IS_SEP( ch ) )
      {
        stream->status = AFM_STREAM_STATUS_EOC;
        break;
      }
      else if ( AFM_IS_EOF( ch ) )
      {
        stream->status = AFM_STREAM_STATUS_EOF;
        break;
      }
    }

    return str;
  }