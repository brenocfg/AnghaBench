#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_15__ {long dwCaps; } ;
struct TYPE_16__ {long dwSize; long dwCaps; long dwCaps2; long dwCKeyCaps; long dwFXCaps; long dwFXAlphaCaps; long dwPalCaps; long dwSVCaps; long dwAlphaBltConstBitDepths; long dwAlphaBltPixelBitDepths; long dwAlphaBltSurfaceBitDepths; long dwAlphaOverlayConstBitDepths; long dwAlphaOverlayPixelBitDepths; long dwAlphaOverlaySurfaceBitDepths; long dwZBufferBitDepths; long dwVidMemTotal; long dwVidMemFree; long dwMaxVisibleOverlays; long dwCurrVisibleOverlays; long dwNumFourCCCodes; long dwAlignBoundarySrc; long dwAlignSizeSrc; long dwAlignBoundaryDest; long dwAlignSizeDest; long dwAlignStrideAlign; long dwMinOverlayStretch; long dwMaxOverlayStretch; long dwMinLiveVideoStretch; long dwMaxLiveVideoStretch; long dwMinHwCodecStretch; long dwMaxHwCodecStretch; long dwReserved1; long dwReserved2; long dwReserved3; long dwSVBCaps; long dwSVBCKeyCaps; long dwSVBFXCaps; long dwVSBCaps; long dwVSBCKeyCaps; long dwVSBFXCaps; long dwSSBCaps; long dwSSBCKeyCaps; long dwSSBFXCaps; long dwMaxVideoPorts; long dwCurrVideoPorts; long dwSVBCaps2; int /*<<< orphan*/ * dwSSBRops; int /*<<< orphan*/ * dwVSBRops; int /*<<< orphan*/ * dwSVBRops; TYPE_3__ ddsCaps; int /*<<< orphan*/ * dwRops; } ;
struct TYPE_13__ {scalar_t__ dwRGBAlphaBitMask; scalar_t__ dwBBitMask; scalar_t__ dwGBitMask; scalar_t__ dwRBitMask; scalar_t__ dwRGBBitCount; scalar_t__ dwFourCC; scalar_t__ dwFlags; scalar_t__ dwSize; } ;
struct TYPE_14__ {scalar_t__ pvPrimary; scalar_t__ dwAlphaAlign; scalar_t__ dwZBufferAlign; scalar_t__ dwTextureAlign; scalar_t__ dwOverlayAlign; scalar_t__ dwOffscreenAlign; TYPE_1__ ddpfDisplay; scalar_t__ lDisplayPitch; scalar_t__ dwDisplayHeight; scalar_t__ dwDisplayWidth; scalar_t__ dwFlags; scalar_t__ fpPrimary; } ;
struct TYPE_21__ {scalar_t__ dwFlags; scalar_t__ GetDriverInfo; TYPE_4__ ddCaps; TYPE_2__ vmiData; scalar_t__ dwSize; } ;
struct TYPE_19__ {int /*<<< orphan*/  dwCaps; } ;
struct TYPE_20__ {long dwSize; long dwFXAlphaCaps; long dwPalCaps; long dwAlphaBltConstBitDepths; long dwAlphaBltPixelBitDepths; long dwAlphaBltSurfaceBitDepths; long dwAlphaOverlayConstBitDepths; long dwAlphaOverlayPixelBitDepths; long dwAlphaOverlaySurfaceBitDepths; long dwZBufferBitDepths; long dwVidMemTotal; long dwVidMemFree; long dwMaxVisibleOverlays; long dwCurrVisibleOverlays; long dwNumFourCCCodes; long dwAlignBoundarySrc; long dwAlignSizeSrc; long dwAlignBoundaryDest; long dwAlignSizeDest; long dwAlignStrideAlign; long dwMinOverlayStretch; long dwMaxOverlayStretch; long dwMinLiveVideoStretch; long dwMaxLiveVideoStretch; long dwMinHwCodecStretch; long dwMaxHwCodecStretch; long dwReserved1; long dwReserved2; long dwReserved3; long dwSVBCKeyCaps; long dwSVBFXCaps; long dwVSBCKeyCaps; long dwVSBFXCaps; long dwSSBCaps; long dwSSBCKeyCaps; long dwSSBFXCaps; int /*<<< orphan*/ * dwSSBRops; int /*<<< orphan*/ * dwVSBRops; int /*<<< orphan*/  dwVSBCaps; int /*<<< orphan*/ * dwSVBRops; int /*<<< orphan*/  dwSVBCaps; TYPE_7__ ddsCaps; int /*<<< orphan*/ * dwRops; int /*<<< orphan*/  dwSVCaps; int /*<<< orphan*/  dwFXCaps; int /*<<< orphan*/  dwCKeyCaps; int /*<<< orphan*/  dwCaps2; int /*<<< orphan*/  dwCaps; } ;
struct TYPE_17__ {scalar_t__ dwRGBAlphaBitMask; scalar_t__ dwBBitMask; scalar_t__ dwGBitMask; scalar_t__ dwRBitMask; scalar_t__ dwRGBBitCount; scalar_t__ dwFourCC; scalar_t__ dwFlags; scalar_t__ dwSize; } ;
struct TYPE_18__ {scalar_t__ pvPrimary; scalar_t__ dwAlphaAlign; scalar_t__ dwZBufferAlign; scalar_t__ dwTextureAlign; scalar_t__ dwOverlayAlign; scalar_t__ dwOffscreenAlign; TYPE_5__ ddpfDisplay; scalar_t__ lDisplayPitch; scalar_t__ dwDisplayHeight; scalar_t__ dwDisplayWidth; scalar_t__ dwFlags; scalar_t__ fpPrimary; } ;
struct TYPE_12__ {int dwSize; scalar_t__ lpD3DBufCallbacks; scalar_t__ lpD3DHALCallbacks; scalar_t__ lpD3DGlobalDriverData; int /*<<< orphan*/  dwFlags; scalar_t__ GetDriverInfo; TYPE_8__ ddCaps; TYPE_6__ vmiData; } ;
typedef  scalar_t__ INT ;
typedef  TYPE_9__ DD_HALINFO_V4 ;
typedef  TYPE_10__ DD_HALINFO ;

/* Variables and functions */
 int /*<<< orphan*/  DDCAPS2_AUTOFLIPOVERLAY ; 
 int /*<<< orphan*/  DDCAPS2_CANAUTOGENMIPMAP ; 
 int /*<<< orphan*/  DDCAPS2_CANBOBHARDWARE ; 
 int /*<<< orphan*/  DDCAPS2_CANBOBINTERLEAVED ; 
 int /*<<< orphan*/  DDCAPS2_CANBOBNONINTERLEAVED ; 
 int /*<<< orphan*/  DDCAPS2_CANCALIBRATEGAMMA ; 
 int /*<<< orphan*/  DDCAPS2_CANDROPZ16BIT ; 
 int /*<<< orphan*/  DDCAPS2_CANFLIPODDEVEN ; 
 int /*<<< orphan*/  DDCAPS2_CANMANAGERESOURCE ; 
 int /*<<< orphan*/  DDCAPS2_CANMANAGETEXTURE ; 
 int /*<<< orphan*/  DDCAPS2_CANRENDERWINDOWED ; 
 int /*<<< orphan*/  DDCAPS2_CERTIFIED ; 
 int /*<<< orphan*/  DDCAPS2_COLORCONTROLOVERLAY ; 
 int /*<<< orphan*/  DDCAPS2_COLORCONTROLPRIMARY ; 
 int /*<<< orphan*/  DDCAPS2_COPYFOURCC ; 
 int /*<<< orphan*/  DDCAPS2_FLIPINTERVAL ; 
 int /*<<< orphan*/  DDCAPS2_FLIPNOVSYNC ; 
 int /*<<< orphan*/  DDCAPS2_NO2DDURING3DSCENE ; 
 int /*<<< orphan*/  DDCAPS2_NONLOCALVIDMEM ; 
 int /*<<< orphan*/  DDCAPS2_NONLOCALVIDMEMCAPS ; 
 int /*<<< orphan*/  DDCAPS2_NOPAGELOCKREQUIRED ; 
 int /*<<< orphan*/  DDCAPS2_PRIMARYGAMMA ; 
 int /*<<< orphan*/  DDCAPS2_VIDEOPORT ; 
 int /*<<< orphan*/  DDCAPS2_WIDESURFACES ; 
 int /*<<< orphan*/  DDCAPS_3D ; 
 int /*<<< orphan*/  DDCAPS_ALIGNBOUNDARYDEST ; 
 int /*<<< orphan*/  DDCAPS_ALIGNBOUNDARYSRC ; 
 int /*<<< orphan*/  DDCAPS_ALIGNSIZEDEST ; 
 int /*<<< orphan*/  DDCAPS_ALIGNSIZESRC ; 
 int /*<<< orphan*/  DDCAPS_ALIGNSTRIDE ; 
 int /*<<< orphan*/  DDCAPS_ALPHA ; 
 int /*<<< orphan*/  DDCAPS_BANKSWITCHED ; 
 int /*<<< orphan*/  DDCAPS_BLT ; 
 int /*<<< orphan*/  DDCAPS_BLTCOLORFILL ; 
 int /*<<< orphan*/  DDCAPS_BLTDEPTHFILL ; 
 int /*<<< orphan*/  DDCAPS_BLTFOURCC ; 
 int /*<<< orphan*/  DDCAPS_BLTQUEUE ; 
 int /*<<< orphan*/  DDCAPS_BLTSTRETCH ; 
 int /*<<< orphan*/  DDCAPS_CANBLTSYSMEM ; 
 int /*<<< orphan*/  DDCAPS_CANCLIP ; 
 int /*<<< orphan*/  DDCAPS_CANCLIPSTRETCHED ; 
 int /*<<< orphan*/  DDCAPS_COLORKEY ; 
 int /*<<< orphan*/  DDCAPS_COLORKEYHWASSIST ; 
 int /*<<< orphan*/  DDCAPS_GDI ; 
 int /*<<< orphan*/  DDCAPS_NOHARDWARE ; 
 int /*<<< orphan*/  DDCAPS_OVERLAY ; 
 int /*<<< orphan*/  DDCAPS_OVERLAYCANTCLIP ; 
 int /*<<< orphan*/  DDCAPS_OVERLAYFOURCC ; 
 int /*<<< orphan*/  DDCAPS_OVERLAYSTRETCH ; 
 int /*<<< orphan*/  DDCAPS_PALETTE ; 
 int /*<<< orphan*/  DDCAPS_PALETTEVSYNC ; 
 int /*<<< orphan*/  DDCAPS_READSCANLINE ; 
 int /*<<< orphan*/  DDCAPS_STEREOVIEW ; 
 int /*<<< orphan*/  DDCAPS_VBI ; 
 int /*<<< orphan*/  DDCAPS_ZBLTS ; 
 int /*<<< orphan*/  DDCAPS_ZOVERLAYS ; 
 int /*<<< orphan*/  DDCKEYCAPS_DESTBLT ; 
 int /*<<< orphan*/  DDCKEYCAPS_DESTBLTCLRSPACE ; 
 int /*<<< orphan*/  DDCKEYCAPS_DESTBLTCLRSPACEYUV ; 
 int /*<<< orphan*/  DDCKEYCAPS_DESTBLTYUV ; 
 int /*<<< orphan*/  DDCKEYCAPS_DESTOVERLAY ; 
 int /*<<< orphan*/  DDCKEYCAPS_DESTOVERLAYCLRSPACE ; 
 int /*<<< orphan*/  DDCKEYCAPS_DESTOVERLAYCLRSPACEYUV ; 
 int /*<<< orphan*/  DDCKEYCAPS_DESTOVERLAYONEACTIVE ; 
 int /*<<< orphan*/  DDCKEYCAPS_DESTOVERLAYYUV ; 
 int /*<<< orphan*/  DDCKEYCAPS_NOCOSTOVERLAY ; 
 int /*<<< orphan*/  DDCKEYCAPS_SRCBLT ; 
 int /*<<< orphan*/  DDCKEYCAPS_SRCBLTCLRSPACE ; 
 int /*<<< orphan*/  DDCKEYCAPS_SRCBLTCLRSPACEYUV ; 
 int /*<<< orphan*/  DDCKEYCAPS_SRCBLTYUV ; 
 int /*<<< orphan*/  DDCKEYCAPS_SRCOVERLAY ; 
 int /*<<< orphan*/  DDCKEYCAPS_SRCOVERLAYCLRSPACE ; 
 int /*<<< orphan*/  DDCKEYCAPS_SRCOVERLAYCLRSPACEYUV ; 
 int /*<<< orphan*/  DDCKEYCAPS_SRCOVERLAYONEACTIVE ; 
 int /*<<< orphan*/  DDCKEYCAPS_SRCOVERLAYYUV ; 
 int /*<<< orphan*/  DDFXCAPS_BLTARITHSTRETCHY ; 
 int /*<<< orphan*/  DDFXCAPS_BLTARITHSTRETCHYN ; 
 int /*<<< orphan*/  DDFXCAPS_BLTMIRRORLEFTRIGHT ; 
 int /*<<< orphan*/  DDFXCAPS_BLTMIRRORUPDOWN ; 
 int /*<<< orphan*/  DDFXCAPS_BLTROTATION ; 
 int /*<<< orphan*/  DDFXCAPS_BLTROTATION90 ; 
 int /*<<< orphan*/  DDFXCAPS_BLTSHRINKX ; 
 int /*<<< orphan*/  DDFXCAPS_BLTSHRINKXN ; 
 int /*<<< orphan*/  DDFXCAPS_BLTSHRINKY ; 
 int /*<<< orphan*/  DDFXCAPS_BLTSHRINKYN ; 
 int /*<<< orphan*/  DDFXCAPS_BLTSTRETCHX ; 
 int /*<<< orphan*/  DDFXCAPS_BLTSTRETCHXN ; 
 int /*<<< orphan*/  DDFXCAPS_BLTSTRETCHY ; 
 int /*<<< orphan*/  DDFXCAPS_BLTSTRETCHYN ; 
 int /*<<< orphan*/  DDFXCAPS_OVERLAYARITHSTRETCHY ; 
 int /*<<< orphan*/  DDFXCAPS_OVERLAYARITHSTRETCHYN ; 
 int /*<<< orphan*/  DDFXCAPS_OVERLAYMIRRORLEFTRIGHT ; 
 int /*<<< orphan*/  DDFXCAPS_OVERLAYMIRRORUPDOWN ; 
 int /*<<< orphan*/  DDFXCAPS_OVERLAYSHRINKX ; 
 int /*<<< orphan*/  DDFXCAPS_OVERLAYSHRINKXN ; 
 int /*<<< orphan*/  DDFXCAPS_OVERLAYSHRINKY ; 
 int /*<<< orphan*/  DDFXCAPS_OVERLAYSHRINKYN ; 
 int /*<<< orphan*/  DDFXCAPS_OVERLAYSTRETCHX ; 
 int /*<<< orphan*/  DDFXCAPS_OVERLAYSTRETCHY ; 
 int /*<<< orphan*/  DDFXCAPS_OVERLAYSTRETCHYN ; 
 int /*<<< orphan*/  DDHALINFO_GETDRIVERINFO2 ; 
 int /*<<< orphan*/  DDHALINFO_GETDRIVERINFOSET ; 
 int /*<<< orphan*/  DDHALINFO_ISPRIMARYDISPLAY ; 
 int /*<<< orphan*/  DDHALINFO_MODEXILLEGAL ; 
 int /*<<< orphan*/  DDSCAPS_3DDEVICE ; 
 int /*<<< orphan*/  DDSCAPS_ALLOCONLOAD ; 
 int /*<<< orphan*/  DDSCAPS_ALPHA ; 
 int /*<<< orphan*/  DDSCAPS_BACKBUFFER ; 
 int /*<<< orphan*/  DDSCAPS_COMPLEX ; 
 int /*<<< orphan*/  DDSCAPS_EXECUTEBUFFER ; 
 int /*<<< orphan*/  DDSCAPS_FLIP ; 
 int /*<<< orphan*/  DDSCAPS_FRONTBUFFER ; 
 int /*<<< orphan*/  DDSCAPS_HWCODEC ; 
 int /*<<< orphan*/  DDSCAPS_LIVEVIDEO ; 
 int /*<<< orphan*/  DDSCAPS_LOCALVIDMEM ; 
 int /*<<< orphan*/  DDSCAPS_MIPMAP ; 
 int /*<<< orphan*/  DDSCAPS_MODEX ; 
 int /*<<< orphan*/  DDSCAPS_NONLOCALVIDMEM ; 
 int /*<<< orphan*/  DDSCAPS_OFFSCREENPLAIN ; 
 int /*<<< orphan*/  DDSCAPS_OPTIMIZED ; 
 int /*<<< orphan*/  DDSCAPS_OVERLAY ; 
 int /*<<< orphan*/  DDSCAPS_OWNDC ; 
 int /*<<< orphan*/  DDSCAPS_PALETTE ; 
 int /*<<< orphan*/  DDSCAPS_PRIMARYSURFACE ; 
 int /*<<< orphan*/  DDSCAPS_PRIMARYSURFACELEFT ; 
 int /*<<< orphan*/  DDSCAPS_STANDARDVGAMODE ; 
 int /*<<< orphan*/  DDSCAPS_SYSTEMMEMORY ; 
 int /*<<< orphan*/  DDSCAPS_TEXTURE ; 
 int /*<<< orphan*/  DDSCAPS_VIDEOMEMORY ; 
 int /*<<< orphan*/  DDSCAPS_VIDEOPORT ; 
 int /*<<< orphan*/  DDSCAPS_VISIBLE ; 
 int /*<<< orphan*/  DDSCAPS_WRITEONLY ; 
 int /*<<< orphan*/  DDSCAPS_ZBUFFER ; 
 int /*<<< orphan*/  DDSVCAPS_ENIGMA ; 
 int /*<<< orphan*/  DDSVCAPS_FLICKER ; 
 int /*<<< orphan*/  DDSVCAPS_REDBLUE ; 
 int /*<<< orphan*/  DDSVCAPS_SPLIT ; 
 int DD_ROP_SPACE ; 
 int /*<<< orphan*/  checkflag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  endcheckflag (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
dump_halinfo(DD_HALINFO *pHalInfo, char *text)
{
    printf("dumping the DD_HALINFO from %s\n",text);

    if (pHalInfo->dwSize == sizeof(DD_HALINFO_V4))
    {
        DD_HALINFO_V4 *pHalInfo4 = (DD_HALINFO_V4 *) pHalInfo;
        int t;

        printf("DD_HALINFO Version NT4 found \n");
        printf(" pHalInfo4->dwSize                                  : 0x%08lx\n",(long)pHalInfo4->dwSize);
        printf(" pHalInfo4->vmiData->fpPrimary                      : 0x%08lx\n",(long)pHalInfo4->vmiData.fpPrimary);
        printf(" pHalInfo4->vmiData->dwFlags                        : 0x%08lx\n",(long)pHalInfo4->vmiData.dwFlags);
        printf(" pHalInfo4->vmiData->dwDisplayWidth                 : 0x%08lx\n",(long)pHalInfo4->vmiData.dwDisplayWidth);
        printf(" pHalInfo4->vmiData->dwDisplayHeight                : 0x%08lx\n",(long)pHalInfo4->vmiData.dwDisplayHeight);
        printf(" pHalInfo4->vmiData->lDisplayPitch                  : 0x%08lx\n",(long)pHalInfo4->vmiData.lDisplayPitch);

        printf(" pHalInfo4->vmiData->ddpfDisplay.dwSize             : 0x%08lx\n",(long)pHalInfo4->vmiData.ddpfDisplay.dwSize);
        printf(" pHalInfo4->vmiData->ddpfDisplay.dwFlags            : 0x%08lx\n",(long)pHalInfo4->vmiData.ddpfDisplay.dwFlags);
        printf(" pHalInfo4->vmiData->ddpfDisplay.dwFourCC           : 0x%08lx\n",(long)pHalInfo4->vmiData.ddpfDisplay.dwFourCC);
        printf(" pHalInfo4->vmiData->ddpfDisplay.dwRGBBitCount      : 0x%08lx\n",(long)pHalInfo4->vmiData.ddpfDisplay.dwRGBBitCount);
        printf(" pHalInfo4->vmiData->ddpfDisplay.dwRBitMask         : 0x%08lx\n",(long)pHalInfo4->vmiData.ddpfDisplay.dwRBitMask);
        printf(" pHalInfo4->vmiData->ddpfDisplay.dwGBitMask         : 0x%08lx\n",(long)pHalInfo4->vmiData.ddpfDisplay.dwGBitMask);
        printf(" pHalInfo4->vmiData->ddpfDisplay.dwBBitMask         : 0x%08lx\n",(long)pHalInfo4->vmiData.ddpfDisplay.dwBBitMask);
        printf(" pHalInfo4->vmiData->ddpfDisplay.dwRGBAlphaBitMask  : 0x%08lx\n",(long)pHalInfo4->vmiData.ddpfDisplay.dwRGBAlphaBitMask);

        printf(" pHalInfo4->vmiData->dwOffscreenAlign               : 0x%08lx\n",(long)pHalInfo4->vmiData.dwOffscreenAlign);
        printf(" pHalInfo4->vmiData->dwOverlayAlign                 : 0x%08lx\n",(long)pHalInfo4->vmiData.dwOverlayAlign);
        printf(" pHalInfo4->vmiData->dwTextureAlign                 : 0x%08lx\n",(long)pHalInfo4->vmiData.dwTextureAlign);
        printf(" pHalInfo4->vmiData->dwZBufferAlign                 : 0x%08lx\n",(long)pHalInfo4->vmiData.dwZBufferAlign);
        printf(" pHalInfo4->vmiData->dwAlphaAlign                   : 0x%08lx\n",(long)pHalInfo4->vmiData.dwAlphaAlign);
        printf(" pHalInfo4->vmiData->pvPrimary                      : 0x%08lx\n",(long)pHalInfo4->vmiData.pvPrimary);

        printf(" pHalInfo4->ddCaps.dwSize                           : 0x%08lx\n",pHalInfo4->ddCaps.dwSize);
        printf(" pHalInfo4->ddCaps.dwCaps                           : 0x%08lx\n",pHalInfo4->ddCaps.dwCaps);
        printf(" pHalInfo4->ddCaps.dwCaps2                          : 0x%08lx\n",pHalInfo4->ddCaps.dwCaps2);
        printf(" pHalInfo4->ddCaps.dwCKeyCaps                       : 0x%08lx\n",pHalInfo4->ddCaps.dwCKeyCaps);
        printf(" pHalInfo4->ddCaps.dwFXCaps                         : 0x%08lx\n",pHalInfo4->ddCaps.dwFXCaps);
        printf(" pHalInfo4->ddCaps.dwFXAlphaCaps                    : 0x%08lx\n",pHalInfo4->ddCaps.dwFXAlphaCaps);
        printf(" pHalInfo4->ddCaps.dwPalCaps                        : 0x%08lx\n",pHalInfo4->ddCaps.dwPalCaps);
        printf(" pHalInfo4->ddCaps.dwSVCaps                         : 0x%08lx\n",pHalInfo4->ddCaps.dwSVCaps);
        printf(" pHalInfo4->ddCaps.dwAlphaBltConstBitDepths         : 0x%08lx\n",pHalInfo4->ddCaps.dwAlphaBltConstBitDepths);
        printf(" pHalInfo4->ddCaps.dwAlphaBltPixelBitDepths         : 0x%08lx\n",pHalInfo4->ddCaps.dwAlphaBltPixelBitDepths);
        printf(" pHalInfo4->ddCaps.dwAlphaBltSurfaceBitDepths       : 0x%08lx\n",pHalInfo4->ddCaps.dwAlphaBltSurfaceBitDepths);
        printf(" pHalInfo4->ddCaps.dwAlphaOverlayConstBitDepths     : 0x%08lx\n",pHalInfo4->ddCaps.dwAlphaOverlayConstBitDepths);
        printf(" pHalInfo4->ddCaps.dwAlphaOverlayPixelBitDepths     : 0x%08lx\n",pHalInfo4->ddCaps.dwAlphaOverlayPixelBitDepths);
        printf(" pHalInfo4->ddCaps.dwAlphaOverlaySurfaceBitDepths   : 0x%08lx\n",pHalInfo4->ddCaps.dwAlphaOverlaySurfaceBitDepths);
        printf(" pHalInfo4->ddCaps.dwZBufferBitDepths               : 0x%08lx\n",pHalInfo4->ddCaps.dwZBufferBitDepths);
        printf(" pHalInfo4->ddCaps.dwVidMemTotal                    : 0x%08lx\n",pHalInfo4->ddCaps.dwVidMemTotal);
        printf(" pHalInfo4->ddCaps.dwVidMemFree                     : 0x%08lx\n",pHalInfo4->ddCaps.dwVidMemFree);
        printf(" pHalInfo4->ddCaps.dwMaxVisibleOverlays             : 0x%08lx\n",pHalInfo4->ddCaps.dwMaxVisibleOverlays);
        printf(" pHalInfo4->ddCaps.dwCurrVisibleOverlays            : 0x%08lx\n",pHalInfo4->ddCaps.dwCurrVisibleOverlays);
        printf(" pHalInfo4->ddCaps.dwNumFourCCCodes                 : 0x%08lx\n",pHalInfo4->ddCaps.dwNumFourCCCodes);
        printf(" pHalInfo4->ddCaps.dwAlignBoundarySrc               : 0x%08lx\n",pHalInfo4->ddCaps.dwAlignBoundarySrc);
        printf(" pHalInfo4->ddCaps.dwAlignSizeSrc                   : 0x%08lx\n",pHalInfo4->ddCaps.dwAlignSizeSrc);
        printf(" pHalInfo4->ddCaps.dwAlignBoundaryDes               : 0x%08lx\n",pHalInfo4->ddCaps.dwAlignBoundaryDest);
        printf(" pHalInfo4->ddCaps.dwAlignSizeDest                  : 0x%08lx\n",pHalInfo4->ddCaps.dwAlignSizeDest);
        printf(" pHalInfo4->ddCaps.dwAlignStrideAlign               : 0x%08lx\n",pHalInfo4->ddCaps.dwAlignStrideAlign);
        for (t=0;t<DD_ROP_SPACE;t++)
        {
        printf(" pHalInfo4->ddCaps.dwRops[0x%04x]                   : 0x%08lx\n",t,pHalInfo4->ddCaps.dwRops[t]);
        }
        printf(" pHalInfo4->ddCaps.ddsCaps.dwCaps                   : 0x%08lx\n",pHalInfo4->ddCaps.ddsCaps.dwCaps);
        printf(" pHalInfo4->ddCaps.dwMinOverlayStretch              : 0x%08lx\n",pHalInfo4->ddCaps.dwMinOverlayStretch);
        printf(" pHalInfo4->ddCaps.dwMaxOverlayStretch              : 0x%08lx\n",pHalInfo4->ddCaps.dwMaxOverlayStretch);
        printf(" pHalInfo4->ddCaps.dwMinLiveVideoStretch            : 0x%08lx\n",pHalInfo4->ddCaps.dwMinLiveVideoStretch);
        printf(" pHalInfo4->ddCaps.dwMaxLiveVideoStretch            : 0x%08lx\n",pHalInfo4->ddCaps.dwMaxLiveVideoStretch);
        printf(" pHalInfo4->ddCaps.dwMinHwCodecStretch              : 0x%08lx\n",pHalInfo4->ddCaps.dwMinHwCodecStretch);
        printf(" pHalInfo4->ddCaps.dwMaxHwCodecStretch              : 0x%08lx\n",pHalInfo4->ddCaps.dwMaxHwCodecStretch);
        printf(" pHalInfo4->ddCaps.dwReserved1                      : 0x%08lx\n",pHalInfo4->ddCaps.dwReserved1);
        printf(" pHalInfo4->ddCaps.dwReserved2                      : 0x%08lx\n",pHalInfo4->ddCaps.dwReserved2);
        printf(" pHalInfo4->ddCaps.dwReserved3                      : 0x%08lx\n",pHalInfo4->ddCaps.dwReserved3);
        printf(" pHalInfo4->ddCaps.dwSVBCaps                        : 0x%08lx\n",pHalInfo4->ddCaps.dwSVBCaps);
        printf(" pHalInfo4->ddCaps.dwSVBCKeyCaps                    : 0x%08lx\n",pHalInfo4->ddCaps.dwSVBCKeyCaps);
        printf(" pHalInfo4->ddCaps.dwSVBFXCaps                      : 0x%08lx\n",pHalInfo4->ddCaps.dwSVBFXCaps);
        for (t=0;t<DD_ROP_SPACE;t++)
        {
        printf(" pHalInfo4->ddCaps.dwSVBRops[0x%04x]                : 0x%08lx\n",t,pHalInfo4->ddCaps.dwSVBRops[t]);
        }
        printf(" pHalInfo4->ddCaps.dwVSBCaps                        : 0x%08lx\n",pHalInfo4->ddCaps.dwVSBCaps);
        printf(" pHalInfo4->ddCaps.dwVSBCKeyCaps                    : 0x%08lx\n",pHalInfo4->ddCaps.dwVSBCKeyCaps);
        printf(" pHalInfo4->ddCaps.dwVSBFXCaps                      : 0x%08lx\n",pHalInfo4->ddCaps.dwVSBFXCaps);
        for (t=0;t<DD_ROP_SPACE;t++)
        {
        printf(" pHalInfo4->ddCaps.dwVSBRops[0x%04x]                : 0x%08lx\n",t,pHalInfo4->ddCaps.dwVSBRops[t]);
        }
        printf(" pHalInfo4->ddCaps.dwSSBCaps                        : 0x%08lx\n",pHalInfo4->ddCaps.dwSSBCaps);
        printf(" pHalInfo4->ddCaps.dwSSBCKeyCa                      : 0x%08lx\n",pHalInfo4->ddCaps.dwSSBCKeyCaps);
        printf(" pHalInfo4->ddCaps.dwSSBFXCaps                      : 0x%08lx\n",pHalInfo4->ddCaps.dwSSBFXCaps);
        for (t=0;t<DD_ROP_SPACE;t++)
        {
        printf(" pHalInfo4->ddCaps.dwSSBRops[0x%04x]                : 0x%08lx\n",t,pHalInfo4->ddCaps.dwSSBRops[t]);
        }

        printf(" pHalInfo4->ddCaps.dwMaxVideoPorts                  : 0x%08lx\n",pHalInfo4->ddCaps.dwMaxVideoPorts);
        printf(" pHalInfo4->ddCaps.dwCurrVideoPorts                 : 0x%08lx\n",pHalInfo4->ddCaps.dwCurrVideoPorts);
        printf(" pHalInfo4->ddCaps.dwSVBCaps2                       : 0x%08lx\n",pHalInfo4->ddCaps.dwSVBCaps2);


        printf(" pHalInfo4->GetDriverInfo                           : 0x%08lx\n",(long)pHalInfo4->GetDriverInfo);
        printf(" pHalInfo4->dwFlags                                 : 0x%08lx\n",(long)pHalInfo4->dwFlags);

    }
    else if (pHalInfo->dwSize == sizeof(DD_HALINFO))
    {
        int t;
        UINT flag;
        INT count=0;
        
        printf("DD_HALINFO Version NT 2000/XP/2003 found \n");
        printf(" pHalInfo->dwSize                                  : 0x%08lx\n",(long)pHalInfo->dwSize);

        printf(" pHalInfo->vmiData->fpPrimary                      : 0x%08lx\n",(long)pHalInfo->vmiData.fpPrimary);
        printf(" pHalInfo->vmiData->dwFlags                        : 0x%08lx\n",(long)pHalInfo->vmiData.dwFlags);
        printf(" pHalInfo->vmiData->dwDisplayWidth                 : 0x%08lx\n",(long)pHalInfo->vmiData.dwDisplayWidth);
        printf(" pHalInfo->vmiData->dwDisplayHeight                : 0x%08lx\n",(long)pHalInfo->vmiData.dwDisplayHeight);
        printf(" pHalInfo->vmiData->lDisplayPitch                  : 0x%08lx\n",(long)pHalInfo->vmiData.lDisplayPitch);

        printf(" pHalInfo->vmiData->ddpfDisplay.dwSize             : 0x%08lx\n",(long)pHalInfo->vmiData.ddpfDisplay.dwSize);
        printf(" pHalInfo->vmiData->ddpfDisplay.dwFlags            : 0x%08lx\n",(long)pHalInfo->vmiData.ddpfDisplay.dwFlags);
        printf(" pHalInfo->vmiData->ddpfDisplay.dwFourCC           : 0x%08lx\n",(long)pHalInfo->vmiData.ddpfDisplay.dwFourCC);
        printf(" pHalInfo->vmiData->ddpfDisplay.dwRGBBitCount      : 0x%08lx\n",(long)pHalInfo->vmiData.ddpfDisplay.dwRGBBitCount);
        printf(" pHalInfo->vmiData->ddpfDisplay.dwRBitMask         : 0x%08lx\n",(long)pHalInfo->vmiData.ddpfDisplay.dwRBitMask);
        printf(" pHalInfo->vmiData->ddpfDisplay.dwGBitMask         : 0x%08lx\n",(long)pHalInfo->vmiData.ddpfDisplay.dwGBitMask);
        printf(" pHalInfo->vmiData->ddpfDisplay.dwBBitMask         : 0x%08lx\n",(long)pHalInfo->vmiData.ddpfDisplay.dwBBitMask);
        printf(" pHalInfo->vmiData->ddpfDisplay.dwRGBAlphaBitMask  : 0x%08lx\n",(long)pHalInfo->vmiData.ddpfDisplay.dwRGBAlphaBitMask);


        printf(" pHalInfo->vmiData->dwOffscreenAlign               : 0x%08lx\n",(long)pHalInfo->vmiData.dwOffscreenAlign);
        printf(" pHalInfo->vmiData->dwOverlayAlign                 : 0x%08lx\n",(long)pHalInfo->vmiData.dwOverlayAlign);
        printf(" pHalInfo->vmiData->dwTextureAlign                 : 0x%08lx\n",(long)pHalInfo->vmiData.dwTextureAlign);
        printf(" pHalInfo->vmiData->dwZBufferAlign                 : 0x%08lx\n",(long)pHalInfo->vmiData.dwZBufferAlign);
        printf(" pHalInfo->vmiData->dwAlphaAlign                   : 0x%08lx\n",(long)pHalInfo->vmiData.dwAlphaAlign);
        printf(" pHalInfo->vmiData->pvPrimary                      : 0x%08lx\n",(long)pHalInfo->vmiData.pvPrimary);

        printf(" pHalInfo->ddCaps.dwSize                           : 0x%08lx\n",pHalInfo->ddCaps.dwSize);
        printf(" pHalInfo->ddCaps.dwCaps                           : ");
        flag = pHalInfo->ddCaps.dwCaps;
        count = 0;
        checkflag(flag,DDCAPS_3D,"DDCAPS_3D");
        checkflag(flag,DDCAPS_ALIGNBOUNDARYDEST,"DDCAPS_ALIGNBOUNDARYDEST");
        checkflag(flag,DDCAPS_ALIGNBOUNDARYSRC,"DDCAPS_ALIGNBOUNDARYSRC");
        checkflag(flag,DDCAPS_ALIGNSIZEDEST,"DDCAPS_ALIGNSIZEDEST");
        checkflag(flag,DDCAPS_ALIGNSIZESRC,"DDCAPS_ALIGNSIZESRC");
        checkflag(flag,DDCAPS_ALIGNSTRIDE,"DDCAPS_ALIGNSTRIDE");
        checkflag(flag,DDCAPS_ALPHA,"DDCAPS_ALPHA");
        checkflag(flag,DDCAPS_BANKSWITCHED,"DDCAPS_BANKSWITCHED");
        checkflag(flag,DDCAPS_BLT,"DDCAPS_BLT");
        checkflag(flag,DDCAPS_BLTCOLORFILL,"DDCAPS_BLTCOLORFILL");
        checkflag(flag,DDCAPS_BLTDEPTHFILL,"DDCAPS_BLTDEPTHFILL");
        checkflag(flag,DDCAPS_BLTFOURCC,"DDCAPS_BLTFOURCC");
        checkflag(flag,DDCAPS_BLTQUEUE,"DDCAPS_BLTQUEUE");
        checkflag(flag,DDCAPS_BLTSTRETCH,"DDCAPS_BLTSTRETCH");
        checkflag(flag,DDCAPS_CANBLTSYSMEM,"DDCAPS_CANBLTSYSMEM");
        checkflag(flag,DDCAPS_CANCLIP,"DDCAPS_CANCLIP");
        checkflag(flag,DDCAPS_CANCLIPSTRETCHED,"DDCAPS_CANCLIPSTRETCHED");
        checkflag(flag,DDCAPS_COLORKEY,"DDCAPS_COLORKEY");
        checkflag(flag,DDCAPS_COLORKEYHWASSIST,"DDCAPS_COLORKEYHWASSIST");
        checkflag(flag,DDCAPS_GDI,"DDCAPS_GDI");
        checkflag(flag,DDCAPS_NOHARDWARE,"DDCAPS_NOHARDWARE");
        checkflag(flag,DDCAPS_OVERLAY,"DDCAPS_OVERLAY");
        checkflag(flag,DDCAPS_OVERLAYCANTCLIP,"DDCAPS_OVERLAYCANTCLIP");
        checkflag(flag,DDCAPS_OVERLAYFOURCC,"DDCAPS_OVERLAYFOURCC");
        checkflag(flag,DDCAPS_OVERLAYSTRETCH,"DDCAPS_OVERLAYSTRETCH");
        checkflag(flag,DDCAPS_PALETTE,"DDCAPS_PALETTE");
        checkflag(flag,DDCAPS_PALETTEVSYNC,"DDCAPS_PALETTEVSYNC");
        checkflag(flag,DDCAPS_READSCANLINE,"DDCAPS_READSCANLINE");
        checkflag(flag,DDCAPS_STEREOVIEW,"DDCAPS_STEREOVIEW");
        checkflag(flag,DDCAPS_VBI,"DDCAPS_VBI");
        checkflag(flag,DDCAPS_ZBLTS,"DDCAPS_ZBLTS");
        checkflag(flag,DDCAPS_ZOVERLAYS,"DDCAPS_ZOVERLAYS");
        endcheckflag(flag,"pHalInfo->ddCaps.dwCaps");

        printf(" pHalInfo->ddCaps.dwCaps2                          : ");
        flag = pHalInfo->ddCaps.dwCaps2;
        count = 0;
        checkflag(flag,DDCAPS2_AUTOFLIPOVERLAY,"DDCAPS2_AUTOFLIPOVERLAY");
        checkflag(flag,DDCAPS2_CANAUTOGENMIPMAP,"DDCAPS2_CANAUTOGENMIPMAP");
        checkflag(flag,DDCAPS2_CANBOBHARDWARE,"DDCAPS2_CANBOBHARDWARE");
        checkflag(flag,DDCAPS2_CANBOBINTERLEAVED,"DDCAPS2_CANBOBINTERLEAVED");
        checkflag(flag,DDCAPS2_CANBOBNONINTERLEAVED,"DDCAPS2_CANBOBNONINTERLEAVED");
        checkflag(flag,DDCAPS2_CANCALIBRATEGAMMA,"DDCAPS2_CANCALIBRATEGAMMA");
        checkflag(flag,DDCAPS2_CANDROPZ16BIT,"DDCAPS2_CANDROPZ16BIT");
        checkflag(flag,DDCAPS2_CANFLIPODDEVEN,"DDCAPS2_CANFLIPODDEVEN");
        checkflag(flag,DDCAPS2_CANMANAGERESOURCE,"DDCAPS2_CANMANAGERESOURCE");
        checkflag(flag,DDCAPS2_CANMANAGETEXTURE,"DDCAPS2_CANMANAGETEXTURE");

        checkflag(flag,DDCAPS2_CANRENDERWINDOWED,"DDCAPS2_CANRENDERWINDOWED");
        checkflag(flag,DDCAPS2_CERTIFIED,"DDCAPS2_CERTIFIED");
        checkflag(flag,DDCAPS2_COLORCONTROLOVERLAY,"DDCAPS2_COLORCONTROLOVERLAY");
        checkflag(flag,DDCAPS2_COLORCONTROLPRIMARY,"DDCAPS2_COLORCONTROLPRIMARY");
        checkflag(flag,DDCAPS2_COPYFOURCC,"DDCAPS2_COPYFOURCC");
        checkflag(flag,DDCAPS2_FLIPINTERVAL,"DDCAPS2_FLIPINTERVAL");
        checkflag(flag,DDCAPS2_FLIPNOVSYNC,"DDCAPS2_FLIPNOVSYNC");
        checkflag(flag,DDCAPS2_NO2DDURING3DSCENE,"DDCAPS2_NO2DDURING3DSCENE");
        checkflag(flag,DDCAPS2_NONLOCALVIDMEM,"DDCAPS2_NONLOCALVIDMEM");
        checkflag(flag,DDCAPS2_NONLOCALVIDMEMCAPS,"DDCAPS2_NONLOCALVIDMEMCAPS");
        checkflag(flag,DDCAPS2_NOPAGELOCKREQUIRED,"DDCAPS2_NOPAGELOCKREQUIRED");
        checkflag(flag,DDCAPS2_PRIMARYGAMMA,"DDCAPS2_PRIMARYGAMMA");
        checkflag(flag,DDCAPS2_VIDEOPORT,"DDCAPS2_VIDEOPORT");
        checkflag(flag,DDCAPS2_WIDESURFACES,"DDCAPS2_WIDESURFACES");
        endcheckflag(flag,"pHalInfo->ddCaps.dwCaps2");

        printf(" pHalInfo->ddCaps.dwCKeyCaps                       : ");
        flag = pHalInfo->ddCaps.dwCKeyCaps;
        count = 0;
        checkflag(flag,DDCKEYCAPS_DESTBLT,"DDCKEYCAPS_DESTBLT");
        checkflag(flag,DDCKEYCAPS_DESTBLTCLRSPACE,"DDCKEYCAPS_DESTBLTCLRSPACE");
        checkflag(flag,DDCKEYCAPS_DESTBLTCLRSPACEYUV,"DDCKEYCAPS_DESTBLTCLRSPACEYUV");
        checkflag(flag,DDCKEYCAPS_DESTBLTYUV,"DDCKEYCAPS_DESTBLTYUV");
        checkflag(flag,DDCKEYCAPS_DESTOVERLAY,"DDCKEYCAPS_DESTOVERLAY");
        checkflag(flag,DDCKEYCAPS_DESTOVERLAYCLRSPACE,"DDCKEYCAPS_DESTOVERLAYCLRSPACE");
        checkflag(flag,DDCKEYCAPS_DESTOVERLAYCLRSPACEYUV,"DDCKEYCAPS_DESTOVERLAYCLRSPACEYUV");
        checkflag(flag,DDCKEYCAPS_DESTOVERLAYONEACTIVE,"DDCKEYCAPS_DESTOVERLAYONEACTIVE");
        checkflag(flag,DDCKEYCAPS_DESTOVERLAYYUV,"DDCKEYCAPS_DESTOVERLAYYUV");
        checkflag(flag,DDCKEYCAPS_NOCOSTOVERLAY,"DDCKEYCAPS_NOCOSTOVERLAY");
        checkflag(flag,DDCKEYCAPS_SRCBLT,"DDCKEYCAPS_SRCBLT");
        checkflag(flag,DDCKEYCAPS_SRCBLTCLRSPACE,"DDCKEYCAPS_SRCBLTCLRSPACE");
        checkflag(flag,DDCKEYCAPS_SRCBLTCLRSPACEYUV,"DDCKEYCAPS_SRCBLTCLRSPACEYUV");
        checkflag(flag,DDCKEYCAPS_SRCBLTYUV,"DDCKEYCAPS_SRCBLTYUV");
        checkflag(flag,DDCKEYCAPS_SRCOVERLAY,"DDCKEYCAPS_SRCOVERLAY");
        checkflag(flag,DDCKEYCAPS_SRCOVERLAYCLRSPACE,"DDCKEYCAPS_SRCOVERLAYCLRSPACE");
        checkflag(flag,DDCKEYCAPS_SRCOVERLAYCLRSPACEYUV,"DDCKEYCAPS_SRCOVERLAYCLRSPACEYUV");
        checkflag(flag,DDCKEYCAPS_SRCOVERLAYONEACTIVE,"DDCKEYCAPS_SRCOVERLAYONEACTIVE");
        checkflag(flag,DDCKEYCAPS_SRCOVERLAYYUV,"DDCKEYCAPS_SRCOVERLAYYUV");
        endcheckflag(flag,"pHalInfo->ddCaps.dwCKeyCaps");

        printf(" pHalInfo->ddCaps.dwFXCaps                         : ");
        flag = pHalInfo->ddCaps.dwFXCaps;
        count = 0;
        checkflag(flag,DDFXCAPS_BLTARITHSTRETCHY,"DDFXCAPS_BLTARITHSTRETCHY");
        checkflag(flag,DDFXCAPS_BLTARITHSTRETCHYN,"DDFXCAPS_BLTARITHSTRETCHYN");
        checkflag(flag,DDFXCAPS_BLTMIRRORLEFTRIGHT,"DDFXCAPS_BLTMIRRORLEFTRIGHT");
        checkflag(flag,DDFXCAPS_BLTMIRRORUPDOWN,"DDFXCAPS_BLTMIRRORUPDOWN");
        checkflag(flag,DDFXCAPS_BLTROTATION,"DDFXCAPS_BLTROTATION");
        checkflag(flag,DDFXCAPS_BLTROTATION90,"DDFXCAPS_BLTROTATION90");
        checkflag(flag,DDFXCAPS_BLTSHRINKX,"DDFXCAPS_BLTSHRINKX");
        checkflag(flag,DDFXCAPS_BLTSHRINKXN,"DDFXCAPS_BLTSHRINKXN");
        checkflag(flag,DDFXCAPS_BLTSHRINKY,"DDFXCAPS_BLTSHRINKY");
        checkflag(flag,DDFXCAPS_BLTSHRINKYN,"DDFXCAPS_BLTSHRINKYN");
        checkflag(flag,DDFXCAPS_BLTSTRETCHX,"DDFXCAPS_BLTSTRETCHX");
        checkflag(flag,DDFXCAPS_BLTSTRETCHXN,"DDFXCAPS_BLTSTRETCHXN");
        checkflag(flag,DDFXCAPS_BLTSTRETCHY,"DDFXCAPS_BLTSTRETCHY");
        checkflag(flag,DDFXCAPS_BLTSTRETCHYN,"DDFXCAPS_BLTSTRETCHYN");
        checkflag(flag,DDFXCAPS_OVERLAYARITHSTRETCHY,"DDFXCAPS_OVERLAYARITHSTRETCHY");
        checkflag(flag,DDFXCAPS_OVERLAYARITHSTRETCHYN,"DDFXCAPS_OVERLAYARITHSTRETCHYN");
        checkflag(flag,DDFXCAPS_OVERLAYMIRRORLEFTRIGHT,"DDFXCAPS_OVERLAYMIRRORLEFTRIGHT");
        checkflag(flag,DDFXCAPS_OVERLAYMIRRORUPDOWN,"DDFXCAPS_OVERLAYMIRRORUPDOWN");
        checkflag(flag,DDFXCAPS_OVERLAYSHRINKX,"DDFXCAPS_OVERLAYSHRINKX");
        checkflag(flag,DDFXCAPS_OVERLAYSHRINKXN,"DDFXCAPS_OVERLAYSHRINKXN");
        checkflag(flag,DDFXCAPS_OVERLAYSHRINKY,"DDFXCAPS_OVERLAYSHRINKY");
        checkflag(flag,DDFXCAPS_OVERLAYSHRINKYN,"DDFXCAPS_OVERLAYSHRINKYN");
        checkflag(flag,DDFXCAPS_OVERLAYSTRETCHX,"DDFXCAPS_OVERLAYSTRETCHX");
        checkflag(flag,DDFXCAPS_OVERLAYSTRETCHX,"DDFXCAPS_OVERLAYSTRETCHX");
        checkflag(flag,DDFXCAPS_OVERLAYSTRETCHY,"DDFXCAPS_OVERLAYSTRETCHY");
        checkflag(flag,DDFXCAPS_OVERLAYSTRETCHYN,"DDFXCAPS_OVERLAYSTRETCHYN");
        endcheckflag(flag,"pHalInfo->ddCaps.dwFXCaps");

        printf(" pHalInfo->ddCaps.dwFXAlphaCaps                    : 0x%08lx\n",pHalInfo->ddCaps.dwFXAlphaCaps);
        printf(" pHalInfo->ddCaps.dwPalCaps                        : 0x%08lx\n",pHalInfo->ddCaps.dwPalCaps);

        printf(" pHalInfo->ddCaps.dwSVCaps                         : ");        
        flag = pHalInfo->ddCaps.dwSVCaps;
        count = 0;
        checkflag(flag,DDSVCAPS_ENIGMA,"DDSVCAPS_ENIGMA");
        checkflag(flag,DDSVCAPS_FLICKER,"DDSVCAPS_FLICKER");
        checkflag(flag,DDSVCAPS_REDBLUE,"DDSVCAPS_REDBLUE");
        checkflag(flag,DDSVCAPS_SPLIT,"DDSVCAPS_SPLIT");
        endcheckflag(flag,"pHalInfo->ddCaps.dwSVCaps");

        printf(" pHalInfo->ddCaps.dwAlphaBltConstBitDepths         : 0x%08lx\n",pHalInfo->ddCaps.dwAlphaBltConstBitDepths);
        printf(" pHalInfo->ddCaps.dwAlphaBltPixelBitDepths         : 0x%08lx\n",pHalInfo->ddCaps.dwAlphaBltPixelBitDepths);
        printf(" pHalInfo->ddCaps.dwAlphaBltSurfaceBitDepths       : 0x%08lx\n",pHalInfo->ddCaps.dwAlphaBltSurfaceBitDepths);
        printf(" pHalInfo->ddCaps.dwAlphaOverlayConstBitDepths     : 0x%08lx\n",pHalInfo->ddCaps.dwAlphaOverlayConstBitDepths);
        printf(" pHalInfo->ddCaps.dwAlphaOverlayPixelBitDepths     : 0x%08lx\n",pHalInfo->ddCaps.dwAlphaOverlayPixelBitDepths);
        printf(" pHalInfo->ddCaps.dwAlphaOverlaySurfaceBitDepths   : 0x%08lx\n",pHalInfo->ddCaps.dwAlphaOverlaySurfaceBitDepths);
        printf(" pHalInfo->ddCaps.dwZBufferBitDepths               : 0x%08lx\n",pHalInfo->ddCaps.dwZBufferBitDepths);
        printf(" pHalInfo->ddCaps.dwVidMemTotal                    : 0x%08lx\n",pHalInfo->ddCaps.dwVidMemTotal);
        printf(" pHalInfo->ddCaps.dwVidMemFree                     : 0x%08lx\n",pHalInfo->ddCaps.dwVidMemFree);
        printf(" pHalInfo->ddCaps.dwMaxVisibleOverlays             : 0x%08lx\n",pHalInfo->ddCaps.dwMaxVisibleOverlays);
        printf(" pHalInfo->ddCaps.dwCurrVisibleOverlays            : 0x%08lx\n",pHalInfo->ddCaps.dwCurrVisibleOverlays);
        printf(" pHalInfo->ddCaps.dwNumFourCCCodes                 : 0x%08lx\n",pHalInfo->ddCaps.dwNumFourCCCodes);
        printf(" pHalInfo->ddCaps.dwAlignBoundarySrc               : 0x%08lx\n",pHalInfo->ddCaps.dwAlignBoundarySrc);
        printf(" pHalInfo->ddCaps.dwAlignSizeSrc                   : 0x%08lx\n",pHalInfo->ddCaps.dwAlignSizeSrc);
        printf(" pHalInfo->ddCaps.dwAlignBoundaryDes               : 0x%08lx\n",pHalInfo->ddCaps.dwAlignBoundaryDest);
        printf(" pHalInfo->ddCaps.dwAlignSizeDest                  : 0x%08lx\n",pHalInfo->ddCaps.dwAlignSizeDest);
        printf(" pHalInfo->ddCaps.dwAlignStrideAlign               : 0x%08lx\n",pHalInfo->ddCaps.dwAlignStrideAlign);
        for (t=0;t<DD_ROP_SPACE;t++)
        {
        printf(" pHalInfo->ddCaps.dwRops[0x%04x]                   : 0x%08lx\n",t,pHalInfo->ddCaps.dwRops[t]);
        }
        printf(" pHalInfo->ddCaps.ddsCaps.dwCaps                   : ");
        flag = pHalInfo->ddCaps.ddsCaps.dwCaps;
        count = 0;
        checkflag(flag,DDSCAPS_3DDEVICE,"DDSCAPS_3DDEVICE");
        checkflag(flag,DDSCAPS_ALLOCONLOAD,"DDSCAPS_ALLOCONLOAD");
        checkflag(flag,DDSCAPS_ALPHA,"DDSCAPS_ALPHA");
        checkflag(flag,DDSCAPS_BACKBUFFER,"DDSCAPS_BACKBUFFER");
        checkflag(flag,DDSCAPS_COMPLEX,"DDSCAPS_COMPLEX");
        checkflag(flag,DDSCAPS_EXECUTEBUFFER,"DDSCAPS_EXECUTEBUFFER");
        checkflag(flag,DDSCAPS_FLIP,"DDSCAPS_FLIP");
        checkflag(flag,DDSCAPS_FRONTBUFFER,"DDSCAPS_FRONTBUFFER");
        checkflag(flag,DDSCAPS_HWCODEC,"DDSCAPS_HWCODEC");
        checkflag(flag,DDSCAPS_LIVEVIDEO,"DDSCAPS_LIVEVIDEO");
        checkflag(flag,DDSCAPS_LOCALVIDMEM,"DDSCAPS_LOCALVIDMEM");
        checkflag(flag,DDSCAPS_MIPMAP,"DDSCAPS_MIPMAP");
        checkflag(flag,DDSCAPS_MODEX,"DDSCAPS_MODEX");
        checkflag(flag,DDSCAPS_NONLOCALVIDMEM,"DDSCAPS_NONLOCALVIDMEM");
        checkflag(flag,DDSCAPS_OFFSCREENPLAIN,"DDSCAPS_OFFSCREENPLAIN");
        checkflag(flag,DDSCAPS_OVERLAY,"DDSCAPS_OVERLAY");
        checkflag(flag,DDSCAPS_OPTIMIZED,"DDSCAPS_OPTIMIZED");
        checkflag(flag,DDSCAPS_OWNDC,"DDSCAPS_OWNDC");
        checkflag(flag,DDSCAPS_PALETTE,"DDSCAPS_PALETTE");
        checkflag(flag,DDSCAPS_PRIMARYSURFACE,"DDSCAPS_PRIMARYSURFACE");
        checkflag(flag,DDSCAPS_PRIMARYSURFACELEFT,"DDSCAPS_PRIMARYSURFACELEFT");
        checkflag(flag,DDSCAPS_STANDARDVGAMODE,"DDSCAPS_STANDARDVGAMODE");
        checkflag(flag,DDSCAPS_SYSTEMMEMORY,"DDSCAPS_SYSTEMMEMORY");
        checkflag(flag,DDSCAPS_TEXTURE,"DDSCAPS_TEXTURE");
        checkflag(flag,DDSCAPS_VIDEOMEMORY,"DDSCAPS_VIDEOMEMORY");
        checkflag(flag,DDSCAPS_VIDEOPORT,"DDSCAPS_VIDEOPORT");
        checkflag(flag,DDSCAPS_VISIBLE,"DDSCAPS_VISIBLE");
        checkflag(flag,DDSCAPS_WRITEONLY,"DDSCAPS_WRITEONLY");
        checkflag(flag,DDSCAPS_ZBUFFER,"DDSCAPS_ZBUFFER");
        endcheckflag(flag,"pHalInfo->ddCaps.ddsCaps.dwCaps");

        printf(" pHalInfo->ddCaps.dwMinOverlayStretch              : 0x%08lx\n",pHalInfo->ddCaps.dwMinOverlayStretch);
        printf(" pHalInfo->ddCaps.dwMaxOverlayStretch              : 0x%08lx\n",pHalInfo->ddCaps.dwMaxOverlayStretch);
        printf(" pHalInfo->ddCaps.dwMinLiveVideoStretch            : 0x%08lx\n",pHalInfo->ddCaps.dwMinLiveVideoStretch);
        printf(" pHalInfo->ddCaps.dwMaxLiveVideoStretch            : 0x%08lx\n",pHalInfo->ddCaps.dwMaxLiveVideoStretch);
        printf(" pHalInfo->ddCaps.dwMinHwCodecStretch              : 0x%08lx\n",pHalInfo->ddCaps.dwMinHwCodecStretch);
        printf(" pHalInfo->ddCaps.dwMaxHwCodecStretch              : 0x%08lx\n",pHalInfo->ddCaps.dwMaxHwCodecStretch);
        printf(" pHalInfo->ddCaps.dwReserved1                      : 0x%08lx\n",pHalInfo->ddCaps.dwReserved1);
        printf(" pHalInfo->ddCaps.dwReserved2                      : 0x%08lx\n",pHalInfo->ddCaps.dwReserved2);
        printf(" pHalInfo->ddCaps.dwReserved3                      : 0x%08lx\n",pHalInfo->ddCaps.dwReserved3);
        
        printf(" pHalInfo->ddCaps.dwSVBCaps                        : ");
        flag = pHalInfo->ddCaps.dwSVBCaps;
        count = 0;   
        checkflag(flag,DDCAPS_3D,"DDCAPS_3D");
        checkflag(flag,DDCAPS_ALIGNBOUNDARYDEST,"DDCAPS_ALIGNBOUNDARYDEST");
        checkflag(flag,DDCAPS_ALIGNBOUNDARYSRC,"DDCAPS_ALIGNBOUNDARYSRC");
        checkflag(flag,DDCAPS_ALIGNSIZEDEST,"DDCAPS_ALIGNSIZEDEST");
        checkflag(flag,DDCAPS_ALIGNSIZESRC,"DDCAPS_ALIGNSIZESRC");
        checkflag(flag,DDCAPS_ALIGNSTRIDE,"DDCAPS_ALIGNSTRIDE");
        checkflag(flag,DDCAPS_ALPHA,"DDCAPS_ALPHA");
        checkflag(flag,DDCAPS_BANKSWITCHED,"DDCAPS_BANKSWITCHED");
        checkflag(flag,DDCAPS_BLT,"DDCAPS_BLT");
        checkflag(flag,DDCAPS_BLTCOLORFILL,"DDCAPS_BLTCOLORFILL");
        checkflag(flag,DDCAPS_BLTDEPTHFILL,"DDCAPS_BLTDEPTHFILL");
        checkflag(flag,DDCAPS_BLTFOURCC,"DDCAPS_BLTFOURCC");
        checkflag(flag,DDCAPS_BLTQUEUE,"DDCAPS_BLTQUEUE");
        checkflag(flag,DDCAPS_BLTSTRETCH,"DDCAPS_BLTSTRETCH");
        checkflag(flag,DDCAPS_CANBLTSYSMEM,"DDCAPS_CANBLTSYSMEM");
        checkflag(flag,DDCAPS_CANCLIP,"DDCAPS_CANCLIP");
        checkflag(flag,DDCAPS_CANCLIPSTRETCHED,"DDCAPS_CANCLIPSTRETCHED");
        checkflag(flag,DDCAPS_COLORKEY,"DDCAPS_COLORKEY");
        checkflag(flag,DDCAPS_COLORKEYHWASSIST,"DDCAPS_COLORKEYHWASSIST");
        checkflag(flag,DDCAPS_GDI,"DDCAPS_GDI");
        checkflag(flag,DDCAPS_NOHARDWARE,"DDCAPS_NOHARDWARE");
        checkflag(flag,DDCAPS_OVERLAY,"DDCAPS_OVERLAY");
        checkflag(flag,DDCAPS_OVERLAYCANTCLIP,"DDCAPS_OVERLAYCANTCLIP");
        checkflag(flag,DDCAPS_OVERLAYFOURCC,"DDCAPS_OVERLAYFOURCC");
        checkflag(flag,DDCAPS_OVERLAYSTRETCH,"DDCAPS_OVERLAYSTRETCH");
        checkflag(flag,DDCAPS_PALETTE,"DDCAPS_PALETTE");
        checkflag(flag,DDCAPS_PALETTEVSYNC,"DDCAPS_PALETTEVSYNC");
        checkflag(flag,DDCAPS_READSCANLINE,"DDCAPS_READSCANLINE");
        checkflag(flag,DDCAPS_STEREOVIEW,"DDCAPS_STEREOVIEW");
        checkflag(flag,DDCAPS_VBI,"DDCAPS_VBI");
        checkflag(flag,DDCAPS_ZBLTS,"DDCAPS_ZBLTS");
        checkflag(flag,DDCAPS_ZOVERLAYS,"DDCAPS_ZOVERLAYS");
        endcheckflag(flag,"pHalInfo->ddCaps.dwSVBCaps");

        printf(" pHalInfo->ddCaps.dwSVBCKeyCaps                    : 0x%08lx\n",pHalInfo->ddCaps.dwSVBCKeyCaps);
        printf(" pHalInfo->ddCaps.dwSVBFXCaps                      : 0x%08lx\n",pHalInfo->ddCaps.dwSVBFXCaps);
        for (t=0;t<DD_ROP_SPACE;t++)
        {
        printf(" pHalInfo->ddCaps.dwSVBRops[0x%04x]                : 0x%08lx\n",t,pHalInfo->ddCaps.dwSVBRops[t]);
        }

        printf(" pHalInfo->ddCaps.dwVSBCaps                        : ");
        flag = pHalInfo->ddCaps.dwVSBCaps;
        count = 0;   
        checkflag(flag,DDCAPS_3D,"DDCAPS_3D");
        checkflag(flag,DDCAPS_ALIGNBOUNDARYDEST,"DDCAPS_ALIGNBOUNDARYDEST");
        checkflag(flag,DDCAPS_ALIGNBOUNDARYSRC,"DDCAPS_ALIGNBOUNDARYSRC");
        checkflag(flag,DDCAPS_ALIGNSIZEDEST,"DDCAPS_ALIGNSIZEDEST");
        checkflag(flag,DDCAPS_ALIGNSIZESRC,"DDCAPS_ALIGNSIZESRC");
        checkflag(flag,DDCAPS_ALIGNSTRIDE,"DDCAPS_ALIGNSTRIDE");
        checkflag(flag,DDCAPS_ALPHA,"DDCAPS_ALPHA");
        checkflag(flag,DDCAPS_BANKSWITCHED,"DDCAPS_BANKSWITCHED");
        checkflag(flag,DDCAPS_BLT,"DDCAPS_BLT");
        checkflag(flag,DDCAPS_BLTCOLORFILL,"DDCAPS_BLTCOLORFILL");
        checkflag(flag,DDCAPS_BLTDEPTHFILL,"DDCAPS_BLTDEPTHFILL");
        checkflag(flag,DDCAPS_BLTFOURCC,"DDCAPS_BLTFOURCC");
        checkflag(flag,DDCAPS_BLTQUEUE,"DDCAPS_BLTQUEUE");
        checkflag(flag,DDCAPS_BLTSTRETCH,"DDCAPS_BLTSTRETCH");
        checkflag(flag,DDCAPS_CANBLTSYSMEM,"DDCAPS_CANBLTSYSMEM");
        checkflag(flag,DDCAPS_CANCLIP,"DDCAPS_CANCLIP");
        checkflag(flag,DDCAPS_CANCLIPSTRETCHED,"DDCAPS_CANCLIPSTRETCHED");
        checkflag(flag,DDCAPS_COLORKEY,"DDCAPS_COLORKEY");
        checkflag(flag,DDCAPS_COLORKEYHWASSIST,"DDCAPS_COLORKEYHWASSIST");
        checkflag(flag,DDCAPS_GDI,"DDCAPS_GDI");
        checkflag(flag,DDCAPS_NOHARDWARE,"DDCAPS_NOHARDWARE");
        checkflag(flag,DDCAPS_OVERLAY,"DDCAPS_OVERLAY");
        checkflag(flag,DDCAPS_OVERLAYCANTCLIP,"DDCAPS_OVERLAYCANTCLIP");
        checkflag(flag,DDCAPS_OVERLAYFOURCC,"DDCAPS_OVERLAYFOURCC");
        checkflag(flag,DDCAPS_OVERLAYSTRETCH,"DDCAPS_OVERLAYSTRETCH");
        checkflag(flag,DDCAPS_PALETTE,"DDCAPS_PALETTE");
        checkflag(flag,DDCAPS_PALETTEVSYNC,"DDCAPS_PALETTEVSYNC");
        checkflag(flag,DDCAPS_READSCANLINE,"DDCAPS_READSCANLINE");
        checkflag(flag,DDCAPS_STEREOVIEW,"DDCAPS_STEREOVIEW");
        checkflag(flag,DDCAPS_VBI,"DDCAPS_VBI");
        checkflag(flag,DDCAPS_ZBLTS,"DDCAPS_ZBLTS");
        checkflag(flag,DDCAPS_ZOVERLAYS,"DDCAPS_ZOVERLAYS");
        endcheckflag(flag,"pHalInfo->ddCaps.dwVSBCaps");

        printf(" pHalInfo->ddCaps.dwVSBCKeyCaps                    : 0x%08lx\n",pHalInfo->ddCaps.dwVSBCKeyCaps);
        printf(" pHalInfo->ddCaps.dwVSBFXCaps                      : 0x%08lx\n",pHalInfo->ddCaps.dwVSBFXCaps);
        for (t=0;t<DD_ROP_SPACE;t++)
        {
        printf(" pHalInfo->ddCaps.dwVSBRops[0x%04x]                : 0x%08lx\n",t,pHalInfo->ddCaps.dwVSBRops[t]);
        }
        printf(" pHalInfo->ddCaps.dwSSBCaps                        : 0x%08lx\n",pHalInfo->ddCaps.dwSSBCaps);
        printf(" pHalInfo->ddCaps.dwSSBCKeyCa                      : 0x%08lx\n",pHalInfo->ddCaps.dwSSBCKeyCaps);
        printf(" pHalInfo->ddCaps.dwSSBFXCaps                      : 0x%08lx\n",pHalInfo->ddCaps.dwSSBFXCaps);
        for (t=0;t<DD_ROP_SPACE;t++)
        {
        printf(" pHalInfo->ddCaps.dwSSBRops[0x%04x]                : 0x%08lx\n",t,pHalInfo->ddCaps.dwSSBRops[t]);
        }

        printf(" pHalInfo->GetDriverInfo                           : 0x%08lx\n",(long)pHalInfo->GetDriverInfo);
        printf(" pHalInfo->dwFlags                                 : ");

        flag = pHalInfo->dwFlags;
        count = 0;
        checkflag(flag,DDHALINFO_ISPRIMARYDISPLAY,"DDHALINFO_ISPRIMARYDISPLAY");
        checkflag(flag,DDHALINFO_MODEXILLEGAL,"DDHALINFO_MODEXILLEGAL");
        checkflag(flag,DDHALINFO_GETDRIVERINFOSET,"DDHALINFO_GETDRIVERINFOSET");
        checkflag(flag,DDHALINFO_GETDRIVERINFO2,"DDHALINFO_GETDRIVERINFO2");
        endcheckflag(flag,"pHalInfo->dwFlags");

        printf(" pHalInfo->lpD3DGlobalDriverData                   : 0x%08lx\n",(long)pHalInfo->lpD3DGlobalDriverData);
        printf(" pHalInfo->lpD3DHALCallbacks                       : 0x%08lx\n",(long)pHalInfo->lpD3DHALCallbacks);
        printf(" pHalInfo->lpD3DBufCallbacks                       : 0x%08lx\n",(long)pHalInfo->lpD3DBufCallbacks);
    }
    else
    {
        if (pHalInfo->dwSize !=0)
        {
            printf("unkonwn dwSize DD_HALINFO : the size found is 0x%08lx\n",pHalInfo->dwSize);
        }
        else
        {
            printf("none pHalInfo from the driver 0x%08lx\n",pHalInfo->dwSize);
        }
    }
}