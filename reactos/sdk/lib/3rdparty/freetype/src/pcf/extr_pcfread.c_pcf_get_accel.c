#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fontAscent; int fontDescent; int /*<<< orphan*/  maxbounds; int /*<<< orphan*/  ink_maxbounds; int /*<<< orphan*/  minbounds; int /*<<< orphan*/  ink_minbounds; int /*<<< orphan*/  maxOverlap; scalar_t__ drawDirection; scalar_t__ inkMetrics; scalar_t__ inkInside; scalar_t__ constantWidth; scalar_t__ terminalFont; scalar_t__ constantMetrics; scalar_t__ noOverlap; } ;
struct TYPE_6__ {int /*<<< orphan*/  count; int /*<<< orphan*/  tables; } ;
struct TYPE_7__ {TYPE_1__ toc; TYPE_3__ accel; } ;
typedef  TYPE_2__* PCF_Face ;
typedef  TYPE_3__* PCF_Accel ;
typedef  scalar_t__ FT_ULong ;
typedef  int /*<<< orphan*/  FT_Stream ;
typedef  scalar_t__ FT_Error ;

/* Variables and functions */
 int FT_ABS (int) ; 
 scalar_t__ FT_READ_ULONG_LE (scalar_t__) ; 
 scalar_t__ FT_STREAM_READ_FIELDS (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  FT_TRACE0 (char*) ; 
 int /*<<< orphan*/  FT_TRACE4 (char*) ; 
 int /*<<< orphan*/  FT_TRACE5 (char*) ; 
 scalar_t__ MSBFirst ; 
 int /*<<< orphan*/  PCF_ACCEL_W_INKBOUNDS ; 
 scalar_t__ PCF_BDF_ACCELERATORS ; 
 scalar_t__ PCF_BYTE_ORDER (scalar_t__) ; 
 int /*<<< orphan*/  PCF_DEFAULT_FORMAT ; 
 scalar_t__ PCF_FORMAT_MASK ; 
 scalar_t__ PCF_FORMAT_MATCH (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcf_accel_header ; 
 int /*<<< orphan*/  pcf_accel_msb_header ; 
 scalar_t__ pcf_get_metric (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ pcf_seek_to_table_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static FT_Error
  pcf_get_accel( FT_Stream  stream,
                 PCF_Face   face,
                 FT_ULong   type )
  {
    FT_ULong   format, size;
    FT_Error   error;
    PCF_Accel  accel = &face->accel;


    error = pcf_seek_to_table_type( stream,
                                    face->toc.tables,
                                    face->toc.count,
                                    type,
                                    &format,
                                    &size );
    if ( error )
      goto Bail;

    if ( FT_READ_ULONG_LE( format ) )
      goto Bail;

    FT_TRACE4(( "pcf_get_accel%s:\n"
                "  format: 0x%lX (%s, %s)\n",
                type == PCF_BDF_ACCELERATORS ? " (getting BDF accelerators)"
                                             : "",
                format,
                PCF_BYTE_ORDER( format ) == MSBFirst ? "MSB" : "LSB",
                PCF_FORMAT_MATCH( format, PCF_ACCEL_W_INKBOUNDS ) ?
                  "accelerated" : "not accelerated" ));

    if ( !PCF_FORMAT_MATCH( format, PCF_DEFAULT_FORMAT )    &&
         !PCF_FORMAT_MATCH( format, PCF_ACCEL_W_INKBOUNDS ) )
      goto Bail;

    if ( PCF_BYTE_ORDER( format ) == MSBFirst )
    {
      if ( FT_STREAM_READ_FIELDS( pcf_accel_msb_header, accel ) )
        goto Bail;
    }
    else
    {
      if ( FT_STREAM_READ_FIELDS( pcf_accel_header, accel ) )
        goto Bail;
    }

    FT_TRACE5(( "  noOverlap=%s, constantMetrics=%s,"
                " terminalFont=%s, constantWidth=%s\n"
                "  inkInside=%s, inkMetrics=%s, drawDirection=%s\n"
                "  fontAscent=%ld, fontDescent=%ld, maxOverlap=%ld\n",
                accel->noOverlap ? "yes" : "no",
                accel->constantMetrics ? "yes" : "no",
                accel->terminalFont ? "yes" : "no",
                accel->constantWidth ? "yes" : "no",
                accel->inkInside ? "yes" : "no",
                accel->inkMetrics ? "yes" : "no",
                accel->drawDirection ? "RTL" : "LTR",
                accel->fontAscent,
                accel->fontDescent,
                accel->maxOverlap ));

    /* sanity checks */
    if ( FT_ABS( accel->fontAscent ) > 0x7FFF )
    {
      accel->fontAscent = accel->fontAscent < 0 ? -0x7FFF : 0x7FFF;
      FT_TRACE0(( "pfc_get_accel: clamping font ascent to value %d\n",
                  accel->fontAscent ));
    }
    if ( FT_ABS( accel->fontDescent ) > 0x7FFF )
    {
      accel->fontDescent = accel->fontDescent < 0 ? -0x7FFF : 0x7FFF;
      FT_TRACE0(( "pfc_get_accel: clamping font descent to value %d\n",
                  accel->fontDescent ));
    }

    FT_TRACE5(( "  minbounds:" ));
    error = pcf_get_metric( stream,
                            format & ( ~PCF_FORMAT_MASK ),
                            &(accel->minbounds) );
    if ( error )
      goto Bail;

    FT_TRACE5(( "  maxbounds:" ));
    error = pcf_get_metric( stream,
                            format & ( ~PCF_FORMAT_MASK ),
                            &(accel->maxbounds) );
    if ( error )
      goto Bail;

    if ( PCF_FORMAT_MATCH( format, PCF_ACCEL_W_INKBOUNDS ) )
    {
      FT_TRACE5(( "  ink minbounds:" ));
      error = pcf_get_metric( stream,
                              format & ( ~PCF_FORMAT_MASK ),
                              &(accel->ink_minbounds) );
      if ( error )
        goto Bail;

      FT_TRACE5(( "  ink maxbounds:" ));
      error = pcf_get_metric( stream,
                              format & ( ~PCF_FORMAT_MASK ),
                              &(accel->ink_maxbounds) );
      if ( error )
        goto Bail;
    }
    else
    {
      accel->ink_minbounds = accel->minbounds;
      accel->ink_maxbounds = accel->maxbounds;
    }

  Bail:
    return error;
  }