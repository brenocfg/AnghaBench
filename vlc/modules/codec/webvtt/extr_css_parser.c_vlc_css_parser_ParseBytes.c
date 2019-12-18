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
typedef  int /*<<< orphan*/  yyscan_t ;
typedef  int /*<<< orphan*/  vlc_css_parser_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  YY_BUFFER_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  yy_delete_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yy_scan_bytes (char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yylex_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yylex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yyparse (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool vlc_css_parser_ParseBytes( vlc_css_parser_t *p_parser, const uint8_t *p_data, size_t i_data )
{
    yyscan_t yy;
    yylex_init(&yy);

    YY_BUFFER_STATE buf = yy_scan_bytes( (const char*) p_data, i_data, yy );

    bool b_ret = !yyparse( yy, p_parser );

    yy_delete_buffer( buf, yy );
    yylex_destroy( yy );

    return b_ret;
}