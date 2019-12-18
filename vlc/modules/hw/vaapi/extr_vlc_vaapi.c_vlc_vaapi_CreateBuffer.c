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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  VADisplay ;
typedef  int /*<<< orphan*/  VAContextID ;
typedef  int /*<<< orphan*/  VABufferType ;
typedef  int /*<<< orphan*/  VABufferID ;

/* Variables and functions */
 int /*<<< orphan*/  VA_CALL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VA_INVALID_ID ; 
 int /*<<< orphan*/  vaCreateBuffer ; 

VABufferID
vlc_vaapi_CreateBuffer(vlc_object_t *o, VADisplay dpy, VAContextID ctx,
                       VABufferType type, unsigned int size,
                       unsigned int num_elements, void *data)
{
    VABufferID buf_id;
    VA_CALL(o, vaCreateBuffer, dpy, ctx, type,
            size, num_elements, data, &buf_id);
    return buf_id;
error: return VA_INVALID_ID;
}