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
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IDropTarget ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoUnmarshalInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IDropTarget ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_stream_from_map (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_droptarget_local_handle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static IDropTarget* get_droptarget_pointer(HWND hwnd)
{
    IDropTarget *droptarget = NULL;
    HANDLE map;
    IStream *stream;

    map = get_droptarget_local_handle(hwnd);
    if(!map) return NULL;

    if(SUCCEEDED(create_stream_from_map(map, &stream)))
    {
        CoUnmarshalInterface(stream, &IID_IDropTarget, (void**)&droptarget);
        IStream_Release(stream);
    }
    CloseHandle(map);
    return droptarget;
}