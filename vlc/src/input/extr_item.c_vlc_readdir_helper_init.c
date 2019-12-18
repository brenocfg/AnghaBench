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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct vlc_readdir_helper {int /*<<< orphan*/  pp_dirs; int /*<<< orphan*/  i_dirs; int /*<<< orphan*/  pp_slaves; int /*<<< orphan*/  i_slaves; void* b_flatten; int /*<<< orphan*/  i_sub_autodetect_fuzzy; int /*<<< orphan*/  psz_ignored_exts; void* b_show_hiddenfiles; TYPE_1__* p_node; } ;
struct TYPE_3__ {int /*<<< orphan*/  p_item; } ;
typedef  TYPE_1__ input_item_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_item_ApplyOptions (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  var_InheritInteger (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  var_InheritString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * vlc_object_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_object_delete (int /*<<< orphan*/ *) ; 

void vlc_readdir_helper_init(struct vlc_readdir_helper *p_rdh,
                             vlc_object_t *p_obj, input_item_node_t *p_node)
{
    /* Read options from the parent item. This allows vlc_stream_ReadDir()
     * users to specify options without affecting any exisitng vlc_object_t.
     * Apply options on a temporary object in order to not apply options (which
     * can be insecure) to the current object. */
    vlc_object_t *p_var_obj = vlc_object_create(p_obj, sizeof(vlc_object_t));
    if (p_var_obj != NULL)
    {
        input_item_ApplyOptions(p_var_obj, p_node->p_item);
        p_obj = p_var_obj;
    }

    p_rdh->p_node = p_node;
    p_rdh->b_show_hiddenfiles = var_InheritBool(p_obj, "show-hiddenfiles");
    p_rdh->psz_ignored_exts = var_InheritString(p_obj, "ignore-filetypes");
    bool b_autodetect = var_InheritBool(p_obj, "sub-autodetect-file");
    p_rdh->i_sub_autodetect_fuzzy = !b_autodetect ? 0 :
        var_InheritInteger(p_obj, "sub-autodetect-fuzzy");
    p_rdh->b_flatten = var_InheritBool(p_obj, "extractor-flatten");
    TAB_INIT(p_rdh->i_slaves, p_rdh->pp_slaves);
    TAB_INIT(p_rdh->i_dirs, p_rdh->pp_dirs);

    if (p_var_obj != NULL)
        vlc_object_delete(p_var_obj);
}