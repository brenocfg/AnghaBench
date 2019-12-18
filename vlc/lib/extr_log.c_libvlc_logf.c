#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_log_t ;
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ log; } ;
typedef  TYPE_2__ libvlc_instance_t ;

/* Variables and functions */
 int LIBVLC_DEBUG ; 
 int LIBVLC_ERROR ; 
 int LIBVLC_NOTICE ; 
 int LIBVLC_WARNING ; 
#define  VLC_MSG_DBG 131 
#define  VLC_MSG_ERR 130 
#define  VLC_MSG_INFO 129 
#define  VLC_MSG_WARN 128 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void libvlc_logf (void *data, int level, const vlc_log_t *item,
                         const char *fmt, va_list ap)
{
    libvlc_instance_t *inst = data;

    switch (level)
    {
        case VLC_MSG_INFO: level = LIBVLC_NOTICE;  break;
        case VLC_MSG_ERR:  level = LIBVLC_ERROR;   break;
        case VLC_MSG_WARN: level = LIBVLC_WARNING; break;
        case VLC_MSG_DBG:  level = LIBVLC_DEBUG;   break;
    }

    inst->log.cb (inst->log.data, level, item, fmt, ap);
}