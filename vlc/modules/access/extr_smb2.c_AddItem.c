#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vlc_readdir_helper {int dummy; } ;
struct access_sys {int /*<<< orphan*/  encoded_url; } ;
struct TYPE_3__ {struct access_sys* p_sys; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  ITEM_NET ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  free (char*) ; 
 int vlc_readdir_helper_additem (struct vlc_readdir_helper*,char*,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 char* vlc_smb2_get_url (int /*<<< orphan*/ *,char*) ; 
 char* vlc_uri_encode (char const*) ; 

__attribute__((used)) static int AddItem(stream_t *access, struct vlc_readdir_helper *rdh,
                   const char *name, int i_type)
{
    struct access_sys *sys = access->p_sys;
    char *name_encoded = vlc_uri_encode(name);
    if (name_encoded == NULL)
        return VLC_ENOMEM;

    char *url = vlc_smb2_get_url(&sys->encoded_url, name_encoded);
    free(name_encoded);
    if (url == NULL)
        return VLC_ENOMEM;

    int ret = vlc_readdir_helper_additem(rdh, url, NULL, name, i_type,
                                         ITEM_NET);
    free(url);
    return ret;
}