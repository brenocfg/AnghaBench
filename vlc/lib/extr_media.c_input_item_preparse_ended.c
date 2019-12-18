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
typedef  int /*<<< orphan*/  libvlc_media_parsed_status_t ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  enum input_item_preparse_status { ____Placeholder_input_item_preparse_status } input_item_preparse_status ;

/* Variables and functions */
#define  ITEM_PREPARSE_DONE 131 
#define  ITEM_PREPARSE_FAILED 130 
#define  ITEM_PREPARSE_SKIPPED 129 
#define  ITEM_PREPARSE_TIMEOUT 128 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_parsed_status_done ; 
 int /*<<< orphan*/  libvlc_media_parsed_status_failed ; 
 int /*<<< orphan*/  libvlc_media_parsed_status_skipped ; 
 int /*<<< orphan*/  libvlc_media_parsed_status_timeout ; 
 int /*<<< orphan*/  send_parsed_changed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void input_item_preparse_ended(input_item_t *item,
                                      enum input_item_preparse_status status,
                                      void *user_data)
{
    VLC_UNUSED(item);
    libvlc_media_t * p_md = user_data;
    libvlc_media_parsed_status_t new_status;

    switch( status )
    {
        case ITEM_PREPARSE_SKIPPED:
            new_status = libvlc_media_parsed_status_skipped;
            break;
        case ITEM_PREPARSE_FAILED:
            new_status = libvlc_media_parsed_status_failed;
            break;
        case ITEM_PREPARSE_TIMEOUT:
            new_status = libvlc_media_parsed_status_timeout;
            break;
        case ITEM_PREPARSE_DONE:
            new_status = libvlc_media_parsed_status_done;
            break;
        default:
            return;
    }
    send_parsed_changed( p_md, new_status );
}