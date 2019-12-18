#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  void* xcb_window_t ;
typedef  int /*<<< orphan*/  xcb_intern_atom_cookie_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  void* xcb_atom_t ;
struct TYPE_15__ {char* x11; } ;
struct TYPE_14__ {void* xid; } ;
struct TYPE_17__ {TYPE_5__* sys; int /*<<< orphan*/ * ops; TYPE_2__ display; TYPE_1__ handle; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ vout_window_t ;
struct TYPE_16__ {int /*<<< orphan*/ * ctx; } ;
struct TYPE_18__ {int /*<<< orphan*/  thread; void* motif_wm_hints; void* wm_state_fullscreen; void* wm_state_below; void* wm_state_above; void* wm_state; TYPE_3__ xkb; void* root; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_5__ vout_window_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DeinitKeyboardExtension (TYPE_4__*) ; 
 int /*<<< orphan*/  InitKeyboardExtension (TYPE_4__*) ; 
 int /*<<< orphan*/  Thread ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_4__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
 int /*<<< orphan*/  VOUT_WINDOW_TYPE_XID ; 
 int /*<<< orphan*/  XA_STRING ; 
 int /*<<< orphan*/  XA_WM_CLASS ; 
 void* XA_WM_ICON_NAME ; 
 void* XA_WM_NAME ; 
 int /*<<< orphan*/  XCB_PROP_MODE_REPLACE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* get_atom (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intern_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ops ; 
 int /*<<< orphan*/  set_ascii_prop (int /*<<< orphan*/ *,void*,void*,char*) ; 
 int /*<<< orphan*/  set_hostname_prop (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  set_string (int /*<<< orphan*/ *,void*,void*,void*,char*) ; 
 int /*<<< orphan*/  set_wm_hints (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ var_InheritBool (TYPE_4__*,char*) ; 
 char* var_InheritString (TYPE_4__*,char*) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* vlc_obj_malloc (int /*<<< orphan*/ ,int) ; 
 char* vlc_pgettext (char*,char*) ; 
 int /*<<< orphan*/  xcb_change_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*) ; 

__attribute__((used)) static int OpenCommon(vout_window_t *wnd, char *display,
                      xcb_connection_t *conn,
                      xcb_window_t root, xcb_window_t window)
{
    vout_window_sys_t *sys = vlc_obj_malloc(VLC_OBJECT(wnd), sizeof (*sys));
    if (sys == NULL)
        return VLC_ENOMEM;

    wnd->type = VOUT_WINDOW_TYPE_XID;
    wnd->handle.xid = window;
    wnd->display.x11 = display;
    wnd->ops = &ops;
    wnd->sys = sys;

    sys->conn = conn;
    sys->root = root;

#ifdef HAVE_XKBCOMMON
    if (var_InheritBool(wnd, "keyboard-events"))
        InitKeyboardExtension(wnd);
    else
        sys->xkb.ctx = NULL;
#endif

    /* ICCCM */
    /* No cut&paste nor drag&drop, only Window Manager communication. */
    set_ascii_prop(conn, window, XA_WM_NAME,
    /* xgettext: This is a plain ASCII spelling of "VLC media player"
       for the ICCCM window name. This must be pure ASCII.
       The limitation is partially with ICCCM and partially with VLC.
       For Latin script languages, you may need to strip accents.
       For other scripts, you will need to transliterate into Latin. */
                   vlc_pgettext("ASCII", "VLC media player"));

    set_ascii_prop(conn, window, XA_WM_ICON_NAME,
    /* xgettext: This is a plain ASCII spelling of "VLC"
       for the ICCCM window name. This must be pure ASCII. */
                   vlc_pgettext("ASCII", "VLC"));

    set_wm_hints(conn, window);
    xcb_change_property(conn, XCB_PROP_MODE_REPLACE, window, XA_WM_CLASS,
                        XA_STRING, 8, 8, "vlc\0Vlc");
    set_hostname_prop(conn, window);

    /* EWMH */
    xcb_intern_atom_cookie_t utf8_string_ck =
        intern_string(conn, "UTF8_STRING");
    xcb_intern_atom_cookie_t net_wm_name_ck =
        intern_string(conn, "_NET_WM_NAME");
    xcb_intern_atom_cookie_t net_wm_icon_name_ck =
        intern_string(conn, "_NET_WM_ICON_NAME");
    xcb_intern_atom_cookie_t wm_window_role_ck =
        intern_string(conn, "WM_WINDOW_ROLE");
    xcb_intern_atom_cookie_t wm_state_ck =
        intern_string(conn, "_NET_WM_STATE");
    xcb_intern_atom_cookie_t wm_state_above_ck =
        intern_string(conn, "_NET_WM_STATE_ABOVE");
    xcb_intern_atom_cookie_t wm_state_below_ck =
        intern_string(conn, "_NET_WM_STATE_BELOW");
    xcb_intern_atom_cookie_t wm_state_fs_ck =
        intern_string(conn, "_NET_WM_STATE_FULLSCREEN");
    xcb_intern_atom_cookie_t motif_wm_hints_ck =
        intern_string(conn, "_MOTIF_WM_HINTS");

    xcb_atom_t utf8 = get_atom(conn, utf8_string_ck);
    xcb_atom_t net_wm_name = get_atom(conn, net_wm_name_ck);
    char *title = var_InheritString(wnd, "video-title");

    if (title != NULL)
    {
        set_string(conn, window, utf8, net_wm_name, title);
        free(title);
    }
    else
        set_string(conn, window, utf8, net_wm_name, _("VLC media player"));

    xcb_atom_t net_wm_icon_name = get_atom(conn, net_wm_icon_name_ck);
    set_string(conn, window, utf8, net_wm_icon_name, _("VLC"));

    xcb_atom_t wm_window_role = get_atom(conn, wm_window_role_ck);
    set_ascii_prop(conn, window, wm_window_role, "vlc-video");

    /* Cache any EWMH atom we may need later */
    sys->wm_state = get_atom(conn, wm_state_ck);
    sys->wm_state_above = get_atom(conn, wm_state_above_ck);
    sys->wm_state_below = get_atom(conn, wm_state_below_ck);
    sys->wm_state_fullscreen = get_atom(conn, wm_state_fs_ck);
    sys->motif_wm_hints = get_atom(conn, motif_wm_hints_ck);

    /* Create the event thread. It will dequeue all events, so any checked
     * request from this thread must be completed at this point. */
    if (vlc_clone(&sys->thread, Thread, wnd, VLC_THREAD_PRIORITY_LOW))
    {
        DeinitKeyboardExtension(wnd);
        return VLC_ENOMEM;
    }

    return VLC_SUCCESS;
}