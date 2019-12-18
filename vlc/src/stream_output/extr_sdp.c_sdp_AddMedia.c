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
struct vlc_memstream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  vlc_memstream_printf (struct vlc_memstream*,char*,...) ; 
 int /*<<< orphan*/  vlc_memstream_puts (struct vlc_memstream*,char*) ; 

void sdp_AddMedia(struct vlc_memstream *restrict stream,
                  const char *type, const char *proto, int dport,
                  unsigned pt, bool bw_indep, unsigned bw,
                  const char *ptname, unsigned clock, unsigned chans,
                  const char *fmtp)
{
    /* Some default values */
    if (type == NULL)
        type = "video";
    if (proto == NULL)
        proto = "RTP/AVP";
    assert (pt < 128u);

    vlc_memstream_printf(stream, "m=%s %u %s %u\r\n", type, dport, proto, pt);

    if (bw > 0)
        vlc_memstream_printf(stream, "b=%s:%u\r\n",
                             bw_indep ? "TIAS" : "AS", bw);
    vlc_memstream_printf(stream, "b=%s:%u\r\n", "RR", 0);

    /* RTP payload type map */
    if (ptname != NULL)
    {
        vlc_memstream_printf(stream, "a=rtpmap:%u %s/%u", pt, ptname, clock);
        if ((strcmp(type, "audio") == 0) && (chans != 1))
            vlc_memstream_printf(stream, "/%u", chans);
        vlc_memstream_puts(stream, "\r\n");
    }

    /* Format parameters */
    if (fmtp != NULL)
        vlc_memstream_printf(stream, "a=fmtp:%u %s\r\n", pt, fmtp);
}