#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tls_t ;
struct TYPE_8__ {int /*<<< orphan*/  p_context; } ;
typedef  TYPE_1__ vlc_tls_st_t ;
struct TYPE_9__ {int /*<<< orphan*/  sys; } ;
typedef  TYPE_2__ vlc_tls_client_t ;
typedef  scalar_t__ OSStatus ;
typedef  int /*<<< orphan*/ * CFMutableArrayRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ SSLSetALPNProtocols (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SSLSetEnableCertVerify (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SSLSetPeerDomainName (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ SSLSetSessionOption (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 int /*<<< orphan*/ * alpnToCFArray (char const* const*) ; 
 int /*<<< orphan*/  kSSLSessionOptionBreakOnServerAuth ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,char const*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*) ; 
 scalar_t__ noErr ; 
 int /*<<< orphan*/  st_SessionClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * st_SessionOpenCommon (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  st_SessionShutdown (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static vlc_tls_t *st_ClientSessionOpen(vlc_tls_client_t *crd, vlc_tls_t *sock,
                                 const char *hostname, const char *const *alpn)
{
    msg_Dbg(crd, "open TLS session for %s", hostname);

    vlc_tls_t *tls = st_SessionOpenCommon(VLC_OBJECT(crd), crd->sys, sock,
                                          false);
    if (tls == NULL)
        return NULL;

    vlc_tls_st_t *sys = (vlc_tls_st_t *)tls;

    OSStatus ret = SSLSetPeerDomainName(sys->p_context, hostname, strlen(hostname));
    if (ret != noErr) {
        msg_Err(crd, "cannot set peer domain name");
        goto error;
    }

// Only try to use ALPN on recent enough SDKs
// macOS 10.13.2, iOS 11, tvOS 11, watchOS 4
#if (TARGET_OS_OSX    && MAC_OS_X_VERSION_MAX_ALLOWED     >= 101302) || \
    (TARGET_OS_IPHONE && __IPHONE_OS_VERSION_MAX_ALLOWED  >= 110000) || \
    (TARGET_OS_TV     && __TV_OS_VERSION_MAX_ALLOWED      >= 110000) || \
    (TARGET_OS_WATCH  && __WATCH_OS_VERSION_MAX_ALLOWED   >= 40000)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpartial-availability"

    /* Handle ALPN */
    if (alpn != NULL) {
        if (SSLSetALPNProtocols != NULL) {
            CFMutableArrayRef alpnValues = alpnToCFArray(alpn);

            if (alpnValues == NULL) {
                msg_Err(crd, "cannot create CFMutableArray for ALPN values");
                goto error;
            }

            OSStatus ret = SSLSetALPNProtocols(sys->p_context, alpnValues);
            if (ret != noErr){
                msg_Err(crd, "failed setting ALPN protocols (%i)", ret);
            }
            CFRelease(alpnValues);
        } else {
            msg_Warn(crd, "Ignoring ALPN request due to lack of support in the backend. Proxy behavior potentially undefined.");
        }
    }

#pragma clang diagnostic pop
#else

    /* No ALPN support */
    if (alpn != NULL) {
        // Fallback if SDK does not has SSLSetALPNProtocols
        msg_Warn(crd, "Compiled in SDK without ALPN support. Proxy behavior potentially undefined.");
        #warning ALPN support in your SDK version missing (need 10.13.2), proxy behavior potentially undefined (rdar://29127318, #17721)
    }

#endif

    /* disable automatic validation. We do so manually to also handle invalid
       certificates */

    /* this has effect only on iOS 5 and OSX 10.8 or later ... */
    ret = SSLSetSessionOption(sys->p_context, kSSLSessionOptionBreakOnServerAuth, true);
    if (ret != noErr) {
        msg_Err (crd, "cannot set session option");
        goto error;
    }
#if !TARGET_OS_IPHONE
    /* ... thus calling this for earlier osx versions, which is not available on iOS in turn */
    ret = SSLSetEnableCertVerify(sys->p_context, false);
    if (ret != noErr) {
        msg_Err(crd, "error setting enable cert verify");
        goto error;
    }
#endif

    return tls;

error:
    st_SessionShutdown(tls, true);
    st_SessionClose(tls);
    return NULL;
}