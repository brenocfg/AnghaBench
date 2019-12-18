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
typedef  int /*<<< orphan*/  libvlc_int_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int intf_Create (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  msg_Info (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 

int libvlc_InternalAddIntf(libvlc_int_t *libvlc, const char *name)
{
    int ret;

    if (name != NULL)
        ret = intf_Create(libvlc, name);
    else
    {   /* Default interface */
        char *intf = var_InheritString(libvlc, "intf");
        if (intf == NULL) /* "intf" has not been set */
        {
#if !defined(_WIN32) && !defined(__OS2__)
            if (!var_InheritBool(libvlc, "daemon"))
#endif
                msg_Info(libvlc, _("Running vlc with the default interface. "
                         "Use 'cvlc' to use vlc without interface."));
        }
        ret = intf_Create(libvlc, intf);
        free(intf);
        name = "default";
    }
    if (ret != VLC_SUCCESS)
        msg_Err(libvlc, "interface \"%s\" initialization failed", name);
    return ret;
}