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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {TYPE_1__* pwfx; } ;
struct TYPE_8__ {TYPE_2__* pwfx; int /*<<< orphan*/  (* convert ) (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_4__* device; } ;
struct TYPE_7__ {int wBitsPerSample; int nChannels; } ;
struct TYPE_6__ {int wBitsPerSample; int nChannels; } ;
typedef  int INT ;
typedef  TYPE_3__ IDirectSoundBufferImpl ;
typedef  TYPE_4__ DirectSoundDevice ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (char*,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cp_fields(const IDirectSoundBufferImpl *dsb, const BYTE *ibuf, BYTE *obuf,
        UINT istride, UINT ostride, UINT count, UINT freqAcc, UINT adj)
{
    DirectSoundDevice *device = dsb->device;
    INT istep = dsb->pwfx->wBitsPerSample / 8, ostep = device->pwfx->wBitsPerSample / 8;

    if (device->pwfx->nChannels == dsb->pwfx->nChannels ||
        (device->pwfx->nChannels == 2 && dsb->pwfx->nChannels == 6) ||
        (device->pwfx->nChannels == 8 && dsb->pwfx->nChannels == 2) ||
        (device->pwfx->nChannels == 6 && dsb->pwfx->nChannels == 2)) {
        dsb->convert(ibuf, obuf, istride, ostride, count, freqAcc, adj);
        if (device->pwfx->nChannels == 2 || dsb->pwfx->nChannels == 2)
            dsb->convert(ibuf + istep, obuf + ostep, istride, ostride, count, freqAcc, adj);
        return;
    }

    if (device->pwfx->nChannels == 1 && dsb->pwfx->nChannels == 2)
    {
        dsb->convert(ibuf, obuf, istride, ostride, count, freqAcc, adj);
        return;
    }

    if (device->pwfx->nChannels == 2 && dsb->pwfx->nChannels == 1)
    {
        dsb->convert(ibuf, obuf, istride, ostride, count, freqAcc, adj);
        dsb->convert(ibuf, obuf + ostep, istride, ostride, count, freqAcc, adj);
        return;
    }

    WARN("Unable to remap channels: device=%u, buffer=%u\n", device->pwfx->nChannels,
            dsb->pwfx->nChannels);
}