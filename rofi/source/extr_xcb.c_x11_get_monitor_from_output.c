#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_randr_output_t ;
struct TYPE_11__ {scalar_t__ crtc; int /*<<< orphan*/  mm_height; int /*<<< orphan*/  mm_width; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ xcb_randr_get_output_info_reply_t ;
typedef  int /*<<< orphan*/  xcb_randr_get_output_info_cookie_t ;
typedef  TYPE_1__ xcb_randr_get_crtc_info_reply_t ;
typedef  int /*<<< orphan*/  xcb_randr_get_crtc_info_cookie_t ;
struct TYPE_12__ {void* name; int /*<<< orphan*/  mh; int /*<<< orphan*/  mw; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ workarea ;
struct TYPE_13__ {int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 int /*<<< orphan*/  XCB_CURRENT_TIME ; 
 scalar_t__ XCB_NONE ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 void* g_malloc0 (int) ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 
 TYPE_8__* xcb ; 
 int /*<<< orphan*/  xcb_randr_get_crtc_info (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* xcb_randr_get_crtc_info_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_randr_get_output_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xcb_randr_get_output_info_name (TYPE_1__*) ; 
 int xcb_randr_get_output_info_name_length (TYPE_1__*) ; 
 TYPE_1__* xcb_randr_get_output_info_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static workarea * x11_get_monitor_from_output ( xcb_randr_output_t out )
{
    xcb_randr_get_output_info_reply_t  *op_reply;
    xcb_randr_get_crtc_info_reply_t    *crtc_reply;
    xcb_randr_get_output_info_cookie_t it = xcb_randr_get_output_info ( xcb->connection, out, XCB_CURRENT_TIME );
    op_reply = xcb_randr_get_output_info_reply ( xcb->connection, it, NULL );
    if ( op_reply->crtc == XCB_NONE ) {
        free ( op_reply );
        return NULL;
    }
    xcb_randr_get_crtc_info_cookie_t ct = xcb_randr_get_crtc_info ( xcb->connection, op_reply->crtc, XCB_CURRENT_TIME );
    crtc_reply = xcb_randr_get_crtc_info_reply ( xcb->connection, ct, NULL );
    if ( !crtc_reply ) {
        free ( op_reply );
        return NULL;
    }
    workarea *retv = g_malloc0 ( sizeof ( workarea ) );
    retv->x = crtc_reply->x;
    retv->y = crtc_reply->y;
    retv->w = crtc_reply->width;
    retv->h = crtc_reply->height;

    retv->mw = op_reply->mm_width;
    retv->mh = op_reply->mm_height;

    char *tname    = (char *) xcb_randr_get_output_info_name ( op_reply );
    int  tname_len = xcb_randr_get_output_info_name_length ( op_reply );

    retv->name = g_malloc0 ( ( tname_len + 1 ) * sizeof ( char ) );
    memcpy ( retv->name, tname, tname_len );

    free ( crtc_reply );
    free ( op_reply );
    return retv;
}