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
struct TYPE_9__ {TYPE_2__* pwfxSrc; TYPE_1__* pwfxDst; } ;
struct TYPE_8__ {int wSamplesPerBlock; } ;
struct TYPE_7__ {int nBlockAlign; } ;
struct TYPE_6__ {int nBlockAlign; int wBitsPerSample; } ;
typedef  int* LPDWORD ;
typedef  int DWORD ;
typedef  TYPE_3__ ADPCMWAVEFORMAT ;
typedef  int /*<<< orphan*/  ADPCMCOEFSET ;
typedef  TYPE_4__ ACMDRVSTREAMINSTANCE ;

/* Variables and functions */
 unsigned char C168 (int) ; 
 int /*<<< orphan*/ * MSADPCM_CoeffSet ; 
 int R16 (unsigned char const*) ; 
 int /*<<< orphan*/  W16 (unsigned char*,int) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  process_nibble (unsigned char const,int*,int*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static	void cvtSSms16K(const ACMDRVSTREAMINSTANCE *adsi,
                        const unsigned char* src, LPDWORD nsrc,
                        unsigned char* dst, LPDWORD ndst)
{
    int                 ideltaL, ideltaR;
    int                 sample1L, sample2L;
    int                 sample1R, sample2R;
    ADPCMCOEFSET        coeffL, coeffR;
    int                 nsamp;
    int		        nsamp_blk = ((ADPCMWAVEFORMAT*)adsi->pwfxSrc)->wSamplesPerBlock;
    DWORD	        nblock = min(*nsrc / adsi->pwfxSrc->nBlockAlign,
                                     *ndst / (nsamp_blk * adsi->pwfxDst->nBlockAlign));

    *nsrc = nblock * adsi->pwfxSrc->nBlockAlign;
    *ndst = nblock * nsamp_blk * adsi->pwfxDst->nBlockAlign;

    nsamp_blk -= 2; /* see below for samples from block head */
    for (; nblock > 0; nblock--)
    {
        const unsigned char*    in_src = src;

        /* Catch a problem from Tomb Raider III (bug 21000) where it passes
         * invalid data after a valid sequence of blocks */
        if (*src > 6 || *(src + 1) > 6)
        {
            /* Recalculate the amount of used output buffer. We are not changing
             * nsrc, let's assume the bad data was parsed */
            *ndst -= nblock * nsamp_blk * adsi->pwfxDst->nBlockAlign;
            WARN("Invalid ADPCM data, stopping conversion\n");
            break;
        }
        coeffL = MSADPCM_CoeffSet[*src++];
        coeffR = MSADPCM_CoeffSet[*src++];

        ideltaL  = R16(src);    src += 2;
        ideltaR  = R16(src);    src += 2;
        sample1L = R16(src);    src += 2;
        sample1R = R16(src);    src += 2;
        sample2L = R16(src);    src += 2;
        sample2R = R16(src);    src += 2;

        if(adsi->pwfxDst->wBitsPerSample == 8){
            /* store samples from block head */
            *dst = C168(sample2L);      ++dst;
            *dst = C168(sample2R);      ++dst;
            *dst = C168(sample1L);      ++dst;
            *dst = C168(sample1R);      ++dst;

            for (nsamp = nsamp_blk; nsamp > 0; nsamp--)
            {
                process_nibble(*src >> 4, &ideltaL, &sample1L, &sample2L, &coeffL);
                *dst = C168(sample1L); ++dst;
                process_nibble(*src++ & 0x0F, &ideltaR, &sample1R, &sample2R, &coeffR);
                *dst = C168(sample1R); ++dst;
            }
        }else if(adsi->pwfxDst->wBitsPerSample == 16){
            /* store samples from block head */
            W16(dst, sample2L);      dst += 2;
            W16(dst, sample2R);      dst += 2;
            W16(dst, sample1L);      dst += 2;
            W16(dst, sample1R);      dst += 2;

            for (nsamp = nsamp_blk; nsamp > 0; nsamp--)
            {
                process_nibble(*src >> 4, &ideltaL, &sample1L, &sample2L, &coeffL);
                W16(dst, sample1L); dst += 2;
                process_nibble(*src++ & 0x0F, &ideltaR, &sample1R, &sample2R, &coeffR);
                W16(dst, sample1R); dst += 2;
            }
        }
        src = in_src + adsi->pwfxSrc->nBlockAlign;
    }
}