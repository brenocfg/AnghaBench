#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_9__ {void* output_message; void* error_exit; } ;
struct TYPE_10__ {TYPE_2__ pub; } ;
struct TYPE_8__ {int /*<<< orphan*/  err; } ;

/* Variables and functions */
 TYPE_1__ Decompressor ; 
 TYPE_6__ ErrorHandler ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FatalError (char*,char const*) ; 
 int /*<<< orphan*/ * InFile ; 
 scalar_t__ JPEG_APP0 ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_create_decompress (TYPE_1__*) ; 
 int /*<<< orphan*/  jpeg_read_header (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_save_markers (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  jpeg_std_error (TYPE_2__*) ; 
 int /*<<< orphan*/  jpeg_stdio_src (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lIsITUFax ; 
 void* my_error_exit ; 

__attribute__((used)) static
cmsBool OpenInput(const char* FileName)
{
    int m;

    lIsITUFax = FALSE;
    InFile  = fopen(FileName, "rb");
    if (InFile == NULL) {
        FatalError("Cannot open '%s'", FileName);
    }

    // Now we can initialize the JPEG decompression object.
    Decompressor.err                 = jpeg_std_error(&ErrorHandler.pub);
    ErrorHandler.pub.error_exit      = my_error_exit;
    ErrorHandler.pub.output_message  = my_error_exit;

    jpeg_create_decompress(&Decompressor);
    jpeg_stdio_src(&Decompressor, InFile);

    for (m = 0; m < 16; m++)
        jpeg_save_markers(&Decompressor, JPEG_APP0 + m, 0xFFFF);

    // setup_read_icc_profile(&Decompressor);

    fseek(InFile, 0, SEEK_SET);
    jpeg_read_header(&Decompressor, TRUE);

    return TRUE;
}