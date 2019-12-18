#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vlc_stream_attachment_private {int /*<<< orphan*/  attachment; } ;
struct TYPE_4__ {int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_input_attachment_Delete (int /*<<< orphan*/ ) ; 
 struct vlc_stream_attachment_private* vlc_stream_Private (TYPE_1__*) ; 

__attribute__((used)) static void stream_AttachmentDelete(stream_t *s)
{
    struct vlc_stream_attachment_private *sys = vlc_stream_Private(s);

    vlc_input_attachment_Delete(sys->attachment);
    free(s->psz_name);
}