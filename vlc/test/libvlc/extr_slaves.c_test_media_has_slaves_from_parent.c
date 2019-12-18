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
typedef  int /*<<< orphan*/  libvlc_media_slave_t ;
typedef  int /*<<< orphan*/  libvlc_media_list_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLAVES_DIR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* libvlc_media_get_mrl (int /*<<< orphan*/ *) ; 
 int libvlc_media_list_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_list_item_at_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  libvlc_media_list_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_new_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_subitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_parse_sync (int /*<<< orphan*/ *) ; 
 char* path_to_mrl (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_expected_slaves (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
test_media_has_slaves_from_parent(libvlc_instance_t *p_vlc,
                                  const char *psz_main_media,
                                  libvlc_media_slave_t *p_expected_slaves,
                                  unsigned i_expected_slaves)
{
    libvlc_media_t *p_m = libvlc_media_new_path(p_vlc, SLAVES_DIR);
    assert(p_m != NULL);

    printf("Parse media dir to get subitems\n");
    media_parse_sync(p_m);

    char *psz_main_media_mrl = path_to_mrl(p_vlc, psz_main_media);
    assert(psz_main_media_mrl != NULL);
    printf("Main media mrl: '%s'\n", psz_main_media_mrl);

    printf("Fetch main media from subitems\n");
    libvlc_media_list_t *p_ml = libvlc_media_subitems(p_m);
    assert(p_ml != NULL);
    libvlc_media_list_lock(p_ml);
    int i_count = libvlc_media_list_count(p_ml);
    assert(i_count > 0);
    libvlc_media_t *p_subm = NULL;
    for (int i = 0; i < i_count; ++i)
    {
        p_subm = libvlc_media_list_item_at_index(p_ml, i);
        assert(p_subm != NULL);
        char *psz_mrl = libvlc_media_get_mrl(p_subm);
        assert(psz_mrl != NULL);
        if (strcmp(psz_main_media_mrl, psz_mrl) == 0)
        {
            printf("Found main media\n");
            free(psz_mrl);
            break;
        }
        free(psz_mrl);
        libvlc_media_release(p_subm);
        p_subm = NULL;
    }
    free(psz_main_media_mrl);
    libvlc_media_list_unlock(p_ml);
    libvlc_media_list_release(p_ml);

    assert(p_subm != NULL);
    test_expected_slaves(p_subm, p_expected_slaves, i_expected_slaves);
    libvlc_media_release(p_subm);

    libvlc_media_release(p_m);
}