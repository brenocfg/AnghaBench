#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vlc_readdir_helper {int dummy; } ;
struct TYPE_6__ {int smb2_type; } ;
struct smb2dirent {int /*<<< orphan*/  name; TYPE_1__ st; } ;
struct access_sys {int /*<<< orphan*/  smb2dir; int /*<<< orphan*/  smb2; } ;
struct TYPE_7__ {struct access_sys* p_sys; } ;
typedef  TYPE_2__ stream_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;

/* Variables and functions */
 int AddItem (TYPE_2__*,struct vlc_readdir_helper*,int /*<<< orphan*/ ,int) ; 
 int ITEM_TYPE_DIRECTORY ; 
 int ITEM_TYPE_FILE ; 
 int ITEM_TYPE_UNKNOWN ; 
#define  SMB2_TYPE_DIRECTORY 129 
#define  SMB2_TYPE_FILE 128 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct smb2dirent* smb2_readdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_readdir_helper_finish (struct vlc_readdir_helper*,int) ; 
 int /*<<< orphan*/  vlc_readdir_helper_init (struct vlc_readdir_helper*,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
DirRead(stream_t *access, input_item_node_t *p_node)
{
    struct access_sys *sys = access->p_sys;
    struct smb2dirent *smb2dirent;
    int ret = VLC_SUCCESS;
    assert(sys->smb2dir);

    struct vlc_readdir_helper rdh;
    vlc_readdir_helper_init(&rdh, access, p_node);

    while (ret == VLC_SUCCESS
        && (smb2dirent = smb2_readdir(sys->smb2, sys->smb2dir)) != NULL)
    {
        int i_type;
        switch (smb2dirent->st.smb2_type)
        {
        case SMB2_TYPE_FILE:
            i_type = ITEM_TYPE_FILE;
            break;
        case SMB2_TYPE_DIRECTORY:
            i_type = ITEM_TYPE_DIRECTORY;
            break;
        default:
            i_type = ITEM_TYPE_UNKNOWN;
            break;
        }
        ret = AddItem(access, &rdh, smb2dirent->name, i_type);
    }

    vlc_readdir_helper_finish(&rdh, ret == VLC_SUCCESS);

    return ret;
}