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
typedef  int uint_fast32_t ;
struct vlc_http_msg {int dummy; } ;
struct vlc_h2_frame {int dummy; } ;

/* Variables and functions */
 int VLC_H2_DEFAULT_MAX_FRAME ; 
 int VLC_H2_MAX_HEADERS ; 
 int /*<<< orphan*/  assert (int) ; 
 struct vlc_http_msg* vlc_http_msg_h2_headers (unsigned int,char const***) ; 

struct vlc_h2_frame *
vlc_h2_frame_headers(uint_fast32_t id, uint_fast32_t mtu, bool eos,
                     unsigned count, const char *const tab[][2])
{
    struct vlc_http_msg *m;

    assert(id == 1);
    assert(mtu == VLC_H2_DEFAULT_MAX_FRAME);
    assert(eos);

    const char *headers[VLC_H2_MAX_HEADERS][2];

    for (unsigned i = 0; i < count; i++)
    {
        headers[i][0] = tab[i][0];
        headers[i][1] = tab[i][1];
    }

    m = vlc_http_msg_h2_headers(count, headers);
    return (struct vlc_h2_frame *)m; /* gruik */
}