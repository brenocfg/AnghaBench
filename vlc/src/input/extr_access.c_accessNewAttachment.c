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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {scalar_t__ psz_url; scalar_t__ psz_location; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  input_thread_t ;
typedef  int /*<<< orphan*/  input_attachment_t ;

/* Variables and functions */
 int /*<<< orphan*/ * input_GetAttachment (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strdup (char const*) ; 
 int /*<<< orphan*/  vlc_input_attachment_Delete (int /*<<< orphan*/ *) ; 
 TYPE_1__* vlc_stream_AttachmentNew (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_stream_Delete (TYPE_1__*) ; 

__attribute__((used)) static stream_t *accessNewAttachment(vlc_object_t *parent,
                                     input_thread_t *input, const char *mrl)
{
    if (!input)
        return NULL;

    input_attachment_t *attachment = input_GetAttachment(input, mrl + 13);
    if (!attachment)
        return NULL;
    stream_t *stream = vlc_stream_AttachmentNew(parent, attachment);
    if (!stream)
    {
        vlc_input_attachment_Delete(attachment);
        return NULL;
    }
    stream->psz_url = strdup(mrl);
    if (!stream->psz_url)
    {
        vlc_stream_Delete(stream);
        return NULL;
    }
    stream->psz_location = stream->psz_url + 13;
    return stream;
}