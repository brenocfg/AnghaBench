#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vlc_readdir_helper {size_t i_dirs; struct rdh_dir** pp_dirs; } ;
struct rdh_dir {char* psz_path; TYPE_1__* p_node; } ;
typedef  int /*<<< orphan*/  input_item_t ;
struct TYPE_5__ {int /*<<< orphan*/  p_item; } ;
typedef  TYPE_1__ input_item_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_DURATION_UNSET ; 
 int /*<<< orphan*/  INPUT_ITEM_URI_NOP ; 
 int /*<<< orphan*/  ITEM_TYPE_DIRECTORY ; 
 int /*<<< orphan*/  TAB_APPEND (size_t,struct rdh_dir**,struct rdh_dir*) ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct rdh_dir*) ; 
 int /*<<< orphan*/  input_item_CopyOptions (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * input_item_NewExt (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 TYPE_1__* input_item_node_AppendItem (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct rdh_dir* malloc (int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int rdh_unflatten(struct vlc_readdir_helper *p_rdh,
                         input_item_node_t **pp_node, const char *psz_path,
                         int i_net)
{
    /* Create an input input for each sub folders that is contained in the full
     * path. Update pp_node to point to the direct parent of the future item to
     * add. */

    assert(psz_path != NULL);
    const char *psz_subpaths = psz_path;

    while ((psz_subpaths = strchr(psz_subpaths, '/')))
    {
        input_item_node_t *p_subnode = NULL;

        /* Check if this sub folder item was already added */
        for (size_t i = 0; i < p_rdh->i_dirs && p_subnode == NULL; i++)
        {
            struct rdh_dir *rdh_dir = p_rdh->pp_dirs[i];
            if (!strncmp(rdh_dir->psz_path, psz_path, psz_subpaths - psz_path))
                p_subnode = rdh_dir->p_node;
        }

        /* The sub folder item doesn't exist, so create it */
        if (p_subnode == NULL)
        {
            size_t i_sub_path_len = psz_subpaths - psz_path;
            struct rdh_dir *p_rdh_dir =
                malloc(sizeof(struct rdh_dir) + 1 + i_sub_path_len);
            if (p_rdh_dir == NULL)
                return VLC_ENOMEM;
            strncpy(p_rdh_dir->psz_path, psz_path, i_sub_path_len);
            p_rdh_dir->psz_path[i_sub_path_len] = 0;

            const char *psz_subpathname = strrchr(p_rdh_dir->psz_path, '/');
            if (psz_subpathname != NULL)
                ++psz_subpathname;
            else
                psz_subpathname = p_rdh_dir->psz_path;

            input_item_t *p_item =
                input_item_NewExt(INPUT_ITEM_URI_NOP, psz_subpathname, INPUT_DURATION_UNSET,
                                  ITEM_TYPE_DIRECTORY, i_net);
            if (p_item == NULL)
            {
                free(p_rdh_dir);
                return VLC_ENOMEM;
            }
            input_item_CopyOptions(p_item, (*pp_node)->p_item);
            *pp_node = input_item_node_AppendItem(*pp_node, p_item);
            input_item_Release(p_item);
            if (*pp_node == NULL)
            {
                free(p_rdh_dir);
                return VLC_ENOMEM;
            }
            p_rdh_dir->p_node = *pp_node;
            TAB_APPEND(p_rdh->i_dirs, p_rdh->pp_dirs, p_rdh_dir);
        }
        else
            *pp_node = p_subnode;
        psz_subpaths++;
    }
    return VLC_SUCCESS;
}