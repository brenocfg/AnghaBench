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
typedef  int /*<<< orphan*/  libvlc_media_t ;
typedef  int /*<<< orphan*/  libvlc_media_list_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int libvlc_media_list_add_media (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int libvlc_media_list_count (int /*<<< orphan*/ *) ; 
 int libvlc_media_list_index_of_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int libvlc_media_list_insert_media (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * libvlc_media_list_item_at_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * libvlc_media_list_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_release (int /*<<< orphan*/ *) ; 
 int libvlc_media_list_remove_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * libvlc_media_new_path (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_new (int,char const**) ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_log (char*) ; 

__attribute__((used)) static void test_media_list (const char ** argv, int argc)
{
    libvlc_instance_t *vlc;
    libvlc_media_t *md, *md1, *md2, *md3, *md4;
    libvlc_media_list_t *ml;
    int ret;

    test_log ("Testing media_list\n");

    vlc = libvlc_new (argc, argv);
    assert (vlc != NULL);

    ml = libvlc_media_list_new (vlc);
    assert (ml != NULL);

    md1 = libvlc_media_new_path (vlc, "/dev/null");
    assert (md1 != NULL);
    md2 = libvlc_media_new_path (vlc, "/dev/null");
    assert (md2 != NULL);
    md3 = libvlc_media_new_path (vlc, "/dev/null");
    assert (md3 != NULL);

    ret = libvlc_media_list_add_media (ml, md1);
    assert (!ret);
    ret = libvlc_media_list_add_media (ml, md2);
    assert (!ret);

    assert( libvlc_media_list_count (ml) == 2 );
    assert( libvlc_media_list_index_of_item (ml, md1) == 0 );
    assert( libvlc_media_list_index_of_item (ml, md2) == 1 );

    ret = libvlc_media_list_remove_index (ml, 0);  /* removing first item */
    assert (!ret);

    /* test if second item was moved on first place */
    assert( libvlc_media_list_index_of_item (ml, md2) == 0 );
    ret = libvlc_media_list_add_media (ml, md1); /* add 2 items */
    assert (!ret);
    ret = libvlc_media_list_add_media (ml, md1);
    assert (!ret);

    /* there should be 3 pieces */
    assert( libvlc_media_list_count (ml) == 3 );

    ret = libvlc_media_list_insert_media (ml, md3, 2);
    assert (!ret);

    /* there should be 4 pieces */
    assert( libvlc_media_list_count (ml) == 4 );

    /* test inserting on right place */
    assert( libvlc_media_list_index_of_item (ml, md3) == 2 );

    /* test right returning descriptor*/
    md = libvlc_media_list_item_at_index (ml, 0);
    assert(md == md2);
    libvlc_media_release(md);

    md = libvlc_media_list_item_at_index (ml, 2);
    assert(md == md3);
    libvlc_media_release(md);

    /* test if give errors, when it should */
    /* have 4 items, so index 4 should give error */
    ret = libvlc_media_list_remove_index (ml, 4);
    assert (ret == -1);

    ret = libvlc_media_list_remove_index (ml, 100);
    assert (ret == -1);

    ret = libvlc_media_list_remove_index (ml, -1);
    assert (ret == -1);

    /* getting non valid items */
    libvlc_media_t * p_non_exist =
        libvlc_media_list_item_at_index (ml, 4);
    assert (p_non_exist == NULL);

    p_non_exist = libvlc_media_list_item_at_index (ml, 100);
    assert (p_non_exist == NULL);

    p_non_exist = libvlc_media_list_item_at_index (ml, -1);
    assert (p_non_exist == NULL);

    md4 = libvlc_media_new_path (vlc, "/dev/null");
    assert (md4 != NULL);

    /* try to find non inserted item */
    int i_non_exist = 0;
    i_non_exist = libvlc_media_list_index_of_item (ml, md4);
    assert ( i_non_exist == -1 );

    libvlc_media_release (md1);
    libvlc_media_release (md2);
    libvlc_media_release (md3);
    libvlc_media_release (md4);

    libvlc_media_list_release (ml);

    libvlc_release (vlc);
}