#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  (* convert ) (TYPE_1__*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,void**) ;} ;
struct TYPE_10__ {int fdwConvert; void* cbDstLengthUsed; void* cbSrcLengthUsed; int /*<<< orphan*/  pbDst; int /*<<< orphan*/  pbSrc; void* cbDstLength; void* cbSrcLength; } ;
struct TYPE_9__ {scalar_t__ dwDriver; } ;
typedef  TYPE_1__* PACMDRVSTREAMINSTANCE ;
typedef  TYPE_2__* PACMDRVSTREAMHEADER ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  void* DWORD ;
typedef  TYPE_3__ AcmMpeg3Data ;

/* Variables and functions */
 int ACM_STREAMCONVERTF_BLOCKALIGN ; 
 int ACM_STREAMCONVERTF_END ; 
 int ACM_STREAMCONVERTF_START ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MPEG3_Reset (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static LRESULT MPEG3_StreamConvert(PACMDRVSTREAMINSTANCE adsi, PACMDRVSTREAMHEADER adsh)
{
    AcmMpeg3Data*	aad = (AcmMpeg3Data*)adsi->dwDriver;
    DWORD		nsrc = adsh->cbSrcLength;
    DWORD		ndst = adsh->cbDstLength;

    if (adsh->fdwConvert &
	~(ACM_STREAMCONVERTF_BLOCKALIGN|
	  ACM_STREAMCONVERTF_END|
	  ACM_STREAMCONVERTF_START))
    {
	FIXME("Unsupported fdwConvert (%08x), ignoring it\n", adsh->fdwConvert);
    }
    /* ACM_STREAMCONVERTF_BLOCKALIGN
     *	currently all conversions are block aligned, so do nothing for this flag
     * ACM_STREAMCONVERTF_END
     *	no pending data, so do nothing for this flag
     */
    if ((adsh->fdwConvert & ACM_STREAMCONVERTF_START))
    {
        MPEG3_Reset(adsi, aad);
    }

    aad->convert(adsi, adsh->pbSrc, &nsrc, adsh->pbDst, &ndst);
    adsh->cbSrcLengthUsed = nsrc;
    adsh->cbDstLengthUsed = ndst;

    return MMSYSERR_NOERROR;
}