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
struct shader_test {scalar_t__* bytes; int /*<<< orphan*/  text; } ;
typedef  int /*<<< orphan*/  ID3DBlob ;
typedef  int HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  D3DCOMPILE_SKIP_VALIDATION ; 
 scalar_t__ D3DSIO_END ; 
 scalar_t__ FAILED (int) ; 
 scalar_t__ FALSE ; 
 scalar_t__* ID3D10Blob_GetBufferPointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D10Blob_Release (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  dump_shader (scalar_t__*) ; 
 int /*<<< orphan*/  ok (int,char*,char const*,unsigned int,...) ; 
 int pD3DAssemble (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void exec_tests(const char *name, struct shader_test tests[], unsigned int count) {
    HRESULT hr;
    DWORD *res;
    unsigned int i, j;
    BOOL diff;
    ID3DBlob *shader, *messages;

    for(i = 0; i < count; i++) {
        /* D3DAssemble sets messages to 0 if there aren't error messages */
        messages = NULL;
        hr = pD3DAssemble(tests[i].text, strlen(tests[i].text), NULL,
                          NULL, NULL, D3DCOMPILE_SKIP_VALIDATION,
                          &shader, &messages);
        ok(hr == S_OK, "Test %s, shader %d: D3DAssemble failed with error 0x%x - %d\n", name, i, hr, hr & 0x0000FFFF);
        if(messages) {
            trace("D3DAssemble messages:\n%s", (char *)ID3D10Blob_GetBufferPointer(messages));
            ID3D10Blob_Release(messages);
        }
        if(FAILED(hr)) continue;

        j = 0;
        diff = FALSE;
        res = ID3D10Blob_GetBufferPointer(shader);
        while(res[j] != D3DSIO_END && tests[i].bytes[j] != D3DSIO_END) {
            if(res[j] != tests[i].bytes[j]) diff = TRUE;
            j++;
        };
        /* Both must have an end token */
        if(res[j] != tests[i].bytes[j]) diff = TRUE;

        if(diff) {
            ok(FALSE, "Test %s, shader %d: Generated code differs\n", name, i);
            dump_shader(res);
        }
        ID3D10Blob_Release(shader);
    }
}