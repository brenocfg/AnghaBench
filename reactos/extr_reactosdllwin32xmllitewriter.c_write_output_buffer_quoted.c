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
typedef  int /*<<< orphan*/  xmlwriteroutput ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  const* quoteW ; 
 int /*<<< orphan*/  write_output_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static HRESULT write_output_buffer_quoted(xmlwriteroutput *output, const WCHAR *data, int len)
{
    write_output_buffer(output, quoteW, ARRAY_SIZE(quoteW));
    write_output_buffer(output, data, len);
    write_output_buffer(output, quoteW, ARRAY_SIZE(quoteW));
    return S_OK;
}