#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int e_wellknowntype; int /*<<< orphan*/  i_blob; int /*<<< orphan*/  p_blob; } ;
typedef  TYPE_1__ MP4_Box_data_data_t ;

/* Variables and functions */
#define  DATA_WKT_SJIS 132 
#define  DATA_WKT_UTF16 131 
#define  DATA_WKT_UTF16_SORT 130 
#define  DATA_WKT_UTF8 129 
#define  DATA_WKT_UTF8_SORT 128 
 char* FromCharset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static char * StringConvert( const MP4_Box_data_data_t *p_data )
{
    if ( !p_data || !p_data->i_blob )
        return NULL;

    switch( p_data->e_wellknowntype )
    {
    case DATA_WKT_UTF8:
    case DATA_WKT_UTF8_SORT:
        return FromCharset( "UTF-8", p_data->p_blob, p_data->i_blob );
    case DATA_WKT_UTF16:
    case DATA_WKT_UTF16_SORT:
        return FromCharset( "UTF-16BE", p_data->p_blob, p_data->i_blob );
    case DATA_WKT_SJIS:
        return FromCharset( "SHIFT-JIS", p_data->p_blob, p_data->i_blob );
    default:
        return NULL;
    }
}