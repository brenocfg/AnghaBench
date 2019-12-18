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
typedef  int ULONG ;
typedef  int NTSTATUS ;

/* Variables and functions */
 int COMPRESSION_ENGINE_MAXIMUM ; 
 int COMPRESSION_FORMAT_DEFAULT ; 
 int COMPRESSION_FORMAT_LZNT1 ; 
 int COMPRESSION_FORMAT_NONE ; 
 int STATUS_INVALID_PARAMETER ; 
 int STATUS_SUCCESS ; 
 int STATUS_UNSUPPORTED_COMPRESSION ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int pRtlGetCompressionWorkSpaceSize (int,int*,int*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RtlGetCompressionWorkSpaceSize(void)
{
    ULONG compress_workspace, decompress_workspace;
    NTSTATUS status;

    if (!pRtlGetCompressionWorkSpaceSize)
    {
        win_skip("RtlGetCompressionWorkSpaceSize is not available\n");
        return;
    }

    /* test invalid format / engine */
    status = pRtlGetCompressionWorkSpaceSize(COMPRESSION_FORMAT_NONE, &compress_workspace,
                                             &decompress_workspace);
    ok(status == STATUS_INVALID_PARAMETER, "got wrong status 0x%08x\n", status);

    status = pRtlGetCompressionWorkSpaceSize(COMPRESSION_FORMAT_DEFAULT, &compress_workspace,
                                             &decompress_workspace);
    ok(status == STATUS_INVALID_PARAMETER, "got wrong status 0x%08x\n", status);

    status = pRtlGetCompressionWorkSpaceSize(0xFF, &compress_workspace, &decompress_workspace);
    ok(status == STATUS_UNSUPPORTED_COMPRESSION, "got wrong status 0x%08x\n", status);

    /* test LZNT1 with normal and maximum compression */
    compress_workspace = decompress_workspace = 0xdeadbeef;
    status = pRtlGetCompressionWorkSpaceSize(COMPRESSION_FORMAT_LZNT1, &compress_workspace,
                                             &decompress_workspace);
    ok(status == STATUS_SUCCESS, "got wrong status 0x%08x\n", status);
    ok(compress_workspace != 0, "got wrong compress_workspace %u\n", compress_workspace);
    ok(decompress_workspace == 0x1000, "got wrong decompress_workspace %u\n", decompress_workspace);

    compress_workspace = decompress_workspace = 0xdeadbeef;
    status = pRtlGetCompressionWorkSpaceSize(COMPRESSION_FORMAT_LZNT1 | COMPRESSION_ENGINE_MAXIMUM,
                                             &compress_workspace, &decompress_workspace);
    ok(status == STATUS_SUCCESS, "got wrong status 0x%08x\n", status);
    ok(compress_workspace != 0, "got wrong compress_workspace %u\n", compress_workspace);
    ok(decompress_workspace == 0x1000, "got wrong decompress_workspace %u\n", decompress_workspace);
}