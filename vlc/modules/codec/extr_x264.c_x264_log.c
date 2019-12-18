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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  encoder_t ;

/* Variables and functions */
 int VLC_MSG_DBG ; 
 int VLC_MSG_ERR ; 
 int VLC_MSG_INFO ; 
 int VLC_MSG_WARN ; 
#define  X264_LOG_DEBUG 131 
#define  X264_LOG_ERROR 130 
#define  X264_LOG_INFO 129 
#define  X264_LOG_WARNING 128 
 int /*<<< orphan*/  msg_GenericVa (int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void x264_log( void *data, int i_level, const char *psz, va_list args)
{
    encoder_t *p_enc = (encoder_t *)data;

    switch( i_level )
    {
        case X264_LOG_ERROR:
            i_level = VLC_MSG_ERR;
            break;
        case X264_LOG_WARNING:
            i_level = VLC_MSG_WARN;
            break;
        case X264_LOG_INFO:
            i_level = VLC_MSG_INFO;
            break;
        case X264_LOG_DEBUG:
        default:
            i_level = VLC_MSG_DBG;
    }

    msg_GenericVa( p_enc, i_level, psz, args );
}