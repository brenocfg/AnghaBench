#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cursor; } ;
typedef  int FT_UShort ;
typedef  int /*<<< orphan*/  FT_ULong ;
typedef  TYPE_1__* FT_Stream ;
typedef  scalar_t__ FT_Error ;

/* Variables and functions */
 scalar_t__ FT_Err_Ok ; 
 int /*<<< orphan*/  FT_FRAME_ENTER (size_t) ; 
 int /*<<< orphan*/  FT_FRAME_EXIT () ; 
 scalar_t__ FT_STREAM_SEEK (int /*<<< orphan*/ ) ; 
 scalar_t__ FT_THROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unknown_File_Format ; 
 scalar_t__ ft_memcmp (int /*<<< orphan*/ ,char const*,size_t) ; 
 scalar_t__ read_pfb_tag (TYPE_1__*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static FT_Error
  check_type1_format( FT_Stream    stream,
                      const char*  header_string,
                      size_t       header_length )
  {
    FT_Error   error;
    FT_UShort  tag;
    FT_ULong   dummy;


    if ( FT_STREAM_SEEK( 0 ) )
      goto Exit;

    error = read_pfb_tag( stream, &tag, &dummy );
    if ( error )
      goto Exit;

    /* We assume that the first segment in a PFB is always encoded as   */
    /* text.  This might be wrong (and the specification doesn't insist */
    /* on that), but we have never seen a counterexample.               */
    if ( tag != 0x8001U && FT_STREAM_SEEK( 0 ) )
      goto Exit;

    if ( !FT_FRAME_ENTER( header_length ) )
    {
      error = FT_Err_Ok;

      if ( ft_memcmp( stream->cursor, header_string, header_length ) != 0 )
        error = FT_THROW( Unknown_File_Format );

      FT_FRAME_EXIT();
    }

  Exit:
    return error;
  }