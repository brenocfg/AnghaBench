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
typedef  int vlc_dialog_question_type ;
typedef  int /*<<< orphan*/  libvlc_dialog_question_type ;

/* Variables and functions */
 int /*<<< orphan*/  LIBVLC_DIALOG_QUESTION_CRITICAL ; 
 int /*<<< orphan*/  LIBVLC_DIALOG_QUESTION_NORMAL ; 
 int /*<<< orphan*/  LIBVLC_DIALOG_QUESTION_WARNING ; 
#define  VLC_DIALOG_QUESTION_CRITICAL 130 
#define  VLC_DIALOG_QUESTION_NORMAL 129 
#define  VLC_DIALOG_QUESTION_WARNING 128 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static libvlc_dialog_question_type
vlc_to_libvlc_dialog_question_type(vlc_dialog_question_type i_type)
{
    switch (i_type)
    {
    case VLC_DIALOG_QUESTION_NORMAL: return LIBVLC_DIALOG_QUESTION_NORMAL;
    case VLC_DIALOG_QUESTION_WARNING: return LIBVLC_DIALOG_QUESTION_WARNING;
    case VLC_DIALOG_QUESTION_CRITICAL: return LIBVLC_DIALOG_QUESTION_CRITICAL;
    default: vlc_assert_unreachable();
    }
}