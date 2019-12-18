#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {TYPE_2__* p_sys; int /*<<< orphan*/  pf_control; int /*<<< orphan*/ * pf_demux; int /*<<< orphan*/  psz_location; int /*<<< orphan*/  psz_name; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_8__ {int fd; int rtcp_fd; int thread_ready; int autodetect; int /*<<< orphan*/  thread; int /*<<< orphan*/ * srtp; int /*<<< orphan*/ * session; void* max_misorder; void* max_dropout; int /*<<< orphan*/  timeout; void* max_src; int /*<<< orphan*/ * chained_demux; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Control ; 
#define  IPPROTO_DCCP 131 
#define  IPPROTO_TCP 130 
#define  IPPROTO_UDP 129 
#define  IPPROTO_UDPLITE 128 
 int /*<<< orphan*/  SOCK_DCCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SRTP_AUTH_HMAC_SHA1 ; 
 int /*<<< orphan*/  SRTP_ENCR_AES_CM ; 
 int /*<<< orphan*/  SRTP_PRF_AES_CM ; 
 int /*<<< orphan*/  SRTP_RCC_MODE1 ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_INPUT ; 
 int /*<<< orphan*/  VLC_VAR_STRING ; 
 int extract_port (char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  net_Close (int) ; 
 int net_Connect (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int) ; 
 int net_OpenDgram (int /*<<< orphan*/ *,char*,int,char*,int,int) ; 
 int /*<<< orphan*/  net_SetCSCov (int,int,int) ; 
 int /*<<< orphan*/  rtp_dgram_thread ; 
 int /*<<< orphan*/ * rtp_session_create (TYPE_1__*) ; 
 int /*<<< orphan*/  rtp_stream_thread ; 
 int /*<<< orphan*/ * srtp_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int srtp_setkeystring (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 
 char* strchr (char*,char) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 void* var_CreateGetInteger (int /*<<< orphan*/ *,char*) ; 
 char* var_CreateGetNonEmptyString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_gcrypt_init () ; 
 int /*<<< orphan*/  vlc_strerror_c (int) ; 
 int /*<<< orphan*/  vlc_tick_from_sec (void*) ; 

__attribute__((used)) static int Open (vlc_object_t *obj)
{
    demux_t *demux = (demux_t *)obj;
    int tp; /* transport protocol */

    if (demux->out == NULL)
        return VLC_EGENERIC;

    if (!strcasecmp(demux->psz_name, "dccp"))
        tp = IPPROTO_DCCP;
    else
    if (!strcasecmp(demux->psz_name, "rtptcp"))
        tp = IPPROTO_TCP;
    else
    if (!strcasecmp(demux->psz_name, "rtp"))
        tp = IPPROTO_UDP;
    else
    if (!strcasecmp(demux->psz_name, "udplite"))
        tp = IPPROTO_UDPLITE;
    else
        return VLC_EGENERIC;

    char *tmp = strdup (demux->psz_location);
    if (tmp == NULL)
        return VLC_ENOMEM;

    char *shost;
    char *dhost = strchr (tmp, '@');
    if (dhost != NULL)
    {
        *(dhost++) = '\0';
        shost = tmp;
    }
    else
    {
        dhost = tmp;
        shost = NULL;
    }

    /* Parses the port numbers */
    int sport = 0, dport = 0;
    if (shost != NULL)
        sport = extract_port (&shost);
    if (dhost != NULL)
        dport = extract_port (&dhost);
    if (dport == 0)
        dport = 5004; /* avt-profile-1 port */

    int rtcp_dport = var_CreateGetInteger (obj, "rtcp-port");

    /* Try to connect */
    int fd = -1, rtcp_fd = -1;

    switch (tp)
    {
        case IPPROTO_UDP:
        case IPPROTO_UDPLITE:
            fd = net_OpenDgram (obj, dhost, dport, shost, sport, tp);
            if (fd == -1)
                break;
            if (rtcp_dport > 0) /* XXX: source port is unknown */
                rtcp_fd = net_OpenDgram (obj, dhost, rtcp_dport, shost, 0, tp);
            break;

         case IPPROTO_DCCP:
#ifndef SOCK_DCCP /* provisional API (FIXME) */
# ifdef __linux__
#  define SOCK_DCCP 6
# endif
#endif
#ifdef SOCK_DCCP
            var_Create (obj, "dccp-service", VLC_VAR_STRING);
            var_SetString (obj, "dccp-service", "RTPV"); /* FIXME: RTPA? */
            fd = net_Connect (obj, dhost, dport, SOCK_DCCP, tp);
#else
            msg_Err (obj, "DCCP support not included");
#endif
            break;

        case IPPROTO_TCP:
            fd = net_Connect (obj, dhost, dport, SOCK_STREAM, tp);
            break;
    }

    free (tmp);
    if (fd == -1)
        return VLC_EGENERIC;
    net_SetCSCov (fd, -1, 12);

    /* Initializes demux */
    demux_sys_t *p_sys = malloc (sizeof (*p_sys));
    if (p_sys == NULL)
    {
        net_Close (fd);
        if (rtcp_fd != -1)
            net_Close (rtcp_fd);
        return VLC_EGENERIC;
    }

    p_sys->chained_demux = NULL;
#ifdef HAVE_SRTP
    p_sys->srtp         = NULL;
#endif
    p_sys->fd           = fd;
    p_sys->rtcp_fd      = rtcp_fd;
    p_sys->max_src      = var_CreateGetInteger (obj, "rtp-max-src");
    p_sys->timeout      = vlc_tick_from_sec( var_CreateGetInteger (obj, "rtp-timeout") );
    p_sys->max_dropout  = var_CreateGetInteger (obj, "rtp-max-dropout");
    p_sys->max_misorder = var_CreateGetInteger (obj, "rtp-max-misorder");
    p_sys->thread_ready = false;
    p_sys->autodetect   = true;

    demux->pf_demux   = NULL;
    demux->pf_control = Control;
    demux->p_sys      = p_sys;

    p_sys->session = rtp_session_create (demux);
    if (p_sys->session == NULL)
        goto error;

#ifdef HAVE_SRTP
    char *key = var_CreateGetNonEmptyString (demux, "srtp-key");
    if (key)
    {
        vlc_gcrypt_init ();
        p_sys->srtp = srtp_create (SRTP_ENCR_AES_CM, SRTP_AUTH_HMAC_SHA1, 10,
                                   SRTP_PRF_AES_CM, SRTP_RCC_MODE1);
        if (p_sys->srtp == NULL)
        {
            free (key);
            goto error;
        }

        char *salt = var_CreateGetNonEmptyString (demux, "srtp-salt");
        int val = srtp_setkeystring (p_sys->srtp, key, salt ? salt : "");
        free (salt);
        free (key);
        if (val)
        {
            msg_Err (obj, "bad SRTP key/salt combination (%s)",
                     vlc_strerror_c(val));
            goto error;
        }
    }
#endif

    if (vlc_clone (&p_sys->thread,
                   (tp != IPPROTO_TCP) ? rtp_dgram_thread : rtp_stream_thread,
                   demux, VLC_THREAD_PRIORITY_INPUT))
        goto error;
    p_sys->thread_ready = true;
    return VLC_SUCCESS;

error:
    Close (obj);
    return VLC_EGENERIC;
}