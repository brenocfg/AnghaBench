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
typedef  int /*<<< orphan*/  LPDIRECTSOUND3DBUFFER ;
typedef  int /*<<< orphan*/  IDirectSound3DBufferImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ IDirectSound3DBufferImpl_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 

HRESULT IDirectSound3DBufferImpl_Destroy(
    IDirectSound3DBufferImpl *pds3db)
{
    TRACE("(%p)\n",pds3db);

    while (IDirectSound3DBufferImpl_Release((LPDIRECTSOUND3DBUFFER)pds3db) > 0);

    return S_OK;
}