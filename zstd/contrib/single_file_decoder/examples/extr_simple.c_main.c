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

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 size_t ZSTD_decompress (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dstDxt1 ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  rawDxt1 ; 
 int /*<<< orphan*/  srcZstd ; 

int main() {
	size_t size = ZSTD_decompress(dstDxt1, sizeof dstDxt1, srcZstd, sizeof srcZstd);
	int compare = memcmp(rawDxt1, dstDxt1, sizeof dstDxt1);
	printf("Decompressed size: %s\n", (size == sizeof dstDxt1) ? "PASSED" : "FAILED");
	printf("Byte comparison: %s\n", (compare == 0) ? "PASSED" : "FAILED");
	if (size == sizeof dstDxt1 && compare == 0) {
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}