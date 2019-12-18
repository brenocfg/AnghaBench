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
typedef  scalar_t__ video_transfer_func_t ;
typedef  scalar_t__ video_color_space_t ;
typedef  scalar_t__ video_color_primaries_t ;
struct d3d11_local_swapchain {int logged_capabilities; TYPE_2__* colorspace; int /*<<< orphan*/  obj; int /*<<< orphan*/  dxgiswapChain; int /*<<< orphan*/  dxgiswapChain4; } ;
struct TYPE_9__ {scalar_t__ transfer; scalar_t__ full_range; scalar_t__ colorspace; scalar_t__ primaries; } ;
typedef  TYPE_1__ libvlc_video_direct3d_cfg_t ;
struct TYPE_10__ {char* name; scalar_t__ dxgi; scalar_t__ primaries; scalar_t__ color; scalar_t__ transfer; scalar_t__ b_full_range; } ;
typedef  TYPE_2__ dxgi_color_space ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_11__ {scalar_t__ ColorSpace; int /*<<< orphan*/  BitsPerColor; int /*<<< orphan*/  MaxFullFrameLuminance; } ;
typedef  int /*<<< orphan*/  IDXGISwapChain3 ;
typedef  int /*<<< orphan*/  IDXGIOutput6 ;
typedef  int /*<<< orphan*/  IDXGIOutput ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ DXGI_OUTPUT_DESC1 ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDXGIOutput6_GetDesc1 (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  IDXGIOutput6_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDXGIOutput_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDXGIOutput_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDXGISwapChain3_CheckColorSpaceSupport (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDXGISwapChain3_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDXGISwapChain3_SetColorSpace1 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  IDXGISwapChain_GetContainingOutput (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDXGISwapChain_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IDXGIOutput6 ; 
 int /*<<< orphan*/  IID_IDXGISwapChain3 ; 
 int /*<<< orphan*/  IID_IDXGISwapChain4 ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ TRANSFER_FUNC_HLG ; 
 scalar_t__ TRANSFER_FUNC_SMPTE_ST2084 ; 
 int /*<<< orphan*/  canHandleConversion (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* color_spaces ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void SelectSwapchainColorspace(struct d3d11_local_swapchain *display, const libvlc_video_direct3d_cfg_t *cfg)
{
    HRESULT hr;
    int best = 0;
    int score, best_score = 0;
    UINT support;
    IDXGISwapChain3 *dxgiswapChain3 = NULL;
    hr = IDXGISwapChain_QueryInterface( display->dxgiswapChain, &IID_IDXGISwapChain3, (void **)&dxgiswapChain3);
    if (FAILED(hr)) {
        msg_Warn(display->obj, "could not get a IDXGISwapChain3");
        goto done;
    }

    /* pick the best output based on color support and transfer */
    /* TODO support YUV output later */
    best = -1;
    for (int i=0; color_spaces[i].name; ++i)
    {
        hr = IDXGISwapChain3_CheckColorSpaceSupport(dxgiswapChain3, color_spaces[i].dxgi, &support);
        if (SUCCEEDED(hr) && support) {
            if (!display->logged_capabilities)
                msg_Dbg(display->obj, "supports colorspace %s", color_spaces[i].name);
            score = 0;
            if (color_spaces[i].primaries == (video_color_primaries_t) cfg->primaries)
                score++;
            if (color_spaces[i].color == (video_color_space_t) cfg->colorspace)
                score += 2; /* we don't want to translate color spaces */
            if (color_spaces[i].transfer == (video_transfer_func_t) cfg->transfer ||
                /* favor 2084 output for HLG source */
                (color_spaces[i].transfer == TRANSFER_FUNC_SMPTE_ST2084 && cfg->transfer == TRANSFER_FUNC_HLG))
                score++;
            if (color_spaces[i].b_full_range == cfg->full_range)
                score++;
            if (score > best_score || (score && best == -1)) {
                best = i;
                best_score = score;
            }
        }
    }
    display->logged_capabilities = true;

    if (best == -1)
    {
        best = 0;
        msg_Warn(display->obj, "no matching colorspace found force %s", color_spaces[best].name);
    }

    IDXGISwapChain_QueryInterface( display->dxgiswapChain, &IID_IDXGISwapChain4, (void **)&display->dxgiswapChain4);

#ifdef HAVE_DXGI1_6_H
    IDXGIOutput *dxgiOutput = NULL;

    if (SUCCEEDED(IDXGISwapChain_GetContainingOutput( display->dxgiswapChain, &dxgiOutput )))
    {
        IDXGIOutput6 *dxgiOutput6 = NULL;
        if (SUCCEEDED(IDXGIOutput_QueryInterface( dxgiOutput, &IID_IDXGIOutput6, (void **)&dxgiOutput6 )))
        {
            DXGI_OUTPUT_DESC1 desc1;
            if (SUCCEEDED(IDXGIOutput6_GetDesc1( dxgiOutput6, &desc1 )))
            {
                const dxgi_color_space *csp = NULL;
                for (int i=0; color_spaces[i].name; ++i)
                {
                    if (color_spaces[i].dxgi == desc1.ColorSpace)
                    {
                        if (!canHandleConversion(&color_spaces[best], &color_spaces[i]))
                            msg_Warn(display->obj, "Can't handle conversion to screen format %s", color_spaces[i].name);
                        else
                        {
                            best = i;
                            csp = &color_spaces[i];
                        }
                        break;
                    }
                }

                msg_Dbg(display->obj, "Output max luminance: %.1f, colorspace %s, bits per pixel %d", desc1.MaxFullFrameLuminance, csp?csp->name:"unknown", desc1.BitsPerColor);
                //sys->display.luminance_peak = desc1.MaxFullFrameLuminance;
            }
            IDXGIOutput6_Release( dxgiOutput6 );
        }
        IDXGIOutput_Release( dxgiOutput );
    }
#endif

    hr = IDXGISwapChain3_SetColorSpace1(dxgiswapChain3, color_spaces[best].dxgi);
    if (SUCCEEDED(hr))
        msg_Dbg(display->obj, "using colorspace %s", color_spaces[best].name);
    else
        msg_Err(display->obj, "Failed to set colorspace %s. (hr=0x%lX)", color_spaces[best].name, hr);
done:
    display->colorspace = &color_spaces[best];
    if (dxgiswapChain3)
        IDXGISwapChain3_Release(dxgiswapChain3);
}