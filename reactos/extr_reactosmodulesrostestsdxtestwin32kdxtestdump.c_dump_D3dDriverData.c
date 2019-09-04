#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_11__ {int dwSize; scalar_t__ dwStippleHeight; scalar_t__ dwStippleWidth; int /*<<< orphan*/  dwTextureAddressCaps; int /*<<< orphan*/  dwTextureBlendCaps; int /*<<< orphan*/  dwTextureFilterCaps; int /*<<< orphan*/  dwTextureCaps; int /*<<< orphan*/  dwShadeCaps; int /*<<< orphan*/  dwAlphaCmpCaps; int /*<<< orphan*/  dwDestBlendCaps; int /*<<< orphan*/  dwSrcBlendCaps; int /*<<< orphan*/  dwZCmpCaps; int /*<<< orphan*/  dwRasterCaps; int /*<<< orphan*/  dwMiscCaps; } ;
struct TYPE_10__ {int dwSize; scalar_t__ dwStippleHeight; scalar_t__ dwStippleWidth; int /*<<< orphan*/  dwTextureAddressCaps; int /*<<< orphan*/  dwTextureBlendCaps; int /*<<< orphan*/  dwTextureFilterCaps; int /*<<< orphan*/  dwTextureCaps; int /*<<< orphan*/  dwShadeCaps; int /*<<< orphan*/  dwAlphaCmpCaps; int /*<<< orphan*/  dwDestBlendCaps; int /*<<< orphan*/  dwSrcBlendCaps; int /*<<< orphan*/  dwZCmpCaps; int /*<<< orphan*/  dwRasterCaps; int /*<<< orphan*/  dwMiscCaps; } ;
struct TYPE_9__ {int dwSize; scalar_t__ dwNumLights; int /*<<< orphan*/  dwLightingModel; int /*<<< orphan*/  dwCaps; } ;
struct TYPE_8__ {int dwSize; int /*<<< orphan*/  dwCaps; } ;
struct TYPE_12__ {int dwSize; scalar_t__ dwMaxVertexCount; scalar_t__ dwMaxBufferSize; scalar_t__ dwDeviceZBufferBitDepth; scalar_t__ dwDeviceRenderBitDepth; TYPE_4__ dpcTriCaps; TYPE_3__ dpcLineCaps; TYPE_2__ dlcLightingCaps; TYPE_1__ dtcTransformCaps; int /*<<< orphan*/  dwDevCaps; scalar_t__ dcmColorModel; int /*<<< orphan*/  dwFlags; } ;
struct TYPE_13__ {int dwSize; scalar_t__ lpTextureFormats; scalar_t__ dwNumTextureFormats; scalar_t__ dwNumClipVertices; scalar_t__ dwNumVertices; TYPE_5__ hwCaps; } ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  D3DTRANSFORMCAPS ;
typedef  int /*<<< orphan*/  D3DPRIMCAPS ;
typedef  TYPE_6__ D3DNTHAL_GLOBALDRIVERDATA ;
typedef  int /*<<< orphan*/  D3DNTHALDEVICEDESC_V1 ;
typedef  int /*<<< orphan*/  D3DLIGHTINGCAPS ;

/* Variables and functions */
 int /*<<< orphan*/  D3DDD_BCLIPPING ; 
 int /*<<< orphan*/  D3DDD_COLORMODEL ; 
 int /*<<< orphan*/  D3DDD_DEVCAPS ; 
 int /*<<< orphan*/  D3DDD_DEVICERENDERBITDEPTH ; 
 int /*<<< orphan*/  D3DDD_DEVICEZBUFFERBITDEPTH ; 
 int /*<<< orphan*/  D3DDD_LIGHTINGCAPS ; 
 int /*<<< orphan*/  D3DDD_LINECAPS ; 
 int /*<<< orphan*/  D3DDD_MAXBUFFERSIZE ; 
 int /*<<< orphan*/  D3DDD_MAXVERTEXCOUNT ; 
 int /*<<< orphan*/  D3DDD_TRANSFORMCAPS ; 
 int /*<<< orphan*/  D3DDD_TRICAPS ; 
 int /*<<< orphan*/  D3DDEVCAPS_CANBLTSYSTONONLOCAL ; 
 int /*<<< orphan*/  D3DDEVCAPS_CANRENDERAFTERFLIP ; 
 int /*<<< orphan*/  D3DDEVCAPS_DRAWPRIMITIVES2 ; 
 int /*<<< orphan*/  D3DDEVCAPS_DRAWPRIMITIVES2EX ; 
 int /*<<< orphan*/  D3DDEVCAPS_DRAWPRIMTLVERTEX ; 
 int /*<<< orphan*/  D3DDEVCAPS_EXECUTESYSTEMMEMORY ; 
 int /*<<< orphan*/  D3DDEVCAPS_EXECUTEVIDEOMEMORY ; 
 int /*<<< orphan*/  D3DDEVCAPS_FLOATTLVERTEX ; 
 int /*<<< orphan*/  D3DDEVCAPS_HWRASTERIZATION ; 
 int /*<<< orphan*/  D3DDEVCAPS_HWTRANSFORMANDLIGHT ; 
 int /*<<< orphan*/  D3DDEVCAPS_SEPARATETEXTUREMEMORIES ; 
 int /*<<< orphan*/  D3DDEVCAPS_SORTDECREASINGZ ; 
 int /*<<< orphan*/  D3DDEVCAPS_SORTEXACT ; 
 int /*<<< orphan*/  D3DDEVCAPS_SORTINCREASINGZ ; 
 int /*<<< orphan*/  D3DDEVCAPS_TEXTURESYSTEMMEMORY ; 
 int /*<<< orphan*/  D3DDEVCAPS_TEXTUREVIDEOMEMORY ; 
 int /*<<< orphan*/  D3DDEVCAPS_TLVERTEXSYSTEMMEMORY ; 
 int /*<<< orphan*/  D3DDEVCAPS_TLVERTEXVIDEOMEMORY ; 
 int /*<<< orphan*/  D3DLIGHTCAPS_DIRECTIONAL ; 
 int /*<<< orphan*/  D3DLIGHTCAPS_GLSPOT ; 
 int /*<<< orphan*/  D3DLIGHTCAPS_PARALLELPOINT ; 
 int /*<<< orphan*/  D3DLIGHTCAPS_POINT ; 
 int /*<<< orphan*/  D3DLIGHTCAPS_SPOT ; 
 int /*<<< orphan*/  D3DLIGHTINGMODEL_MONO ; 
 int /*<<< orphan*/  D3DLIGHTINGMODEL_RGB ; 
 int /*<<< orphan*/  D3DPBLENDCAPS_BOTHINVSRCALPHA ; 
 int /*<<< orphan*/  D3DPBLENDCAPS_BOTHSRCALPHA ; 
 int /*<<< orphan*/  D3DPBLENDCAPS_DESTALPHA ; 
 int /*<<< orphan*/  D3DPBLENDCAPS_DESTCOLOR ; 
 int /*<<< orphan*/  D3DPBLENDCAPS_INVDESTALPHA ; 
 int /*<<< orphan*/  D3DPBLENDCAPS_INVDESTCOLOR ; 
 int /*<<< orphan*/  D3DPBLENDCAPS_INVSRCALPHA ; 
 int /*<<< orphan*/  D3DPBLENDCAPS_INVSRCCOLOR ; 
 int /*<<< orphan*/  D3DPBLENDCAPS_ONE ; 
 int /*<<< orphan*/  D3DPBLENDCAPS_SRCALPHA ; 
 int /*<<< orphan*/  D3DPBLENDCAPS_SRCALPHASAT ; 
 int /*<<< orphan*/  D3DPBLENDCAPS_SRCCOLOR ; 
 int /*<<< orphan*/  D3DPBLENDCAPS_ZERO ; 
 int /*<<< orphan*/  D3DPCMPCAPS_ALWAYS ; 
 int /*<<< orphan*/  D3DPCMPCAPS_EQUAL ; 
 int /*<<< orphan*/  D3DPCMPCAPS_GREATER ; 
 int /*<<< orphan*/  D3DPCMPCAPS_GREATEREQUAL ; 
 int /*<<< orphan*/  D3DPCMPCAPS_LESS ; 
 int /*<<< orphan*/  D3DPCMPCAPS_LESSEQUAL ; 
 int /*<<< orphan*/  D3DPCMPCAPS_NEVER ; 
 int /*<<< orphan*/  D3DPCMPCAPS_NOTEQUAL ; 
 int /*<<< orphan*/  D3DPMISCCAPS_CONFORMANT ; 
 int /*<<< orphan*/  D3DPMISCCAPS_CULLCCW ; 
 int /*<<< orphan*/  D3DPMISCCAPS_CULLCW ; 
 int /*<<< orphan*/  D3DPMISCCAPS_CULLNONE ; 
 int /*<<< orphan*/  D3DPMISCCAPS_LINEPATTERNREP ; 
 int /*<<< orphan*/  D3DPMISCCAPS_MASKPLANES ; 
 int /*<<< orphan*/  D3DPMISCCAPS_MASKZ ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_ANISOTROPY ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_ANTIALIASEDGES ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_ANTIALIASSORTDEPENDENT ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_ANTIALIASSORTINDEPENDENT ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_DITHER ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_FOGRANGE ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_FOGTABLE ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_FOGVERTEX ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_PAT ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_ROP2 ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_STIPPLE ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_SUBPIXEL ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_SUBPIXELX ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_TRANSLUCENTSORTINDEPENDENT ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_WBUFFER ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_WFOG ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_XOR ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_ZBIAS ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_ZBUFFERLESSHSR ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_ZFOG ; 
 int /*<<< orphan*/  D3DPRASTERCAPS_ZTEST ; 
 int /*<<< orphan*/  D3DPSHADECAPS_ALPHAFLATBLEND ; 
 int /*<<< orphan*/  D3DPSHADECAPS_ALPHAFLATSTIPPLED ; 
 int /*<<< orphan*/  D3DPSHADECAPS_ALPHAGOURAUDBLEND ; 
 int /*<<< orphan*/  D3DPSHADECAPS_ALPHAGOURAUDSTIPPLED ; 
 int /*<<< orphan*/  D3DPSHADECAPS_ALPHAPHONGBLEND ; 
 int /*<<< orphan*/  D3DPSHADECAPS_ALPHAPHONGSTIPPLED ; 
 int /*<<< orphan*/  D3DPSHADECAPS_COLORFLATMONO ; 
 int /*<<< orphan*/  D3DPSHADECAPS_COLORFLATRGB ; 
 int /*<<< orphan*/  D3DPSHADECAPS_COLORGOURAUDMONO ; 
 int /*<<< orphan*/  D3DPSHADECAPS_COLORGOURAUDRGB ; 
 int /*<<< orphan*/  D3DPSHADECAPS_COLORPHONGMONO ; 
 int /*<<< orphan*/  D3DPSHADECAPS_COLORPHONGRGB ; 
 int /*<<< orphan*/  D3DPSHADECAPS_FOGFLAT ; 
 int /*<<< orphan*/  D3DPSHADECAPS_FOGGOURAUD ; 
 int /*<<< orphan*/  D3DPSHADECAPS_FOGPHONG ; 
 int /*<<< orphan*/  D3DPSHADECAPS_SPECULARFLATMONO ; 
 int /*<<< orphan*/  D3DPSHADECAPS_SPECULARFLATRGB ; 
 int /*<<< orphan*/  D3DPSHADECAPS_SPECULARGOURAUDMONO ; 
 int /*<<< orphan*/  D3DPSHADECAPS_SPECULARGOURAUDRGB ; 
 int /*<<< orphan*/  D3DPSHADECAPS_SPECULARPHONGMONO ; 
 int /*<<< orphan*/  D3DPSHADECAPS_SPECULARPHONGRGB ; 
 int /*<<< orphan*/  D3DPTADDRESSCAPS_BORDER ; 
 int /*<<< orphan*/  D3DPTADDRESSCAPS_CLAMP ; 
 int /*<<< orphan*/  D3DPTADDRESSCAPS_INDEPENDENTUV ; 
 int /*<<< orphan*/  D3DPTADDRESSCAPS_MIRROR ; 
 int /*<<< orphan*/  D3DPTADDRESSCAPS_WRAP ; 
 int /*<<< orphan*/  D3DPTBLENDCAPS_ADD ; 
 int /*<<< orphan*/  D3DPTBLENDCAPS_COPY ; 
 int /*<<< orphan*/  D3DPTBLENDCAPS_DECAL ; 
 int /*<<< orphan*/  D3DPTBLENDCAPS_DECALALPHA ; 
 int /*<<< orphan*/  D3DPTBLENDCAPS_DECALMASK ; 
 int /*<<< orphan*/  D3DPTBLENDCAPS_MODULATE ; 
 int /*<<< orphan*/  D3DPTBLENDCAPS_MODULATEALPHA ; 
 int /*<<< orphan*/  D3DPTBLENDCAPS_MODULATEMASK ; 
 int /*<<< orphan*/  D3DPTEXTURECAPS_ALPHA ; 
 int /*<<< orphan*/  D3DPTEXTURECAPS_ALPHAPALETTE ; 
 int /*<<< orphan*/  D3DPTEXTURECAPS_BORDER ; 
 int /*<<< orphan*/  D3DPTEXTURECAPS_COLORKEYBLEND ; 
 int /*<<< orphan*/  D3DPTEXTURECAPS_CUBEMAP ; 
 int /*<<< orphan*/  D3DPTEXTURECAPS_NONPOW2CONDITIONAL ; 
 int /*<<< orphan*/  D3DPTEXTURECAPS_PERSPECTIVE ; 
 int /*<<< orphan*/  D3DPTEXTURECAPS_POW2 ; 
 int /*<<< orphan*/  D3DPTEXTURECAPS_PROJECTED ; 
 int /*<<< orphan*/  D3DPTEXTURECAPS_SQUAREONLY ; 
 int /*<<< orphan*/  D3DPTEXTURECAPS_TRANSPARENCY ; 
 int /*<<< orphan*/  D3DPTFILTERCAPS_LINEAR ; 
 int /*<<< orphan*/  D3DPTFILTERCAPS_LINEARMIPLINEAR ; 
 int /*<<< orphan*/  D3DPTFILTERCAPS_LINEARMIPNEAREST ; 
 int /*<<< orphan*/  D3DPTFILTERCAPS_MAGFAFLATCUBIC ; 
 int /*<<< orphan*/  D3DPTFILTERCAPS_MAGFANISOTROPIC ; 
 int /*<<< orphan*/  D3DPTFILTERCAPS_MAGFGAUSSIANCUBIC ; 
 int /*<<< orphan*/  D3DPTFILTERCAPS_MAGFLINEAR ; 
 int /*<<< orphan*/  D3DPTFILTERCAPS_MAGFPOINT ; 
 int /*<<< orphan*/  D3DPTFILTERCAPS_MINFANISOTROPIC ; 
 int /*<<< orphan*/  D3DPTFILTERCAPS_MINFLINEAR ; 
 int /*<<< orphan*/  D3DPTFILTERCAPS_MINFPOINT ; 
 int /*<<< orphan*/  D3DPTFILTERCAPS_MIPFLINEAR ; 
 int /*<<< orphan*/  D3DPTFILTERCAPS_MIPFPOINT ; 
 int /*<<< orphan*/  D3DPTFILTERCAPS_MIPLINEAR ; 
 int /*<<< orphan*/  D3DPTFILTERCAPS_MIPNEAREST ; 
 int /*<<< orphan*/  D3DPTFILTERCAPS_NEAREST ; 
 int /*<<< orphan*/  D3DTRANSFORMCAPS_CLIP ; 
 int /*<<< orphan*/  checkflag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  endcheckflag (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
dump_D3dDriverData(D3DNTHAL_GLOBALDRIVERDATA *puD3dDriverData, char *text)
{
    UINT flag = 0;
    INT count = 0;

    printf("dumping the D3DNTHAL_GLOBALDRIVERDATA from %s\n",text);
    if (puD3dDriverData->dwSize ==  sizeof(D3DNTHAL_GLOBALDRIVERDATA))
    {
        printf(" puD3dDriverData->dwSize                                        : 0x%08lx\n",(long)puD3dDriverData->dwSize);
        if (puD3dDriverData->hwCaps.dwSize == sizeof(D3DNTHALDEVICEDESC_V1))
        {
            printf(" puD3dDriverData->hwCaps.dwSize                                 : 0x%08lx\n",(long)puD3dDriverData->hwCaps.dwSize);
            printf(" puD3dDriverData->hwCaps.dwFlags                                : ");

            flag = puD3dDriverData->hwCaps.dwFlags;
            checkflag(flag,D3DDD_BCLIPPING,"D3DDD_BCLIPPING");
            checkflag(flag,D3DDD_COLORMODEL,"D3DDD_COLORMODEL");
            checkflag(flag,D3DDD_DEVCAPS,"D3DDD_DEVCAPS");
            checkflag(flag,D3DDD_DEVICERENDERBITDEPTH,"D3DDD_DEVICERENDERBITDEPTH");
            checkflag(flag,D3DDD_DEVICEZBUFFERBITDEPTH,"D3DDD_DEVICEZBUFFERBITDEPTH");
            checkflag(flag,D3DDD_LIGHTINGCAPS,"D3DDD_LIGHTINGCAPS");
            checkflag(flag,D3DDD_LINECAPS,"D3DDD_LINECAPS");
            checkflag(flag,D3DDD_MAXBUFFERSIZE,"D3DDD_MAXBUFFERSIZE");
            checkflag(flag,D3DDD_MAXVERTEXCOUNT,"D3DDD_MAXVERTEXCOUNT");
            checkflag(flag,D3DDD_TRANSFORMCAPS,"D3DDD_TRANSFORMCAPS");
            checkflag(flag,D3DDD_TRICAPS,"D3DDD_TRICAPS");
            endcheckflag(flag,"puD3dDriverData->hwCaps.dwFlags ");
             
            printf(" puD3dDriverData->hwCaps.dcmColorModel                          : 0x%08lx\n",(long)puD3dDriverData->hwCaps.dcmColorModel);
            printf(" puD3dDriverData->hwCaps.dwDevCaps                              : ");

            count = 0;
            flag = puD3dDriverData->hwCaps.dwDevCaps;
            checkflag(flag,D3DDEVCAPS_CANBLTSYSTONONLOCAL,"D3DDEVCAPS_CANBLTSYSTONONLOCAL");
            checkflag(flag,D3DDEVCAPS_CANRENDERAFTERFLIP,"D3DDEVCAPS_CANRENDERAFTERFLIP");
            checkflag(flag,D3DDEVCAPS_DRAWPRIMITIVES2,"D3DDEVCAPS_DRAWPRIMITIVES2");
            checkflag(flag,D3DDEVCAPS_DRAWPRIMITIVES2EX,"D3DDEVCAPS_DRAWPRIMITIVES2EX");
            checkflag(flag,D3DDEVCAPS_DRAWPRIMTLVERTEX,"D3DDEVCAPS_DRAWPRIMTLVERTEX");
            checkflag(flag,D3DDEVCAPS_EXECUTESYSTEMMEMORY,"D3DDEVCAPS_EXECUTESYSTEMMEMORY");
            checkflag(flag,D3DDEVCAPS_EXECUTEVIDEOMEMORY,"D3DDEVCAPS_EXECUTEVIDEOMEMORY");
            checkflag(flag,D3DDEVCAPS_FLOATTLVERTEX,"D3DDEVCAPS_FLOATTLVERTEX");
            checkflag(flag,D3DDEVCAPS_HWRASTERIZATION,"D3DDEVCAPS_HWRASTERIZATION");
            checkflag(flag,D3DDEVCAPS_HWTRANSFORMANDLIGHT,"D3DDEVCAPS_HWTRANSFORMANDLIGHT");
            checkflag(flag,D3DDEVCAPS_SEPARATETEXTUREMEMORIES,"D3DDEVCAPS_SEPARATETEXTUREMEMORIES");
            checkflag(flag,D3DDEVCAPS_SORTDECREASINGZ,"D3DDEVCAPS_SORTDECREASINGZ");
            checkflag(flag,D3DDEVCAPS_SORTEXACT,"D3DDEVCAPS_SORTEXACT");
            checkflag(flag,D3DDEVCAPS_SORTINCREASINGZ,"D3DDEVCAPS_SORTINCREASINGZ");
            // not in ddk or dxsdk I have but it is msdn checkflag(flag,D3DDEVCAPS_TEXTURENONLOCALVIDEOMEMORY,"D3DDEVCAPS_TEXTURENONLOCALVIDEOMEMORY");
            checkflag(flag,D3DDEVCAPS_TLVERTEXSYSTEMMEMORY,"D3DDEVCAPS_TLVERTEXSYSTEMMEMORY");
            checkflag(flag,D3DDEVCAPS_TLVERTEXVIDEOMEMORY,"D3DDEVCAPS_TLVERTEXVIDEOMEMORY");
            checkflag(flag,D3DDEVCAPS_TEXTURESYSTEMMEMORY,"D3DDEVCAPS_TEXTURESYSTEMMEMORY");
            checkflag(flag,D3DDEVCAPS_TEXTUREVIDEOMEMORY,"D3DDEVCAPS_TEXTUREVIDEOMEMORY");
            endcheckflag(flag,"puD3dDriverData->hwCaps.dwDevCaps");
            
            if (puD3dDriverData->hwCaps.dtcTransformCaps.dwSize == sizeof(D3DTRANSFORMCAPS))
            {
                printf(" puD3dDriverData->hwCaps.dtcTransformCaps.dwSize                : 0x%08lx\n",(long) puD3dDriverData->hwCaps.dtcTransformCaps.dwSize);
                printf(" puD3dDriverData->hwCaps.dtcTransformCaps.dwCaps                : ");

                count = 0;
                flag = puD3dDriverData->hwCaps.dtcTransformCaps.dwCaps;
                checkflag(flag,D3DTRANSFORMCAPS_CLIP,"D3DTRANSFORMCAPS_CLIP");
                endcheckflag(flag,"puD3dDriverData->hwCaps.dtcTransformCaps.dwCaps");                 
            }
            else
            {
                printf("none puD3dDriverData->hwCaps.dtcTransformCaps.dwSize from the driver 0x%08lx\n",puD3dDriverData->hwCaps.dtcTransformCaps.dwSize);
            }

            if (puD3dDriverData->hwCaps.dlcLightingCaps.dwSize == sizeof(D3DLIGHTINGCAPS))
            {
                printf(" puD3dDriverData->hwCaps.dlcLightingCaps.dwSize                 : 0x%08lx\n",(long)puD3dDriverData->hwCaps.dlcLightingCaps.dwSize);
                printf(" puD3dDriverData->hwCaps.dlcLightingCaps.dwCaps                 : ");

                count = 0;
                flag = puD3dDriverData->hwCaps.dlcLightingCaps.dwCaps;

                checkflag(flag,D3DLIGHTCAPS_DIRECTIONAL,"D3DLIGHTCAPS_DIRECTIONAL");
                checkflag(flag,D3DLIGHTCAPS_GLSPOT,"D3DLIGHTCAPS_GLSPOT");
                checkflag(flag,D3DLIGHTCAPS_PARALLELPOINT,"D3DLIGHTCAPS_PARALLELPOINT");
                checkflag(flag,D3DLIGHTCAPS_POINT,"D3DLIGHTCAPS_POINT");
                checkflag(flag,D3DLIGHTCAPS_SPOT,"D3DLIGHTCAPS_SPOT");
                endcheckflag(flag,"puD3dDriverData->hwCaps.dlcLightingCaps.dwCaps");         
                
                printf(" puD3dDriverData->hwCaps.dlcLightingCaps.dwLightingModel        : ");

                count = 0;
                flag = puD3dDriverData->hwCaps.dlcLightingCaps.dwLightingModel;

                checkflag(flag,D3DLIGHTINGMODEL_MONO,"D3DLIGHTINGMODEL_MONO");
                checkflag(flag,D3DLIGHTINGMODEL_RGB,"D3DLIGHTINGMODEL_RGB");
                endcheckflag(flag,"puD3dDriverData->hwCaps.dlcLightingCaps.dwLightingModel"); 
               
                printf(" puD3dDriverData->hwCaps.dlcLightingCaps.dwNumLights            : 0x%08lx\n",(long)puD3dDriverData->hwCaps.dlcLightingCaps.dwNumLights);
            }
            else
            {
                printf("none puD3dDriverData->hwCaps.dlcLightingCaps.dwSize from the driver 0x%08lx\n",puD3dDriverData->hwCaps.dlcLightingCaps.dwSize);
            }


            if (puD3dDriverData->hwCaps.dpcLineCaps.dwSize == sizeof(D3DPRIMCAPS))
            {
                printf(" puD3dDriverData->hwCaps.dpcLineCaps.dwSize                     : 0x%08lx\n",(long)puD3dDriverData->hwCaps.dpcLineCaps.dwSize);

                printf(" puD3dDriverData->hwCaps.dpcLineCaps.dwMiscCaps                 : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcLineCaps.dwMiscCaps;
                checkflag(flag,D3DPMISCCAPS_CONFORMANT,"D3DPMISCCAPS_CONFORMANT");
                checkflag(flag,D3DPMISCCAPS_CULLCCW,"D3DPMISCCAPS_CULLCCW");
                checkflag(flag,D3DPMISCCAPS_CULLCW,"D3DPMISCCAPS_CULLCW");
                checkflag(flag,D3DPMISCCAPS_CULLNONE,"D3DPMISCCAPS_CULLNONE");
                checkflag(flag,D3DPMISCCAPS_LINEPATTERNREP,"D3DPMISCCAPS_LINEPATTERNREP");
                checkflag(flag,D3DPMISCCAPS_MASKPLANES,"D3DPMISCCAPS_MASKPLANES");
                checkflag(flag,D3DPMISCCAPS_MASKZ,"D3DPMISCCAPS_MASKZ");
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcLineCaps.dwMiscCaps"); 

                printf(" puD3dDriverData->hwCaps.dpcLineCaps.dwRasterCaps               : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcLineCaps.dwRasterCaps;
                checkflag(flag,D3DPRASTERCAPS_ANISOTROPY,"D3DPRASTERCAPS_ANISOTROPY");
                checkflag(flag,D3DPRASTERCAPS_ANTIALIASEDGES,"D3DPRASTERCAPS_ANTIALIASEDGES");
                checkflag(flag,D3DPRASTERCAPS_ANTIALIASSORTDEPENDENT,"D3DPRASTERCAPS_ANTIALIASSORTDEPENDENT");
                checkflag(flag,D3DPRASTERCAPS_ANTIALIASSORTINDEPENDENT,"D3DPRASTERCAPS_ANTIALIASSORTINDEPENDENT");
                checkflag(flag,D3DPRASTERCAPS_DITHER,"D3DPRASTERCAPS_DITHER");
                checkflag(flag,D3DPRASTERCAPS_FOGRANGE,"D3DPRASTERCAPS_FOGRANGE");
                checkflag(flag,D3DPRASTERCAPS_FOGTABLE,"D3DPRASTERCAPS_FOGTABLE");
                checkflag(flag,D3DPRASTERCAPS_FOGVERTEX,"D3DPRASTERCAPS_FOGVERTEX");
                checkflag(flag,D3DPRASTERCAPS_PAT,"D3DPRASTERCAPS_PAT");
                checkflag(flag,D3DPRASTERCAPS_ROP2,"D3DPRASTERCAPS_ROP2");
                checkflag(flag,D3DPRASTERCAPS_STIPPLE,"D3DPRASTERCAPS_STIPPLE");
                checkflag(flag,D3DPRASTERCAPS_SUBPIXEL,"D3DPRASTERCAPS_SUBPIXEL");
                checkflag(flag,D3DPRASTERCAPS_SUBPIXELX,"D3DPRASTERCAPS_SUBPIXELX");
                checkflag(flag,D3DPRASTERCAPS_TRANSLUCENTSORTINDEPENDENT,"D3DPRASTERCAPS_TRANSLUCENTSORTINDEPENDENT");
                checkflag(flag,D3DPRASTERCAPS_WBUFFER,"D3DPRASTERCAPS_WBUFFER");
                checkflag(flag,D3DPRASTERCAPS_WFOG,"D3DPRASTERCAPS_WFOG");
                checkflag(flag,D3DPRASTERCAPS_XOR,"D3DPRASTERCAPS_XOR");
                checkflag(flag,D3DPRASTERCAPS_ZBIAS,"D3DPRASTERCAPS_ZBIAS");
                checkflag(flag,D3DPRASTERCAPS_ZBUFFERLESSHSR,"D3DPRASTERCAPS_ZBUFFERLESSHSR");
                checkflag(flag,D3DPRASTERCAPS_ZFOG,"D3DPRASTERCAPS_ZFOG");
                checkflag(flag,D3DPRASTERCAPS_ZTEST,"D3DPRASTERCAPS_ZTEST");               
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcLineCaps.dwRasterCaps"); 

                printf(" puD3dDriverData->hwCaps.dpcLineCaps.dwZCmpCaps                 : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcLineCaps.dwZCmpCaps;
                checkflag(flag,D3DPCMPCAPS_ALWAYS,"D3DPCMPCAPS_ALWAYS");
                checkflag(flag,D3DPCMPCAPS_EQUAL,"D3DPCMPCAPS_EQUAL");
                checkflag(flag,D3DPCMPCAPS_GREATER,"D3DPCMPCAPS_GREATER");
                checkflag(flag,D3DPCMPCAPS_GREATEREQUAL,"D3DPCMPCAPS_GREATEREQUAL");
                checkflag(flag,D3DPCMPCAPS_LESS,"D3DPCMPCAPS_LESS");
                checkflag(flag,D3DPCMPCAPS_LESSEQUAL,"D3DPCMPCAPS_LESSEQUAL");
                checkflag(flag,D3DPCMPCAPS_NEVER,"D3DPCMPCAPS_NEVER");
                checkflag(flag,D3DPCMPCAPS_NOTEQUAL,"D3DPCMPCAPS_NOTEQUAL");               
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcLineCaps.dwZCmpCaps "); 
                               
                printf(" puD3dDriverData->hwCaps.dpcLineCaps.dwSrcBlendCaps             : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcLineCaps.dwSrcBlendCaps;
                checkflag(flag,D3DPBLENDCAPS_BOTHINVSRCALPHA,"D3DPBLENDCAPS_BOTHINVSRCALPHA");
                checkflag(flag,D3DPBLENDCAPS_BOTHSRCALPHA,"D3DPBLENDCAPS_BOTHSRCALPHA");
                checkflag(flag,D3DPBLENDCAPS_DESTALPHA,"D3DPBLENDCAPS_DESTALPHA");
                checkflag(flag,D3DPBLENDCAPS_DESTCOLOR,"D3DPBLENDCAPS_DESTCOLOR");
                checkflag(flag,D3DPBLENDCAPS_INVDESTALPHA,"D3DPBLENDCAPS_INVDESTALPHA");
                checkflag(flag,D3DPBLENDCAPS_INVDESTCOLOR,"D3DPBLENDCAPS_INVDESTCOLOR");
                checkflag(flag,D3DPBLENDCAPS_INVSRCALPHA,"D3DPBLENDCAPS_INVSRCALPHA");
                checkflag(flag,D3DPBLENDCAPS_INVSRCCOLOR,"D3DPBLENDCAPS_INVSRCCOLOR");   
                checkflag(flag,D3DPBLENDCAPS_ONE,"D3DPBLENDCAPS_ONE");
                checkflag(flag,D3DPBLENDCAPS_SRCALPHA,"D3DPBLENDCAPS_SRCALPHA");
                checkflag(flag,D3DPBLENDCAPS_SRCALPHASAT,"D3DPBLENDCAPS_SRCALPHASAT");
                checkflag(flag,D3DPBLENDCAPS_SRCCOLOR,"D3DPBLENDCAPS_SRCCOLOR");
                checkflag(flag,D3DPBLENDCAPS_ZERO,"D3DPBLENDCAPS_ZERO");            
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcLineCaps.dwSrcBlendCaps "); 

                printf(" puD3dDriverData->hwCaps.dpcLineCaps.dwDestBlendCaps            : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcLineCaps.dwDestBlendCaps;
                checkflag(flag,D3DPBLENDCAPS_BOTHINVSRCALPHA,"D3DPBLENDCAPS_BOTHINVSRCALPHA");
                checkflag(flag,D3DPBLENDCAPS_BOTHSRCALPHA,"D3DPBLENDCAPS_BOTHSRCALPHA");
                checkflag(flag,D3DPBLENDCAPS_DESTALPHA,"D3DPBLENDCAPS_DESTALPHA");
                checkflag(flag,D3DPBLENDCAPS_DESTCOLOR,"D3DPBLENDCAPS_DESTCOLOR");
                checkflag(flag,D3DPBLENDCAPS_INVDESTALPHA,"D3DPBLENDCAPS_INVDESTALPHA");
                checkflag(flag,D3DPBLENDCAPS_INVDESTCOLOR,"D3DPBLENDCAPS_INVDESTCOLOR");
                checkflag(flag,D3DPBLENDCAPS_INVSRCALPHA,"D3DPBLENDCAPS_INVSRCALPHA");
                checkflag(flag,D3DPBLENDCAPS_INVSRCCOLOR,"D3DPBLENDCAPS_INVSRCCOLOR");   
                checkflag(flag,D3DPBLENDCAPS_ONE,"D3DPBLENDCAPS_ONE");
                checkflag(flag,D3DPBLENDCAPS_SRCALPHA,"D3DPBLENDCAPS_SRCALPHA");
                checkflag(flag,D3DPBLENDCAPS_SRCALPHASAT,"D3DPBLENDCAPS_SRCALPHASAT");
                checkflag(flag,D3DPBLENDCAPS_SRCCOLOR,"D3DPBLENDCAPS_SRCCOLOR");
                checkflag(flag,D3DPBLENDCAPS_ZERO,"D3DPBLENDCAPS_ZERO");            
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcLineCaps.dwDestBlendCaps "); 

                printf(" puD3dDriverData->hwCaps.dpcLineCaps.dwAlphaCmpCaps             : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcLineCaps.dwAlphaCmpCaps;
                checkflag(flag,D3DPCMPCAPS_ALWAYS,"D3DPCMPCAPS_ALWAYS");
                checkflag(flag,D3DPCMPCAPS_EQUAL,"D3DPCMPCAPS_EQUAL");
                checkflag(flag,D3DPCMPCAPS_GREATER,"D3DPCMPCAPS_GREATER");
                checkflag(flag,D3DPCMPCAPS_GREATEREQUAL,"D3DPCMPCAPS_GREATEREQUAL");
                checkflag(flag,D3DPCMPCAPS_LESS,"D3DPCMPCAPS_LESS");
                checkflag(flag,D3DPCMPCAPS_LESSEQUAL,"D3DPCMPCAPS_LESSEQUAL");
                checkflag(flag,D3DPCMPCAPS_NEVER,"D3DPCMPCAPS_NEVER");
                checkflag(flag,D3DPCMPCAPS_NOTEQUAL,"D3DPCMPCAPS_NOTEQUAL");               
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcLineCaps.dwAlphaCmpCaps "); 

                printf(" puD3dDriverData->hwCaps.dpcLineCaps.dwShadeCaps                : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcLineCaps.dwShadeCaps;
                checkflag(flag,D3DPSHADECAPS_ALPHAFLATBLEND,"D3DPSHADECAPS_ALPHAFLATBLEND");
                checkflag(flag,D3DPSHADECAPS_ALPHAFLATSTIPPLED,"D3DPSHADECAPS_ALPHAFLATSTIPPLED");
                checkflag(flag,D3DPSHADECAPS_ALPHAGOURAUDBLEND,"D3DPSHADECAPS_ALPHAGOURAUDBLEND");
                checkflag(flag,D3DPSHADECAPS_ALPHAGOURAUDSTIPPLED,"D3DPSHADECAPS_ALPHAGOURAUDSTIPPLED");
                checkflag(flag,D3DPSHADECAPS_ALPHAPHONGBLEND,"D3DPSHADECAPS_ALPHAPHONGBLEND");
                checkflag(flag,D3DPSHADECAPS_ALPHAPHONGSTIPPLED,"D3DPSHADECAPS_ALPHAPHONGSTIPPLED");
                checkflag(flag,D3DPSHADECAPS_COLORFLATMONO,"D3DPSHADECAPS_COLORFLATMONO");
                checkflag(flag,D3DPSHADECAPS_COLORFLATRGB,"D3DPSHADECAPS_COLORFLATRGB");       
                checkflag(flag,D3DPSHADECAPS_COLORGOURAUDMONO,"D3DPSHADECAPS_COLORGOURAUDMONO");
                checkflag(flag,D3DPSHADECAPS_COLORGOURAUDRGB,"D3DPSHADECAPS_COLORGOURAUDRGB");
                checkflag(flag,D3DPSHADECAPS_COLORPHONGMONO,"D3DPSHADECAPS_COLORPHONGMONO");
                checkflag(flag,D3DPSHADECAPS_COLORPHONGRGB,"D3DPSHADECAPS_COLORPHONGRGB");
                checkflag(flag,D3DPSHADECAPS_FOGFLAT,"D3DPSHADECAPS_FOGFLAT");
                checkflag(flag,D3DPSHADECAPS_FOGGOURAUD,"D3DPSHADECAPS_FOGGOURAUD");
                checkflag(flag,D3DPSHADECAPS_FOGPHONG,"D3DPSHADECAPS_FOGPHONG");
                checkflag(flag,D3DPSHADECAPS_SPECULARFLATMONO,"D3DPSHADECAPS_SPECULARFLATMONO"); 
                checkflag(flag,D3DPSHADECAPS_SPECULARFLATRGB,"D3DPSHADECAPS_SPECULARFLATRGB"); 
                checkflag(flag,D3DPSHADECAPS_SPECULARGOURAUDMONO,"D3DPSHADECAPS_SPECULARGOURAUDMONO");
                checkflag(flag,D3DPSHADECAPS_SPECULARGOURAUDRGB,"D3DPSHADECAPS_SPECULARGOURAUDRGB");
                checkflag(flag,D3DPSHADECAPS_SPECULARPHONGMONO,"D3DPSHADECAPS_SPECULARPHONGMONO"); 
                checkflag(flag,D3DPSHADECAPS_SPECULARPHONGRGB,"D3DPSHADECAPS_SPECULARPHONGRGB"); 
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcLineCaps.dwShadeCaps "); 

                printf(" puD3dDriverData->hwCaps.dpcLineCaps.dwTextureCaps              : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcLineCaps.dwTextureCaps;
                checkflag(flag,D3DPTEXTURECAPS_ALPHA,"D3DPTEXTURECAPS_ALPHA");
                checkflag(flag,D3DPTEXTURECAPS_ALPHAPALETTE,"D3DPTEXTURECAPS_ALPHAPALETTE");
                checkflag(flag,D3DPTEXTURECAPS_BORDER,"D3DPTEXTURECAPS_BORDER");
                checkflag(flag,D3DPTEXTURECAPS_COLORKEYBLEND,"D3DPTEXTURECAPS_COLORKEYBLEND");
                checkflag(flag,D3DPTEXTURECAPS_CUBEMAP,"D3DPTEXTURECAPS_CUBEMAP");
                checkflag(flag,D3DPTEXTURECAPS_PERSPECTIVE,"D3DPTEXTURECAPS_PERSPECTIVE");
                checkflag(flag,D3DPTEXTURECAPS_POW2,"D3DPTEXTURECAPS_POW2");
                checkflag(flag,D3DPTEXTURECAPS_PROJECTED,"D3DPTEXTURECAPS_PROJECTED");       
                checkflag(flag,D3DPTEXTURECAPS_NONPOW2CONDITIONAL,"D3DPTEXTURECAPS_NONPOW2CONDITIONAL");
                checkflag(flag,D3DPTEXTURECAPS_SQUAREONLY,"D3DPTEXTURECAPS_SQUAREONLY");
                // not in ddk or dxsdk but it is in msdn checkflag(flag,D3DPTEXTURECAPS_TEXREPEATNOTSCALESBYSIZE,"D3DPTEXTURECAPS_TEXREPEATNOTSCALESBYSIZE");
                // not in ddk or dxsdk but it is in msdn checkflag(flag,D3DPTEXTURECAPS_TEXTURETRANSFORM,"D3DPTEXTURECAPS_TEXTURETRANSFORM");
                checkflag(flag,D3DPTEXTURECAPS_TRANSPARENCY,"D3DPTEXTURECAPS_TRANSPARENCY");
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcLineCaps.dwTextureCaps "); 

                printf(" puD3dDriverData->hwCaps.dpcLineCaps.dwTextureFilterCaps        : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcLineCaps.dwTextureFilterCaps;
                checkflag(flag,D3DPTFILTERCAPS_LINEAR,"D3DPTFILTERCAPS_LINEAR");
                checkflag(flag,D3DPTFILTERCAPS_LINEARMIPLINEAR,"D3DPTFILTERCAPS_LINEARMIPLINEAR");
                checkflag(flag,D3DPTFILTERCAPS_LINEARMIPNEAREST,"D3DPTFILTERCAPS_LINEARMIPNEAREST");
                checkflag(flag,D3DPTFILTERCAPS_MAGFAFLATCUBIC,"D3DPTFILTERCAPS_MAGFAFLATCUBIC");
                checkflag(flag,D3DPTFILTERCAPS_MAGFANISOTROPIC,"D3DPTFILTERCAPS_MAGFANISOTROPIC");
                checkflag(flag,D3DPTFILTERCAPS_MAGFGAUSSIANCUBIC,"D3DPTFILTERCAPS_MAGFGAUSSIANCUBIC");
                checkflag(flag,D3DPTFILTERCAPS_MAGFLINEAR,"D3DPTFILTERCAPS_MAGFLINEAR");
                checkflag(flag,D3DPTFILTERCAPS_MAGFPOINT,"D3DPTFILTERCAPS_MAGFPOINT");       
                checkflag(flag,D3DPTFILTERCAPS_MINFANISOTROPIC,"D3DPTFILTERCAPS_MINFANISOTROPIC");
                checkflag(flag,D3DPTFILTERCAPS_MINFLINEAR,"D3DPTFILTERCAPS_MINFLINEAR");
                checkflag(flag,D3DPTFILTERCAPS_MINFPOINT,"D3DPTFILTERCAPS_MINFPOINT");
                checkflag(flag,D3DPTFILTERCAPS_MIPFLINEAR,"D3DPTFILTERCAPS_MIPFLINEAR");
                checkflag(flag,D3DPTFILTERCAPS_MIPFPOINT,"D3DPTFILTERCAPS_MIPFPOINT");
                checkflag(flag,D3DPTFILTERCAPS_MIPLINEAR,"D3DPTFILTERCAPS_MIPLINEAR");
                checkflag(flag,D3DPTFILTERCAPS_MIPNEAREST,"D3DPTFILTERCAPS_MIPNEAREST");
                checkflag(flag,D3DPTFILTERCAPS_NEAREST,"D3DPTFILTERCAPS_NEAREST");
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcLineCaps.dwTextureFilterCaps "); 

                printf(" puD3dDriverData->hwCaps.dpcLineCaps.dwTextureBlendCaps         : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcLineCaps.dwTextureBlendCaps;
                checkflag(flag,D3DPTBLENDCAPS_ADD,"D3DPTBLENDCAPS_ADD");
                checkflag(flag,D3DPTBLENDCAPS_COPY,"D3DPTBLENDCAPS_COPY");
                checkflag(flag,D3DPTBLENDCAPS_DECAL,"D3DPTBLENDCAPS_DECAL");
                checkflag(flag,D3DPTBLENDCAPS_DECALALPHA,"D3DPTBLENDCAPS_DECALALPHA");
                checkflag(flag,D3DPTBLENDCAPS_DECALMASK,"D3DPTBLENDCAPS_DECALMASK");
                checkflag(flag,D3DPTBLENDCAPS_MODULATE,"D3DPTBLENDCAPS_MODULATE");
                checkflag(flag,D3DPTBLENDCAPS_MODULATEALPHA,"D3DPTBLENDCAPS_MODULATEALPHA");
                checkflag(flag,D3DPTBLENDCAPS_MODULATEMASK,"D3DPTBLENDCAPS_MODULATEMASK");       
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcLineCaps.dwTextureBlendCaps "); 

                printf(" puD3dDriverData->hwCaps.dpcLineCaps.dwTextureAddressCaps       : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcLineCaps.dwTextureAddressCaps;
                checkflag(flag,D3DPTADDRESSCAPS_BORDER,"D3DPTADDRESSCAPS_BORDER");
                checkflag(flag,D3DPTADDRESSCAPS_CLAMP,"D3DPTADDRESSCAPS_CLAMP");
                checkflag(flag,D3DPTADDRESSCAPS_INDEPENDENTUV,"D3DPTADDRESSCAPS_INDEPENDENTUV");
                checkflag(flag,D3DPTADDRESSCAPS_MIRROR,"D3DPTADDRESSCAPS_MIRROR");
                checkflag(flag,D3DPTADDRESSCAPS_WRAP,"D3DPTADDRESSCAPS_WRAP");                                
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcLineCaps.dwTextureAddressCaps "); 

                printf(" puD3dDriverData->hwCaps.dpcLineCaps.dwStippleWidth             : 0x%08lx\n",(long)puD3dDriverData->hwCaps.dpcLineCaps.dwStippleWidth);
                printf(" puD3dDriverData->hwCaps.dpcLineCaps.dwStippleHeight            : 0x%08lx\n",(long)puD3dDriverData->hwCaps.dpcLineCaps.dwStippleHeight);
            }
            else
            {
                printf("none puD3dDriverData->hwCaps.dpcLineCaps.dwSize from the driver 0x%08lx\n",puD3dDriverData->hwCaps.dpcLineCaps.dwSize);
            }

            if (puD3dDriverData->hwCaps.dpcTriCaps.dwSize == sizeof(D3DPRIMCAPS))
            {
                printf(" puD3dDriverData->hwCaps.dpcTriCaps.dwSize                      : 0x%08lx\n",(long)puD3dDriverData->hwCaps.dpcTriCaps.dwSize);

                printf(" puD3dDriverData->hwCaps.dpcTriCaps.dwMiscCaps                  : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcTriCaps.dwMiscCaps;
                checkflag(flag,D3DPMISCCAPS_CONFORMANT,"D3DPMISCCAPS_CONFORMANT");
                checkflag(flag,D3DPMISCCAPS_CULLCCW,"D3DPMISCCAPS_CULLCCW");
                checkflag(flag,D3DPMISCCAPS_CULLCW,"D3DPMISCCAPS_CULLCW");
                checkflag(flag,D3DPMISCCAPS_CULLNONE,"D3DPMISCCAPS_CULLNONE");
                checkflag(flag,D3DPMISCCAPS_LINEPATTERNREP,"D3DPMISCCAPS_LINEPATTERNREP");
                checkflag(flag,D3DPMISCCAPS_MASKPLANES,"D3DPMISCCAPS_MASKPLANES");
                checkflag(flag,D3DPMISCCAPS_MASKZ,"D3DPMISCCAPS_MASKZ");
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcTriCaps.dwMiscCaps"); 

                printf(" puD3dDriverData->hwCaps.dpcTriCaps.dwRasterCaps                : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcTriCaps.dwRasterCaps;
                checkflag(flag,D3DPRASTERCAPS_ANISOTROPY,"D3DPRASTERCAPS_ANISOTROPY");
                checkflag(flag,D3DPRASTERCAPS_ANTIALIASEDGES,"D3DPRASTERCAPS_ANTIALIASEDGES");
                checkflag(flag,D3DPRASTERCAPS_ANTIALIASSORTDEPENDENT,"D3DPRASTERCAPS_ANTIALIASSORTDEPENDENT");
                checkflag(flag,D3DPRASTERCAPS_ANTIALIASSORTINDEPENDENT,"D3DPRASTERCAPS_ANTIALIASSORTINDEPENDENT");
                checkflag(flag,D3DPRASTERCAPS_DITHER,"D3DPRASTERCAPS_DITHER");
                checkflag(flag,D3DPRASTERCAPS_FOGRANGE,"D3DPRASTERCAPS_FOGRANGE");
                checkflag(flag,D3DPRASTERCAPS_FOGTABLE,"D3DPRASTERCAPS_FOGTABLE");
                checkflag(flag,D3DPRASTERCAPS_FOGVERTEX,"D3DPRASTERCAPS_FOGVERTEX");
                checkflag(flag,D3DPRASTERCAPS_PAT,"D3DPRASTERCAPS_PAT");
                checkflag(flag,D3DPRASTERCAPS_ROP2,"D3DPRASTERCAPS_ROP2");
                checkflag(flag,D3DPRASTERCAPS_STIPPLE,"D3DPRASTERCAPS_STIPPLE");
                checkflag(flag,D3DPRASTERCAPS_SUBPIXEL,"D3DPRASTERCAPS_SUBPIXEL");
                checkflag(flag,D3DPRASTERCAPS_SUBPIXELX,"D3DPRASTERCAPS_SUBPIXELX");
                checkflag(flag,D3DPRASTERCAPS_TRANSLUCENTSORTINDEPENDENT,"D3DPRASTERCAPS_TRANSLUCENTSORTINDEPENDENT");
                checkflag(flag,D3DPRASTERCAPS_WBUFFER,"D3DPRASTERCAPS_WBUFFER");
                checkflag(flag,D3DPRASTERCAPS_WFOG,"D3DPRASTERCAPS_WFOG");
                checkflag(flag,D3DPRASTERCAPS_XOR,"D3DPRASTERCAPS_XOR");
                checkflag(flag,D3DPRASTERCAPS_ZBIAS,"D3DPRASTERCAPS_ZBIAS");
                checkflag(flag,D3DPRASTERCAPS_ZBUFFERLESSHSR,"D3DPRASTERCAPS_ZBUFFERLESSHSR");
                checkflag(flag,D3DPRASTERCAPS_ZFOG,"D3DPRASTERCAPS_ZFOG");
                checkflag(flag,D3DPRASTERCAPS_ZTEST,"D3DPRASTERCAPS_ZTEST");               
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcTriCaps.dwRasterCaps"); 

                printf(" puD3dDriverData->hwCaps.dpcTriCaps.dwZCmpCaps                  : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcTriCaps.dwZCmpCaps;
                checkflag(flag,D3DPCMPCAPS_ALWAYS,"D3DPCMPCAPS_ALWAYS");
                checkflag(flag,D3DPCMPCAPS_EQUAL,"D3DPCMPCAPS_EQUAL");
                checkflag(flag,D3DPCMPCAPS_GREATER,"D3DPCMPCAPS_GREATER");
                checkflag(flag,D3DPCMPCAPS_GREATEREQUAL,"D3DPCMPCAPS_GREATEREQUAL");
                checkflag(flag,D3DPCMPCAPS_LESS,"D3DPCMPCAPS_LESS");
                checkflag(flag,D3DPCMPCAPS_LESSEQUAL,"D3DPCMPCAPS_LESSEQUAL");
                checkflag(flag,D3DPCMPCAPS_NEVER,"D3DPCMPCAPS_NEVER");
                checkflag(flag,D3DPCMPCAPS_NOTEQUAL,"D3DPCMPCAPS_NOTEQUAL");               
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcTriCaps.dwZCmpCaps "); 
                               
                printf(" puD3dDriverData->hwCaps.dpcTriCaps.dwSrcBlendCaps              : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcTriCaps.dwSrcBlendCaps;
                checkflag(flag,D3DPBLENDCAPS_BOTHINVSRCALPHA,"D3DPBLENDCAPS_BOTHINVSRCALPHA");
                checkflag(flag,D3DPBLENDCAPS_BOTHSRCALPHA,"D3DPBLENDCAPS_BOTHSRCALPHA");
                checkflag(flag,D3DPBLENDCAPS_DESTALPHA,"D3DPBLENDCAPS_DESTALPHA");
                checkflag(flag,D3DPBLENDCAPS_DESTCOLOR,"D3DPBLENDCAPS_DESTCOLOR");
                checkflag(flag,D3DPBLENDCAPS_INVDESTALPHA,"D3DPBLENDCAPS_INVDESTALPHA");
                checkflag(flag,D3DPBLENDCAPS_INVDESTCOLOR,"D3DPBLENDCAPS_INVDESTCOLOR");
                checkflag(flag,D3DPBLENDCAPS_INVSRCALPHA,"D3DPBLENDCAPS_INVSRCALPHA");
                checkflag(flag,D3DPBLENDCAPS_INVSRCCOLOR,"D3DPBLENDCAPS_INVSRCCOLOR");   
                checkflag(flag,D3DPBLENDCAPS_ONE,"D3DPBLENDCAPS_ONE");
                checkflag(flag,D3DPBLENDCAPS_SRCALPHA,"D3DPBLENDCAPS_SRCALPHA");
                checkflag(flag,D3DPBLENDCAPS_SRCALPHASAT,"D3DPBLENDCAPS_SRCALPHASAT");
                checkflag(flag,D3DPBLENDCAPS_SRCCOLOR,"D3DPBLENDCAPS_SRCCOLOR");
                checkflag(flag,D3DPBLENDCAPS_ZERO,"D3DPBLENDCAPS_ZERO");            
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcTriCaps.dwSrcBlendCaps "); 

                printf(" puD3dDriverData->hwCaps.dpcTriCaps.dwDestBlendCaps             : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcTriCaps.dwDestBlendCaps;
                checkflag(flag,D3DPBLENDCAPS_BOTHINVSRCALPHA,"D3DPBLENDCAPS_BOTHINVSRCALPHA");
                checkflag(flag,D3DPBLENDCAPS_BOTHSRCALPHA,"D3DPBLENDCAPS_BOTHSRCALPHA");
                checkflag(flag,D3DPBLENDCAPS_DESTALPHA,"D3DPBLENDCAPS_DESTALPHA");
                checkflag(flag,D3DPBLENDCAPS_DESTCOLOR,"D3DPBLENDCAPS_DESTCOLOR");
                checkflag(flag,D3DPBLENDCAPS_INVDESTALPHA,"D3DPBLENDCAPS_INVDESTALPHA");
                checkflag(flag,D3DPBLENDCAPS_INVDESTCOLOR,"D3DPBLENDCAPS_INVDESTCOLOR");
                checkflag(flag,D3DPBLENDCAPS_INVSRCALPHA,"D3DPBLENDCAPS_INVSRCALPHA");
                checkflag(flag,D3DPBLENDCAPS_INVSRCCOLOR,"D3DPBLENDCAPS_INVSRCCOLOR");   
                checkflag(flag,D3DPBLENDCAPS_ONE,"D3DPBLENDCAPS_ONE");
                checkflag(flag,D3DPBLENDCAPS_SRCALPHA,"D3DPBLENDCAPS_SRCALPHA");
                checkflag(flag,D3DPBLENDCAPS_SRCALPHASAT,"D3DPBLENDCAPS_SRCALPHASAT");
                checkflag(flag,D3DPBLENDCAPS_SRCCOLOR,"D3DPBLENDCAPS_SRCCOLOR");
                checkflag(flag,D3DPBLENDCAPS_ZERO,"D3DPBLENDCAPS_ZERO");            
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcTriCaps.dwDestBlendCaps "); 

                printf(" puD3dDriverData->hwCaps.dpcTriCaps.dwAlphaCmpCaps              : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcTriCaps.dwAlphaCmpCaps;
                checkflag(flag,D3DPCMPCAPS_ALWAYS,"D3DPCMPCAPS_ALWAYS");
                checkflag(flag,D3DPCMPCAPS_EQUAL,"D3DPCMPCAPS_EQUAL");
                checkflag(flag,D3DPCMPCAPS_GREATER,"D3DPCMPCAPS_GREATER");
                checkflag(flag,D3DPCMPCAPS_GREATEREQUAL,"D3DPCMPCAPS_GREATEREQUAL");
                checkflag(flag,D3DPCMPCAPS_LESS,"D3DPCMPCAPS_LESS");
                checkflag(flag,D3DPCMPCAPS_LESSEQUAL,"D3DPCMPCAPS_LESSEQUAL");
                checkflag(flag,D3DPCMPCAPS_NEVER,"D3DPCMPCAPS_NEVER");
                checkflag(flag,D3DPCMPCAPS_NOTEQUAL,"D3DPCMPCAPS_NOTEQUAL");               
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcTriCaps.dwAlphaCmpCaps "); 

                printf(" puD3dDriverData->hwCaps.dpcTriCaps.dwShadeCaps                 : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcTriCaps.dwShadeCaps;
                checkflag(flag,D3DPSHADECAPS_ALPHAFLATBLEND,"D3DPSHADECAPS_ALPHAFLATBLEND");
                checkflag(flag,D3DPSHADECAPS_ALPHAFLATSTIPPLED,"D3DPSHADECAPS_ALPHAFLATSTIPPLED");
                checkflag(flag,D3DPSHADECAPS_ALPHAGOURAUDBLEND,"D3DPSHADECAPS_ALPHAGOURAUDBLEND");
                checkflag(flag,D3DPSHADECAPS_ALPHAGOURAUDSTIPPLED,"D3DPSHADECAPS_ALPHAGOURAUDSTIPPLED");
                checkflag(flag,D3DPSHADECAPS_ALPHAPHONGBLEND,"D3DPSHADECAPS_ALPHAPHONGBLEND");
                checkflag(flag,D3DPSHADECAPS_ALPHAPHONGSTIPPLED,"D3DPSHADECAPS_ALPHAPHONGSTIPPLED");
                checkflag(flag,D3DPSHADECAPS_COLORFLATMONO,"D3DPSHADECAPS_COLORFLATMONO");
                checkflag(flag,D3DPSHADECAPS_COLORFLATRGB,"D3DPSHADECAPS_COLORFLATRGB");       
                checkflag(flag,D3DPSHADECAPS_COLORGOURAUDMONO,"D3DPSHADECAPS_COLORGOURAUDMONO");
                checkflag(flag,D3DPSHADECAPS_COLORGOURAUDRGB,"D3DPSHADECAPS_COLORGOURAUDRGB");
                checkflag(flag,D3DPSHADECAPS_COLORPHONGMONO,"D3DPSHADECAPS_COLORPHONGMONO");
                checkflag(flag,D3DPSHADECAPS_COLORPHONGRGB,"D3DPSHADECAPS_COLORPHONGRGB");
                checkflag(flag,D3DPSHADECAPS_FOGFLAT,"D3DPSHADECAPS_FOGFLAT");
                checkflag(flag,D3DPSHADECAPS_FOGGOURAUD,"D3DPSHADECAPS_FOGGOURAUD");
                checkflag(flag,D3DPSHADECAPS_FOGPHONG,"D3DPSHADECAPS_FOGPHONG");
                checkflag(flag,D3DPSHADECAPS_SPECULARFLATMONO,"D3DPSHADECAPS_SPECULARFLATMONO"); 
                checkflag(flag,D3DPSHADECAPS_SPECULARFLATRGB,"D3DPSHADECAPS_SPECULARFLATRGB"); 
                checkflag(flag,D3DPSHADECAPS_SPECULARGOURAUDMONO,"D3DPSHADECAPS_SPECULARGOURAUDMONO");
                checkflag(flag,D3DPSHADECAPS_SPECULARGOURAUDRGB,"D3DPSHADECAPS_SPECULARGOURAUDRGB");
                checkflag(flag,D3DPSHADECAPS_SPECULARPHONGMONO,"D3DPSHADECAPS_SPECULARPHONGMONO"); 
                checkflag(flag,D3DPSHADECAPS_SPECULARPHONGRGB,"D3DPSHADECAPS_SPECULARPHONGRGB"); 
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcTriCaps.dwShadeCaps "); 

                printf(" puD3dDriverData->hwCaps.dpcTriCaps.dwTextureCaps              : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcTriCaps.dwTextureCaps;
                checkflag(flag,D3DPTEXTURECAPS_ALPHA,"D3DPTEXTURECAPS_ALPHA");
                checkflag(flag,D3DPTEXTURECAPS_ALPHAPALETTE,"D3DPTEXTURECAPS_ALPHAPALETTE");
                checkflag(flag,D3DPTEXTURECAPS_BORDER,"D3DPTEXTURECAPS_BORDER");
                checkflag(flag,D3DPTEXTURECAPS_COLORKEYBLEND,"D3DPTEXTURECAPS_COLORKEYBLEND");
                checkflag(flag,D3DPTEXTURECAPS_CUBEMAP,"D3DPTEXTURECAPS_CUBEMAP");
                checkflag(flag,D3DPTEXTURECAPS_PERSPECTIVE,"D3DPTEXTURECAPS_PERSPECTIVE");
                checkflag(flag,D3DPTEXTURECAPS_POW2,"D3DPTEXTURECAPS_POW2");
                checkflag(flag,D3DPTEXTURECAPS_PROJECTED,"D3DPTEXTURECAPS_PROJECTED");       
                checkflag(flag,D3DPTEXTURECAPS_NONPOW2CONDITIONAL,"D3DPTEXTURECAPS_NONPOW2CONDITIONAL");
                checkflag(flag,D3DPTEXTURECAPS_SQUAREONLY,"D3DPTEXTURECAPS_SQUAREONLY");
                //not in ddk or dxsdk but it is in msdn  checkflag(flag,D3DPTEXTURECAPS_TEXREPEATNOTSCALESBYSIZE,"D3DPTEXTURECAPS_TEXREPEATNOTSCALESBYSIZE");
                //not in ddk or dxsdk but it is in msdn  checkflag(flag,D3DPTEXTURECAPS_TEXTURETRANSFORM,"D3DPTEXTURECAPS_TEXTURETRANSFORM");
                checkflag(flag,D3DPTEXTURECAPS_TRANSPARENCY,"D3DPTEXTURECAPS_TRANSPARENCY");
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcTriCaps.dwTextureCaps "); 

                printf(" puD3dDriverData->hwCaps.dpcTriCaps.dwTextureFilterCaps         : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcTriCaps.dwTextureFilterCaps;
                checkflag(flag,D3DPTFILTERCAPS_LINEAR,"D3DPTFILTERCAPS_LINEAR");
                checkflag(flag,D3DPTFILTERCAPS_LINEARMIPLINEAR,"D3DPTFILTERCAPS_LINEARMIPLINEAR");
                checkflag(flag,D3DPTFILTERCAPS_LINEARMIPNEAREST,"D3DPTFILTERCAPS_LINEARMIPNEAREST");
                checkflag(flag,D3DPTFILTERCAPS_MAGFAFLATCUBIC,"D3DPTFILTERCAPS_MAGFAFLATCUBIC");
                checkflag(flag,D3DPTFILTERCAPS_MAGFANISOTROPIC,"D3DPTFILTERCAPS_MAGFANISOTROPIC");
                checkflag(flag,D3DPTFILTERCAPS_MAGFGAUSSIANCUBIC,"D3DPTFILTERCAPS_MAGFGAUSSIANCUBIC");
                checkflag(flag,D3DPTFILTERCAPS_MAGFLINEAR,"D3DPTFILTERCAPS_MAGFLINEAR");
                checkflag(flag,D3DPTFILTERCAPS_MAGFPOINT,"D3DPTFILTERCAPS_MAGFPOINT");       
                checkflag(flag,D3DPTFILTERCAPS_MINFANISOTROPIC,"D3DPTFILTERCAPS_MINFANISOTROPIC");
                checkflag(flag,D3DPTFILTERCAPS_MINFLINEAR,"D3DPTFILTERCAPS_MINFLINEAR");
                checkflag(flag,D3DPTFILTERCAPS_MINFPOINT,"D3DPTFILTERCAPS_MINFPOINT");
                checkflag(flag,D3DPTFILTERCAPS_MIPFLINEAR,"D3DPTFILTERCAPS_MIPFLINEAR");
                checkflag(flag,D3DPTFILTERCAPS_MIPFPOINT,"D3DPTFILTERCAPS_MIPFPOINT");
                checkflag(flag,D3DPTFILTERCAPS_MIPLINEAR,"D3DPTFILTERCAPS_MIPLINEAR");
                checkflag(flag,D3DPTFILTERCAPS_MIPNEAREST,"D3DPTFILTERCAPS_MIPNEAREST");
                checkflag(flag,D3DPTFILTERCAPS_NEAREST,"D3DPTFILTERCAPS_NEAREST");
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcTriCaps.dwTextureFilterCaps "); 

                printf(" puD3dDriverData->hwCaps.dpcTriCaps.dwTextureBlendCaps          : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcTriCaps.dwTextureBlendCaps;
                checkflag(flag,D3DPTBLENDCAPS_ADD,"D3DPTBLENDCAPS_ADD");
                checkflag(flag,D3DPTBLENDCAPS_COPY,"D3DPTBLENDCAPS_COPY");
                checkflag(flag,D3DPTBLENDCAPS_DECAL,"D3DPTBLENDCAPS_DECAL");
                checkflag(flag,D3DPTBLENDCAPS_DECALALPHA,"D3DPTBLENDCAPS_DECALALPHA");
                checkflag(flag,D3DPTBLENDCAPS_DECALMASK,"D3DPTBLENDCAPS_DECALMASK");
                checkflag(flag,D3DPTBLENDCAPS_MODULATE,"D3DPTBLENDCAPS_MODULATE");
                checkflag(flag,D3DPTBLENDCAPS_MODULATEALPHA,"D3DPTBLENDCAPS_MODULATEALPHA");
                checkflag(flag,D3DPTBLENDCAPS_MODULATEMASK,"D3DPTBLENDCAPS_MODULATEMASK");       
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcTriCaps.dwTextureBlendCaps "); 

                printf(" puD3dDriverData->hwCaps.dpcTriCaps.dwTextureAddressCaps        : ");
                count = 0;
                flag = puD3dDriverData->hwCaps.dpcTriCaps.dwTextureAddressCaps;
                checkflag(flag,D3DPTADDRESSCAPS_BORDER,"D3DPTADDRESSCAPS_BORDER");
                checkflag(flag,D3DPTADDRESSCAPS_CLAMP,"D3DPTADDRESSCAPS_CLAMP");
                checkflag(flag,D3DPTADDRESSCAPS_INDEPENDENTUV,"D3DPTADDRESSCAPS_INDEPENDENTUV");
                checkflag(flag,D3DPTADDRESSCAPS_MIRROR,"D3DPTADDRESSCAPS_MIRROR");
                checkflag(flag,D3DPTADDRESSCAPS_WRAP,"D3DPTADDRESSCAPS_WRAP");                                
                endcheckflag(flag,"puD3dDriverData->hwCaps.dpcTriCaps.dwTextureAddressCaps "); 

                printf(" puD3dDriverData->hwCaps.dpcTriCaps.dwStippleWidth              : 0x%08lx\n",(long)puD3dDriverData->hwCaps.dpcTriCaps.dwStippleWidth);
                printf(" puD3dDriverData->hwCaps.dpcTriCaps.dwStippleHeight             : 0x%08lx\n",(long)puD3dDriverData->hwCaps.dpcTriCaps.dwStippleHeight);
            }
            else
            {
                printf("none puD3dDriverData->hwCaps.dpcTriCaps.dwSize from the driver 0x%08lx\n",puD3dDriverData->hwCaps.dpcTriCaps.dwSize);
            }

            printf(" puD3dDriverData->hwCaps.dwDeviceRenderBitDepth                 : 0x%08lx\n",(long)puD3dDriverData->hwCaps.dwDeviceRenderBitDepth);
            printf(" puD3dDriverData->hwCaps.dwDeviceZBufferBitDepth                : 0x%08lx\n",(long)puD3dDriverData->hwCaps.dwDeviceZBufferBitDepth);
            printf(" puD3dDriverData->hwCaps.dwMaxBufferSize                        : 0x%08lx\n",(long)puD3dDriverData->hwCaps.dwMaxBufferSize);
            printf(" puD3dDriverData->hwCaps.dwMaxVertexCount                       : 0x%08lx\n",(long)puD3dDriverData->hwCaps.dwMaxVertexCount);
        }
        else
        {
            printf("none puD3dDriverData->hwCaps.dwSize from the driver 0x%08lx\n",puD3dDriverData->hwCaps.dwSize);
        }

        printf(" puD3dDriverData->dwNumVertices                                 : 0x%08lx\n",(long)puD3dDriverData->dwNumVertices);
        printf(" puD3dDriverData->dwNumClipVertices                             : 0x%08lx\n",(long)puD3dDriverData->dwNumClipVertices);
        printf(" puD3dDriverData->dwNumTextureFormats                           : 0x%08lx\n",(long)puD3dDriverData->dwNumTextureFormats);
        printf(" puD3dDriverData->lpTextureFormats                              : 0x%08lx\n",(long)puD3dDriverData->lpTextureFormats);
        printf(" puD3dDriverData->lpTextureFormats                              : 0x%08lx\n",(long)puD3dDriverData->lpTextureFormats);
    }
    else
    {
        printf("none puD3dDriverData from the driver 0x%08lx\n",puD3dDriverData->dwSize);
    }
}