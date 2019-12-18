#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  event_data; void* data_2; void* data_1; int /*<<< orphan*/  event; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; TYPE_2__** pp_last_event; } ;
typedef  TYPE_1__ OmxEventQueue ;
typedef  TYPE_2__ OmxEvent ;
typedef  void* OMX_U32 ;
typedef  int /*<<< orphan*/  OMX_PTR ;
typedef  int /*<<< orphan*/  OMX_EVENTTYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  OMX_ErrorInsufficientResources ; 
 int /*<<< orphan*/  OMX_ErrorNone ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

OMX_ERRORTYPE PostOmxEvent(OmxEventQueue *queue, OMX_EVENTTYPE event,
    OMX_U32 data_1, OMX_U32 data_2, OMX_PTR event_data)
{
    OmxEvent *p_event;

    p_event = malloc(sizeof(OmxEvent));
    if(!p_event) return OMX_ErrorInsufficientResources;

    p_event->event = event;
    p_event->data_1 = data_1;
    p_event->data_2 = data_2;
    p_event->event_data = event_data;
    p_event->next = 0;

    vlc_mutex_lock(&queue->mutex);
    *queue->pp_last_event = p_event;
    queue->pp_last_event = &p_event->next;
    vlc_cond_signal(&queue->cond);
    vlc_mutex_unlock(&queue->mutex);
    return OMX_ErrorNone;
}