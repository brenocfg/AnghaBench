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
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_6__ {int i_ref; int i_max_size; int b_own; TYPE_1__* vt; int /*<<< orphan*/ * p_block; } ;
struct TYPE_5__ {int /*<<< orphan*/  GetBufferAndLength; int /*<<< orphan*/  GetMaxLength; int /*<<< orphan*/  SetLength; int /*<<< orphan*/  Release; int /*<<< orphan*/  AddRef; int /*<<< orphan*/  QueryInterface; } ;
typedef  TYPE_1__ IMediaBuffer_vt ;
typedef  TYPE_2__ CMediaBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef ; 
 int /*<<< orphan*/  GetBufferAndLength ; 
 int /*<<< orphan*/  GetMaxLength ; 
 int /*<<< orphan*/  QueryInterface ; 
 int /*<<< orphan*/  Release ; 
 int /*<<< orphan*/  SetLength ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ malloc (int) ; 

CMediaBuffer *CMediaBufferCreate( block_t *p_block, int i_max_size,
                                  bool b_own )
{
    CMediaBuffer *p_mb = (CMediaBuffer *)malloc( sizeof(CMediaBuffer) );
    if( !p_mb ) return NULL;

    p_mb->vt = (IMediaBuffer_vt *)malloc( sizeof(IMediaBuffer_vt) );
    if( !p_mb->vt )
    {
        free( p_mb );
        return NULL;
    }

    p_mb->i_ref = 1;
    p_mb->p_block = p_block;
    p_mb->i_max_size = i_max_size;
    p_mb->b_own = b_own;

    p_mb->vt->QueryInterface = QueryInterface;
    p_mb->vt->AddRef = AddRef;
    p_mb->vt->Release = Release;

    p_mb->vt->SetLength = SetLength;
    p_mb->vt->GetMaxLength = GetMaxLength;
    p_mb->vt->GetBufferAndLength = GetBufferAndLength;

    return p_mb;
}