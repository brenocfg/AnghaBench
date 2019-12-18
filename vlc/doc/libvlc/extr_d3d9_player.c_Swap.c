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
struct render_context {int /*<<< orphan*/  hWnd; int /*<<< orphan*/  d3ddev; int /*<<< orphan*/  rectangleFVFVertexBuf; scalar_t__ renderTexture; int /*<<< orphan*/  backBuffer; } ;
struct CUSTOMVERTEX {int dummy; } ;
typedef  int /*<<< orphan*/  IDirect3DBaseTexture9 ;

/* Variables and functions */
 int /*<<< orphan*/  CUSTOMFVF ; 
 int /*<<< orphan*/  D3DCLEAR_TARGET ; 
 int /*<<< orphan*/  D3DCOLOR_XRGB (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D3DPT_TRIANGLEFAN ; 
 int /*<<< orphan*/  IDirect3DDevice9_BeginScene (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_Clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_DrawPrimitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirect3DDevice9_EndScene (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_Present (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetFVF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetRenderTarget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetStreamSource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Swap(struct render_context *ctx)
{
    /* finished drawing to our swap surface, now render that surface to the backbuffer */
    IDirect3DDevice9_SetRenderTarget(ctx->d3ddev, 0, ctx->backBuffer);

    /* clear the backbuffer to orange */
    IDirect3DDevice9_Clear(ctx->d3ddev, 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 120, 0), 1.0f, 0);

    IDirect3DDevice9_BeginScene(ctx->d3ddev);
    IDirect3DDevice9_SetTexture(ctx->d3ddev, 0, (IDirect3DBaseTexture9*)ctx->renderTexture);

    IDirect3DDevice9_SetStreamSource(ctx->d3ddev, 0, ctx->rectangleFVFVertexBuf, 0, sizeof(struct CUSTOMVERTEX));
    IDirect3DDevice9_SetFVF(ctx->d3ddev, CUSTOMFVF);
    IDirect3DDevice9_DrawPrimitive(ctx->d3ddev, D3DPT_TRIANGLEFAN, 0, 2);
    IDirect3DDevice9_EndScene(ctx->d3ddev);

    IDirect3DDevice9_Present(ctx->d3ddev, NULL, NULL, ctx->hWnd, NULL);
}