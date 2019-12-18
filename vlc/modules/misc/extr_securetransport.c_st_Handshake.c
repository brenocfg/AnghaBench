#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tls_t ;
struct TYPE_2__ {int b_server_mode; int b_handshaked; int /*<<< orphan*/  obj; scalar_t__ b_blocking_send; int /*<<< orphan*/  p_context; } ;
typedef  TYPE_1__ vlc_tls_st_t ;
typedef  scalar_t__ OSStatus ;
typedef  int /*<<< orphan*/ * CFArrayRef ;

/* Variables and functions */
 char* CFArrayALPNCopyFirst (int /*<<< orphan*/ *) ; 
 scalar_t__ SSLCopyALPNProtocols (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ SSLHandshake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
#define  errSSLConnectionRefused 132 
#define  errSSLFatalAlert 131 
#define  errSSLNegotiation 130 
#define  errSSLServerAuthCompleted 129 
 scalar_t__ errSSLWouldBlock ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,...) ; 
#define  noErr 128 
 int /*<<< orphan*/  st_validateServerCertificate (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_Handshake (vlc_tls_t *session,
                         const char *host, const char *service,
                         char **restrict alp) {

    vlc_tls_st_t *sys = (vlc_tls_st_t *)session;

    VLC_UNUSED(service);

    OSStatus retValue = SSLHandshake(sys->p_context);

// Only try to use ALPN on recent enough SDKs
// macOS 10.13.2, iOS 11, tvOS 11, watchOS 4
#if (TARGET_OS_OSX    && MAC_OS_X_VERSION_MAX_ALLOWED     >= 101302) || \
    (TARGET_OS_IPHONE && __IPHONE_OS_VERSION_MAX_ALLOWED  >= 110000) || \
    (TARGET_OS_TV     && __TV_OS_VERSION_MAX_ALLOWED      >= 110000) || \
    (TARGET_OS_WATCH  && __WATCH_OS_VERSION_MAX_ALLOWED   >= 40000)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpartial-availability"

    /* Handle ALPN data */
    if (alp != NULL) {
        if (SSLCopyALPNProtocols != NULL) {
            CFArrayRef alpnArray = NULL;
            OSStatus res = SSLCopyALPNProtocols(sys->p_context, &alpnArray);
            if (res == noErr && alpnArray) {
                *alp = CFArrayALPNCopyFirst(alpnArray);
                if (unlikely(*alp == NULL))
                    return -1;
            } else {
                *alp = NULL;
            }
        } else {
            *alp = NULL;
        }
    }

#pragma clang diagnostic pop
#else

    /* No ALPN support */
    if (alp != NULL) {
        *alp = NULL;
    }

#endif

    if (retValue == errSSLWouldBlock) {
        msg_Dbg(sys->obj, "handshake is blocked, try again later");
        return 1 + (sys->b_blocking_send ? 1 : 0);
    }

    switch (retValue) {
        case noErr:
            if (sys->b_server_mode == false && st_validateServerCertificate(session, host) != 0) {
                return -1;
            }
            msg_Dbg(sys->obj, "handshake completed successfully");
            sys->b_handshaked = true;
            return 0;

        case errSSLServerAuthCompleted:
            msg_Dbg(sys->obj, "SSLHandshake returned errSSLServerAuthCompleted, continuing handshake");
            return st_Handshake(session, host, service, alp);

        case errSSLConnectionRefused:
            msg_Err(sys->obj, "connection was refused");
            return -1;
        case errSSLNegotiation:
            msg_Err(sys->obj, "cipher suite negotiation failed");
            return -1;
        case errSSLFatalAlert:
            msg_Err(sys->obj, "fatal error occurred during handshake");
            return -1;

        default:
            msg_Err(sys->obj, "handshake returned error %d", (int)retValue);
            return -1;
    }
}