#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stgmed_obj_t ;
struct TYPE_9__ {TYPE_2__* buf; int /*<<< orphan*/  IStream_iface; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pstm; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pUnkForRelease; TYPE_1__ u; int /*<<< orphan*/  tymed; } ;
struct TYPE_7__ {int /*<<< orphan*/  IUnknown_iface; } ;
typedef  TYPE_3__ STGMEDIUM ;
typedef  TYPE_4__ ProtocolStream ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TYMED_ISTREAM ; 

__attribute__((used)) static HRESULT stgmed_stream_fill_stgmed(stgmed_obj_t *obj, STGMEDIUM *stgmed)
{
    ProtocolStream *stream = (ProtocolStream*)obj;

    stgmed->tymed = TYMED_ISTREAM;
    stgmed->u.pstm = &stream->IStream_iface;
    stgmed->pUnkForRelease = &stream->buf->IUnknown_iface;

    return S_OK;
}