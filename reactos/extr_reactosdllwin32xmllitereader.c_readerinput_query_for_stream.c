#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  input; } ;
typedef  TYPE_1__ xmlreaderinput ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IID_ISequentialStream ; 
 int /*<<< orphan*/  IID_IStream ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  readerinput_release_stream (TYPE_1__*) ; 

__attribute__((used)) static inline HRESULT readerinput_query_for_stream(xmlreaderinput *readerinput)
{
    HRESULT hr;

    readerinput_release_stream(readerinput);
    hr = IUnknown_QueryInterface(readerinput->input, &IID_IStream, (void**)&readerinput->stream);
    if (hr != S_OK)
        hr = IUnknown_QueryInterface(readerinput->input, &IID_ISequentialStream, (void**)&readerinput->stream);

    return hr;
}