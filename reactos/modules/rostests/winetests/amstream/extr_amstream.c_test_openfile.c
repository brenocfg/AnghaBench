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
typedef  int /*<<< orphan*/  IGraphBuilder ;
typedef  int /*<<< orphan*/  IAMMultiMediaStream ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IAMMultiMediaStream_GetFilterGraph (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IAMMultiMediaStream_OpenFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAMMultiMediaStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IGraphBuilder_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * create_ammultimediastream () ; 
 int /*<<< orphan*/  filenameW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_openfile(void)
{
    IAMMultiMediaStream *pams;
    HRESULT hr;
    IGraphBuilder* pgraph;

    if (!(pams = create_ammultimediastream()))
        return;

    hr = IAMMultiMediaStream_GetFilterGraph(pams, &pgraph);
    ok(hr==S_OK, "IAMMultiMediaStream_GetFilterGraph returned: %x\n", hr);
    ok(pgraph==NULL, "Filtergraph should not be created yet\n");

    if (pgraph)
        IGraphBuilder_Release(pgraph);

    hr = IAMMultiMediaStream_OpenFile(pams, filenameW, 0);
    ok(hr==S_OK, "IAMMultiMediaStream_OpenFile returned: %x\n", hr);

    hr = IAMMultiMediaStream_GetFilterGraph(pams, &pgraph);
    ok(hr==S_OK, "IAMMultiMediaStream_GetFilterGraph returned: %x\n", hr);
    ok(pgraph!=NULL, "Filtergraph should be created\n");

    if (pgraph)
        IGraphBuilder_Release(pgraph);

    IAMMultiMediaStream_Release(pams);
}