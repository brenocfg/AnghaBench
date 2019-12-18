#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_7__ {void* output_message; void* error_exit; } ;
struct TYPE_8__ {TYPE_2__ pub; } ;
struct TYPE_6__ {int input_components; int num_components; int /*<<< orphan*/  err; } ;

/* Variables and functions */
 TYPE_1__ Compressor ; 
 TYPE_4__ ErrorHandler ; 
 int /*<<< orphan*/  FatalError (char*,char const*) ; 
 int /*<<< orphan*/ * OutFile ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  jpeg_create_compress (TYPE_1__*) ; 
 int /*<<< orphan*/  jpeg_std_error (TYPE_2__*) ; 
 int /*<<< orphan*/  jpeg_stdio_dest (TYPE_1__*,int /*<<< orphan*/ *) ; 
 void* my_error_exit ; 

__attribute__((used)) static
cmsBool OpenOutput(const char* FileName)
{

    OutFile = fopen(FileName, "wb");
    if (OutFile == NULL) {
        FatalError("Cannot create '%s'", FileName);

    }

    Compressor.err                   = jpeg_std_error(&ErrorHandler.pub);
    ErrorHandler.pub.error_exit      = my_error_exit;
    ErrorHandler.pub.output_message  = my_error_exit;

    Compressor.input_components = Compressor.num_components = 4;

    jpeg_create_compress(&Compressor);
    jpeg_stdio_dest(&Compressor, OutFile);
    return TRUE;
}