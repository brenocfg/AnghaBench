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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdout ; 

void help_display()
{
    /*             "1234567890123456789012345678901234567890123456789012345678901234567890123456789" */
    fprintf(stdout, "                Help for the 'mj2_to_metadata' Program\n");
    fprintf(stdout, "                ======================================\n");
    fprintf(stdout, "The -h option displays this information on screen.\n\n");

    fprintf(stdout,
            "mj2_to_metadata generates an XML file from a Motion JPEG 2000 file.\n");
    fprintf(stdout,
            "The generated XML shows the structural, but not (yet) curatorial,\n");
    fprintf(stdout,
            "metadata from the movie header and from the JPEG 2000 image and tile\n");
    fprintf(stdout,
            "headers of a sample frame.  Excluded: low-level packed-bits image data.\n\n");

    fprintf(stdout, "By Default\n");
    fprintf(stdout, "----------\n");
    fprintf(stdout,
            "The metadata includes the jp2 image and tile headers of the first frame.\n");
    fprintf(stdout, "\n");
    fprintf(stdout,
            "Metadata values are shown in 'raw' form (e.g., hexadecimal) as stored in the\n");
    fprintf(stdout,
            "file, and, if apt, in a 'derived' form that is more quickly grasped.\n");
    fprintf(stdout, "\n");
    fprintf(stdout,
            "Notes explaining the XML are embedded as terse comments.  These include\n");
    fprintf(stdout, "   meaning of non-obvious tag abbreviations;\n");
    fprintf(stdout, "   range and precision of valid values;\n");
    fprintf(stdout, "   interpretations of values, such as enumerations; and\n");
    fprintf(stdout, "   current implementation limitations.\n");
    fprintf(stdout, "\n");
    fprintf(stdout,
            "The sample-size and chunk-offset tables, each with 1 row per frame, are not reported.\n");
    fprintf(stdout, "\n");
    fprintf(stdout,
            "The file is self-contained and no verification (e.g., against a DTD) is requested.\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Required Parameters (except with -h)\n");
    fprintf(stdout, "------------------------------------\n");
    fprintf(stdout,
            "[Caution: file strings that contain spaces should be wrapped with quotes.]\n");
    fprintf(stdout,
            "-i input.mj2  : where 'input' is any source file name or path.\n");
    fprintf(stdout,
            "                MJ2 files created with 'frames_to_mj2' are supported so far.\n");
    fprintf(stdout,
            "                These are silent, single-track, 'MJ2 Simple Profile' videos.\n");
    fprintf(stdout,
            "-o output.xml : where 'output' is any destination file name or path.\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Optional Parameters\n");
    fprintf(stdout, "-------------------\n");
    fprintf(stdout, "-h            : Display this help information.\n");
    fprintf(stdout, "-n            : Suppress all mj2_to_metadata notes.\n");
    fprintf(stdout,
            "-t            : Include sample-size and chunk-offset tables.\n");
    fprintf(stdout,
            "-f n          : where n > 0.  Include jp2 header info for frame n [default=1].\n");
    fprintf(stdout, "-f 0          : No jp2 header info.\n");
    fprintf(stdout,
            "-r            : Suppress all 'raw' data for which a 'derived' form exists.\n");
    fprintf(stdout, "-d            : Suppress all 'derived' data.\n");
    fprintf(stdout,
            "                (If both -r and -d given, -r will be ignored.)\n");
    fprintf(stdout,
            "-v string     : Verify against the DTD file located by the string.\n");
    fprintf(stdout,
            "                Prepend quoted 'string' with either SYSTEM or PUBLIC keyword.\n");
    fprintf(stdout,
            "                Thus, for the distributed DTD placed in the same directory as\n");
    fprintf(stdout,
            "                the output file: -v \"SYSTEM mj2_to_metadata.dtd\"\n");
    fprintf(stdout,
            "                \"PUBLIC\" is used with an access protocol (e.g., http:) + URL.\n");
    /* More to come */
    fprintf(stdout, "\n");
    /*             "1234567890123456789012345678901234567890123456789012345678901234567890123456789" */
}