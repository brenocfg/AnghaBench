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
struct callback_ctx {int /*<<< orphan*/  regions; int /*<<< orphan*/  styles; } ;
typedef  enum webvtt_header_line_e { ____Placeholder_webvtt_header_line_e } webvtt_header_line_e ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int) ; 
 int WEBVTT_HEADER_REGION ; 
 int WEBVTT_HEADER_STYLE ; 
 int /*<<< orphan*/  memstream_Append (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void ParserHeaderHandler( void *priv, enum webvtt_header_line_e s,
                                 bool b_new, const char *psz_line )
{
    VLC_UNUSED(b_new);
    struct callback_ctx *ctx = (struct callback_ctx *) priv;
    if( s == WEBVTT_HEADER_STYLE )
        memstream_Append( &ctx->styles, psz_line );
    else if( s == WEBVTT_HEADER_REGION )
        memstream_Append( &ctx->regions, psz_line );
}