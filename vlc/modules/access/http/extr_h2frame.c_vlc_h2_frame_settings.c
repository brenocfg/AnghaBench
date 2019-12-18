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
typedef  int /*<<< orphan*/  uint8_t ;
struct vlc_h2_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SetDWBE (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SetWBE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ VLC_H2_DEFAULT_INIT_WINDOW ; 
 scalar_t__ VLC_H2_DEFAULT_MAX_FRAME ; 
 scalar_t__ VLC_H2_DEFAULT_MAX_HEADER_TABLE ; 
 int /*<<< orphan*/  VLC_H2_FRAME_SETTINGS ; 
 scalar_t__ VLC_H2_INIT_WINDOW ; 
 scalar_t__ VLC_H2_MAX_FRAME ; 
 scalar_t__ VLC_H2_MAX_HEADER_LIST ; 
 scalar_t__ VLC_H2_MAX_HEADER_TABLE ; 
 scalar_t__ VLC_H2_MAX_STREAMS ; 
 int /*<<< orphan*/  VLC_H2_SETTING_ENABLE_PUSH ; 
 int /*<<< orphan*/  VLC_H2_SETTING_HEADER_TABLE_SIZE ; 
 int /*<<< orphan*/  VLC_H2_SETTING_INITIAL_WINDOW_SIZE ; 
 int /*<<< orphan*/  VLC_H2_SETTING_MAX_CONCURRENT_STREAMS ; 
 int /*<<< orphan*/  VLC_H2_SETTING_MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  VLC_H2_SETTING_MAX_HEADER_LIST_SIZE ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct vlc_h2_frame* vlc_h2_frame_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * vlc_h2_frame_payload (struct vlc_h2_frame*) ; 

struct vlc_h2_frame *vlc_h2_frame_settings(void)
{
    unsigned n = (VLC_H2_MAX_HEADER_TABLE != VLC_H2_DEFAULT_MAX_HEADER_TABLE)
               + 1 /* ENABLE_PUSH */
#if defined(VLC_H2_MAX_STREAMS)
               + 1
#endif
               + (VLC_H2_INIT_WINDOW != VLC_H2_DEFAULT_INIT_WINDOW)
               + (VLC_H2_MAX_FRAME != VLC_H2_DEFAULT_MAX_FRAME)
#if defined(VLC_H2_MAX_HEADER_LIST)
               + 1
#endif
    ;
    struct vlc_h2_frame *f = vlc_h2_frame_alloc(VLC_H2_FRAME_SETTINGS, 0, 0,
                                                n * 6);
    if (unlikely(f == NULL))
        return NULL;

    uint8_t *p = vlc_h2_frame_payload(f);

#if (VLC_H2_MAX_HEADER_TABLE != VLC_H2_DEFAULT_MAX_HEADER_TABLE)
    SetWBE(p, VLC_H2_SETTING_HEADER_TABLE_SIZE);
    SetDWBE(p + 2, VLC_H2_MAX_HEADER_TABLE);
    p += 6;
#endif

    SetWBE(p, VLC_H2_SETTING_ENABLE_PUSH);
    SetDWBE(p + 2, 0);
    p += 6;

#if defined(VLC_H2_MAX_STREAMS)
    SetWBE(p, VLC_H2_SETTING_MAX_CONCURRENT_STREAMS);
    SetDWBE(p + 2, VLC_H2_MAX_STREAMS);
    p += 6;
#endif

#if (VLC_H2_INIT_WINDOW != VLC_H2_DEFAULT_INIT_WINDOW)
# if (VLC_H2_INIT_WINDOW > 2147483647)
#  error Illegal initial window value
# endif
    SetWBE(p, VLC_H2_SETTING_INITIAL_WINDOW_SIZE);
    SetDWBE(p + 2, VLC_H2_INIT_WINDOW);
    p += 6;
#endif

#if (VLC_H2_MAX_FRAME != VLC_H2_DEFAULT_MAX_FRAME)
# if (VLC_H2_MAX_FRAME < 16384 || VLC_H2_MAX_FRAME > 16777215)
#  error Illegal maximum frame size
# endif
    SetWBE(p, VLC_H2_SETTING_MAX_FRAME_SIZE);
    SetDWBE(p + 2, VLC_H2_MAX_FRAME);
    p += 6;
#endif

#if defined(VLC_H2_MAX_HEADER_LIST)
    SetWBE(p, VLC_H2_SETTING_MAX_HEADER_LIST_SIZE);
    SetDWBE(p + 2, VLC_H2_MAX_HEADER_LIST);
    p += 6;
#endif

    return f;
}