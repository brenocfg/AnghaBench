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
typedef  scalar_t__ cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  Compressor ; 
 int /*<<< orphan*/  Decompressor ; 
 int /*<<< orphan*/  InFile ; 
 int /*<<< orphan*/  OutFile ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_destroy_compress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jpeg_destroy_decompress (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsBool Done(void)
{
    jpeg_destroy_decompress(&Decompressor);
    jpeg_destroy_compress(&Compressor);
    return fclose(InFile) + fclose(OutFile);

}