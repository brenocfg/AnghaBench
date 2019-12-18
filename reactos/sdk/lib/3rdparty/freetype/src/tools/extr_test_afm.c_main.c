#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  memory; } ;
struct TYPE_13__ {scalar_t__ TrackKerns; scalar_t__ KernPairs; int /*<<< orphan*/  memory; } ;
typedef  TYPE_1__ FT_StreamRec ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  TYPE_2__* FT_Library ;
typedef  int FT_Error ;
typedef  TYPE_1__ AFM_FontInfoRec ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Done_FreeType (TYPE_2__*) ; 
 int FT_ERR (int /*<<< orphan*/ ) ; 
 int FT_Err_Ok ; 
 int /*<<< orphan*/  FT_FREE (scalar_t__) ; 
 int FT_Init_FreeType (TYPE_2__**) ; 
 int /*<<< orphan*/  FT_Stream_Close (TYPE_1__*) ; 
 int FT_Stream_Open (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  FT_ZERO (TYPE_1__*) ; 
 int /*<<< orphan*/  Invalid_Argument ; 
 int /*<<< orphan*/  dump_fontinfo (TYPE_1__*) ; 
 int parse_afm (TYPE_2__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main( int    argc,
            char** argv )
  {
    FT_Library       library;
    FT_StreamRec     stream;
    FT_Error         error = FT_Err_Ok;
    AFM_FontInfoRec  fi;


    if ( argc < 2 )
      return FT_ERR( Invalid_Argument );

    error = FT_Init_FreeType( &library );
    if ( error )
      return error;

    FT_ZERO( &stream );
    error = FT_Stream_Open( &stream, argv[1] );
    if ( error )
      goto Exit;
    stream.memory = library->memory;

    FT_ZERO( &fi );
    error = parse_afm( library, &stream, &fi );

    if ( !error )
    {
      FT_Memory  memory = library->memory;


      dump_fontinfo( &fi );

      if ( fi.KernPairs )
        FT_FREE( fi.KernPairs );
      if ( fi.TrackKerns )
        FT_FREE( fi.TrackKerns );
    }
    else
      printf( "parse error\n" );

    FT_Stream_Close( &stream );

  Exit:
    FT_Done_FreeType( library );

    return error;
  }