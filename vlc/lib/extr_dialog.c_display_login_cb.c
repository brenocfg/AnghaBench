#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_dialog_id ;
struct TYPE_4__ {int /*<<< orphan*/  (* pf_display_login ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char const*,char const*,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  data; TYPE_1__ cbs; } ;
struct TYPE_6__ {TYPE_2__ dialog; } ;
typedef  TYPE_3__ libvlc_instance_t ;
typedef  int /*<<< orphan*/  libvlc_dialog_id ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char const*,char const*,int) ; 

__attribute__((used)) static void
display_login_cb(void *p_data, vlc_dialog_id *p_id, const char *psz_title,
                 const char *psz_text, const char *psz_default_username,
                 bool b_ask_store)
{
    libvlc_instance_t *p_instance = p_data;

    p_instance->dialog.cbs.pf_display_login(p_instance->dialog.data,
                                            (libvlc_dialog_id *) p_id,
                                            psz_title, psz_text,
                                            psz_default_username, b_ask_store);
}