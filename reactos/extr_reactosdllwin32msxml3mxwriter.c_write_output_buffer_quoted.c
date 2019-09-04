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
typedef  int /*<<< orphan*/  mxwriter ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  const* quotW ; 
 int /*<<< orphan*/  write_output_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static HRESULT write_output_buffer_quoted(mxwriter *writer, const WCHAR *data, int len)
{
    write_output_buffer(writer, quotW, 1);
    write_output_buffer(writer, data, len);
    write_output_buffer(writer, quotW, 1);

    return S_OK;
}