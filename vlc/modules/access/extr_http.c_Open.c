#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_23__ {char* psz_authtype; scalar_t__ psz_password; scalar_t__ psz_username; int /*<<< orphan*/ * psz_realm; } ;
typedef  TYPE_2__ vlc_credential ;
typedef  int uint8_t ;
struct TYPE_24__ {char* psz_url; int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_read; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ stream_t ;
struct TYPE_26__ {char* psz_host; int i_port; char* psz_password; char* psz_path; char* psz_username; } ;
struct TYPE_22__ {scalar_t__ i_nonce; int /*<<< orphan*/ * psz_realm; scalar_t__ psz_nonce; } ;
struct TYPE_25__ {int b_proxy; char* psz_proxy_passbuf; char* psz_mime; int b_icecast; char* psz_location; char* psz_user_agent; char* psz_referrer; char* psz_username; char* psz_password; int b_has_size; int i_code; TYPE_9__ proxy; TYPE_9__ url; scalar_t__ b_reconnect; TYPE_1__ auth; scalar_t__ size; scalar_t__ offset; int /*<<< orphan*/ * psz_icy_title; int /*<<< orphan*/ * psz_icy_genre; int /*<<< orphan*/ * psz_icy_name; scalar_t__ i_icy_offset; scalar_t__ i_icy_meta; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_4__ access_sys_t ;

/* Variables and functions */
 scalar_t__ Connect (TYPE_3__*) ; 
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Disconnect (TYPE_3__*) ; 
 int /*<<< orphan*/  Read ; 
 int /*<<< orphan*/  Seek ; 
 unsigned int UINT_MAX ; 
 int VLC_ACCESS_REDIRECT ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*) ; 
 char* strchr (char*,char) ; 
 void* strdup (scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ var_InheritBool (TYPE_3__*,char*) ; 
 void* var_InheritString (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  vlc_UrlClean (TYPE_9__*) ; 
 scalar_t__ vlc_UrlParse (TYPE_9__*,char const*) ; 
 int /*<<< orphan*/  vlc_credential_clean (TYPE_2__*) ; 
 scalar_t__ vlc_credential_get (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  vlc_credential_init (TYPE_2__*,TYPE_9__*) ; 
 int /*<<< orphan*/  vlc_credential_store (TYPE_2__*,TYPE_3__*) ; 
 char* vlc_getProxyUrl (char const*) ; 
 TYPE_4__* vlc_obj_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    stream_t *p_access = (stream_t*)p_this;
    const char *psz_url = p_access->psz_url;
    char *psz;
    int ret = VLC_EGENERIC;
    vlc_credential credential;

    access_sys_t *p_sys = vlc_obj_malloc( p_this, sizeof(*p_sys) );
    if( unlikely(p_sys == NULL) )
        return VLC_ENOMEM;

    p_sys->stream = NULL;
    p_sys->b_proxy = false;
    p_sys->psz_proxy_passbuf = NULL;
    p_sys->psz_mime = NULL;
    p_sys->b_icecast = false;
    p_sys->psz_location = NULL;
    p_sys->psz_user_agent = NULL;
    p_sys->psz_referrer = NULL;
    p_sys->psz_username = NULL;
    p_sys->psz_password = NULL;
    p_sys->i_icy_meta = 0;
    p_sys->i_icy_offset = 0;
    p_sys->psz_icy_name = NULL;
    p_sys->psz_icy_genre = NULL;
    p_sys->psz_icy_title = NULL;
    p_sys->b_has_size = false;
    p_sys->offset = 0;
    p_sys->size = 0;
    p_access->p_sys = p_sys;

    if( vlc_UrlParse( &p_sys->url, psz_url ) || p_sys->url.psz_host == NULL )
    {
        msg_Err( p_access, "invalid URL" );
        vlc_UrlClean( &p_sys->url );
        return VLC_EGENERIC;
    }
    if( p_sys->url.i_port <= 0 )
        p_sys->url.i_port = 80;

    vlc_credential_init( &credential, &p_sys->url );

    /* Determine the HTTP user agent */
    /* See RFC2616 §2.2 token and comment definition, and §3.8 and
     * §14.43 user-agent header */
    p_sys->psz_user_agent = var_InheritString( p_access, "http-user-agent" );
    if (p_sys->psz_user_agent)
    {
        unsigned comment_level = 0;
        for( char *p = p_sys->psz_user_agent; *p; p++ )
        {
            uint8_t c = *p;
            if (comment_level == 0)
            {
                if( c < 32 || strchr( ")<>@,;:\\\"[]?={}", c ) )
                    *p = '_'; /* remove potentially harmful characters */
            }
            else
            {
                if (c == ')')
                    comment_level--;
                else if( c < 32 && strchr( "\t\r\n", c ) == NULL)
                    *p = '_'; /* remove potentially harmful characters */
            }
            if (c == '(')
            {
                if (comment_level == UINT_MAX)
                    break;
                comment_level++;
            }
        }
        /* truncate evil unclosed comments */
        if (comment_level > 0)
        {
            char *p = strchr(p_sys->psz_user_agent, '(');
            *p = '\0';
        }
    }

    /* HTTP referrer */
    p_sys->psz_referrer = var_InheritString( p_access, "http-referrer" );

    /* Check proxy */
    psz = var_InheritString( p_access, "http-proxy" );
    if( psz == NULL )
    {
        msg_Dbg(p_access, "querying proxy for %s", psz_url);
        psz = vlc_getProxyUrl(psz_url);

        if (psz != NULL)
            msg_Dbg(p_access, "proxy: %s", psz);
        else
            msg_Dbg(p_access, "no proxy");
    }
    if( psz != NULL )
    {
        p_sys->b_proxy = true;
        vlc_UrlParse( &p_sys->proxy, psz );
        free( psz );

        psz = var_InheritString( p_access, "http-proxy-pwd" );
        if( psz )
            p_sys->proxy.psz_password = p_sys->psz_proxy_passbuf = psz;

        if( p_sys->proxy.psz_host == NULL || *p_sys->proxy.psz_host == '\0' )
        {
            msg_Warn( p_access, "invalid proxy host" );
            goto error;
        }
        if( p_sys->proxy.i_port <= 0 )
        {
            p_sys->proxy.i_port = 80;
        }
    }

    msg_Dbg( p_access, "http: server='%s' port=%d file='%s'",
             p_sys->url.psz_host, p_sys->url.i_port,
             p_sys->url.psz_path != NULL ? p_sys->url.psz_path : "" );
    if( p_sys->b_proxy )
    {
        msg_Dbg( p_access, "      proxy %s:%d", p_sys->proxy.psz_host,
                 p_sys->proxy.i_port );
    }
    if( p_sys->url.psz_username && *p_sys->url.psz_username )
    {
        msg_Dbg( p_access, "      user='%s'", p_sys->url.psz_username );
    }

    p_sys->b_reconnect = var_InheritBool( p_access, "http-reconnect" );

    if( vlc_credential_get( &credential, p_access, NULL, NULL, NULL, NULL ) )
    {
        p_sys->url.psz_username = (char *) credential.psz_username;
        p_sys->url.psz_password = (char *) credential.psz_password;
    }

connect:
    /* Connect */
    if( Connect( p_access ) )
        goto disconnect;

    if( p_sys->i_code == 401 )
    {
        if( p_sys->auth.psz_realm == NULL )
        {
            msg_Err( p_access, "authentication failed without realm" );
            goto disconnect;
        }
        /* FIXME ? */
        if( p_sys->url.psz_username && p_sys->url.psz_password &&
            p_sys->auth.psz_nonce && p_sys->auth.i_nonce == 0 )
        {
            Disconnect( p_access );
            goto connect;
        }
        free( p_sys->psz_username );
        free( p_sys->psz_password );
        p_sys->psz_username = p_sys->psz_password = NULL;

        msg_Dbg( p_access, "authentication failed for realm %s",
                 p_sys->auth.psz_realm );

        credential.psz_realm = p_sys->auth.psz_realm;
        credential.psz_authtype = p_sys->auth.psz_nonce  ? "Digest" : "Basic";

        if( vlc_credential_get( &credential, p_access, NULL, NULL,
                               _("HTTP authentication"),
                               _("Please enter a valid login name and a "
                               "password for realm %s."), p_sys->auth.psz_realm ) )
        {
            p_sys->psz_username = strdup(credential.psz_username);
            p_sys->psz_password = strdup(credential.psz_password);
            if (!p_sys->psz_username || !p_sys->psz_password)
                goto disconnect;
            msg_Err( p_access, "retrying with user=%s", p_sys->psz_username );
            p_sys->url.psz_username = p_sys->psz_username;
            p_sys->url.psz_password = p_sys->psz_password;
            Disconnect( p_access );
            goto connect;
        }
        else
            goto disconnect;
    }
    else
        vlc_credential_store( &credential, p_access );

    if( ( p_sys->i_code == 301 || p_sys->i_code == 302 ||
          p_sys->i_code == 303 || p_sys->i_code == 307 ) &&
        p_sys->psz_location != NULL )
    {
        p_access->psz_url = p_sys->psz_location;
        p_sys->psz_location = NULL;
        ret = VLC_ACCESS_REDIRECT;
        goto disconnect;
    }

    if( p_sys->b_reconnect ) msg_Dbg( p_access, "auto re-connect enabled" );

    /* Set up p_access */
    p_access->pf_read = Read;
    p_access->pf_control = Control;
    p_access->pf_seek = Seek;

    vlc_credential_clean( &credential );

    return VLC_SUCCESS;

disconnect:
    Disconnect( p_access );

error:
    vlc_credential_clean( &credential );
    vlc_UrlClean( &p_sys->url );
    if( p_sys->b_proxy )
        vlc_UrlClean( &p_sys->proxy );
    free( p_sys->psz_proxy_passbuf );
    free( p_sys->psz_mime );
    free( p_sys->psz_location );
    free( p_sys->psz_user_agent );
    free( p_sys->psz_referrer );
    free( p_sys->psz_username );
    free( p_sys->psz_password );

    return ret;
}