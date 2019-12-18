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
struct vlc_readdir_helper {size_t i_slaves; size_t i_dirs; struct rdh_slave** pp_dirs; struct rdh_slave** pp_slaves; struct rdh_slave* psz_ignored_exts; int /*<<< orphan*/  p_node; } ;
struct rdh_slave {struct rdh_slave* psz_filename; int /*<<< orphan*/  p_slave; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_CLEAN (size_t,struct rdh_slave**) ; 
 int /*<<< orphan*/  free (struct rdh_slave*) ; 
 int /*<<< orphan*/  input_item_slave_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdh_attach_slaves (struct vlc_readdir_helper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdh_sort (int /*<<< orphan*/ ) ; 

void vlc_readdir_helper_finish(struct vlc_readdir_helper *p_rdh, bool b_success)
{
    if (b_success)
    {
        rdh_sort(p_rdh->p_node);
        rdh_attach_slaves(p_rdh, p_rdh->p_node);
    }
    free(p_rdh->psz_ignored_exts);

    /* Remove unmatched slaves */
    for (size_t i = 0; i < p_rdh->i_slaves; i++)
    {
        struct rdh_slave *p_rdh_slave = p_rdh->pp_slaves[i];
        if (p_rdh_slave != NULL)
        {
            input_item_slave_Delete(p_rdh_slave->p_slave);
            free(p_rdh_slave->psz_filename);
            free(p_rdh_slave);
        }
    }
    TAB_CLEAN(p_rdh->i_slaves, p_rdh->pp_slaves);

    for (size_t i = 0; i < p_rdh->i_dirs; i++)
        free(p_rdh->pp_dirs[i]);
    TAB_CLEAN(p_rdh->i_dirs, p_rdh->pp_dirs);
}