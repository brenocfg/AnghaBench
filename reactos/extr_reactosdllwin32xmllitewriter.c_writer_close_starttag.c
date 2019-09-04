#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ starttagopen; int /*<<< orphan*/  output; } ;
typedef  TYPE_1__ xmlwriter ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  gtW ; 
 int /*<<< orphan*/  write_output_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT writer_close_starttag(xmlwriter *writer)
{
    HRESULT hr;

    if (!writer->starttagopen) return S_OK;
    hr = write_output_buffer(writer->output, gtW, ARRAY_SIZE(gtW));
    writer->starttagopen = FALSE;
    return hr;
}