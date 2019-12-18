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
struct check_items_order_data {int dummy; } ;
typedef  int /*<<< orphan*/  libvlc_media_t ;
typedef  int /*<<< orphan*/  libvlc_media_list_t ;
typedef  int /*<<< orphan*/  libvlc_media_list_player_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;
typedef  int /*<<< orphan*/  libvlc_event_manager_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_data_init (struct check_items_order_data*) ; 
 int /*<<< orphan*/  check_items_order_callback ; 
 int /*<<< orphan*/  libvlc_MediaListPlayerNextItemSet ; 
 int libvlc_event_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct check_items_order_data*) ; 
 int /*<<< orphan*/  libvlc_media_list_add_media (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_list_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_list_player_event_manager (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_list_player_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_player_play (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_player_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_player_set_media_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_new_as_node (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * libvlc_media_new_path (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * libvlc_media_subitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_new (int,char const**) ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * media_list_add_file_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  queue_expected_item (struct check_items_order_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_and_wait (int /*<<< orphan*/ *) ; 
 char* test_default_sample ; 
 int /*<<< orphan*/  test_log (char*) ; 
 int /*<<< orphan*/  wait_queued_items (struct check_items_order_data*) ; 

__attribute__((used)) static void test_media_list_player_items_queue(const char** argv, int argc)
{
    libvlc_instance_t *vlc;
    libvlc_media_t *md;
    libvlc_media_list_t *ml;
    libvlc_media_list_player_t *mlp;

    const char * file = test_default_sample;

    test_log ("Testing media player item queue-ing\n");

    vlc = libvlc_new (argc, argv);
    assert (vlc != NULL);

    md = libvlc_media_new_path (vlc, file);
    assert(md);

    ml = libvlc_media_list_new (vlc);
    assert (ml != NULL);

    mlp = libvlc_media_list_player_new (vlc);
    assert(mlp);

    libvlc_media_list_add_media (ml, md);

    static struct check_items_order_data check;
    check_data_init(&check);
    queue_expected_item(&check, md);

    // Add three more media
    queue_expected_item(&check, media_list_add_file_path (vlc, ml, file));
    queue_expected_item(&check, media_list_add_file_path (vlc, ml, file));
    queue_expected_item(&check, media_list_add_file_path (vlc, ml, file));

    // Add a node
    libvlc_media_t *node = libvlc_media_new_as_node(vlc, "node");
    assert(node);
    libvlc_media_list_add_media(ml, node);
    queue_expected_item(&check, node);

    // Add items to that node
    libvlc_media_list_t *subitems = libvlc_media_subitems(node);
    queue_expected_item(&check, media_list_add_file_path(vlc, subitems, file));
    queue_expected_item(&check, media_list_add_file_path(vlc, subitems, file));
    queue_expected_item(&check, media_list_add_file_path(vlc, subitems, file));
    libvlc_media_list_release(subitems);

    libvlc_media_list_player_set_media_list (mlp, ml);

    libvlc_event_manager_t * em = libvlc_media_list_player_event_manager(mlp);
    int val = libvlc_event_attach(em, libvlc_MediaListPlayerNextItemSet,
                                  check_items_order_callback, &check);
    assert(val == 0);

    libvlc_media_list_player_play(mlp);

    // Wait until all item are read
    wait_queued_items(&check);

    stop_and_wait (mlp);

    libvlc_media_list_player_release (mlp);
    libvlc_release (vlc);
}