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
typedef  int /*<<< orphan*/  (* class_constructor ) (int /*<<< orphan*/ *,void**) ;
typedef  int /*<<< orphan*/  IWICPersistStream ;
typedef  int /*<<< orphan*/  IWICMetadataReader ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IWICMetadataReader ; 
 int /*<<< orphan*/  IID_IWICPersistStream ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICMetadataReader_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IWICMetadataReader_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICPersistStream_LoadEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWICPersistStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WICPersistOptionDefault ; 
 int /*<<< orphan*/ * create_stream (void const*,int) ; 

__attribute__((used)) static HRESULT create_metadata_reader(const void *data, int data_size,
                                      class_constructor constructor,
                                      IWICMetadataReader **reader)
{
    HRESULT hr;
    IWICMetadataReader *metadata_reader;
    IWICPersistStream *persist;
    IStream *stream;

    /* FIXME: Use IWICComponentFactory_CreateMetadataReader once it's implemented */

    hr = constructor(&IID_IWICMetadataReader, (void**)&metadata_reader);
    if (FAILED(hr)) return hr;

    hr = IWICMetadataReader_QueryInterface(metadata_reader, &IID_IWICPersistStream, (void **)&persist);
    if (FAILED(hr))
    {
        IWICMetadataReader_Release(metadata_reader);
        return hr;
    }

    stream = create_stream(data, data_size);
    IWICPersistStream_LoadEx(persist, stream, NULL, WICPersistOptionDefault);
    IStream_Release(stream);

    IWICPersistStream_Release(persist);

    *reader = metadata_reader;
    return S_OK;
}