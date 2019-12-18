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
typedef  int OutputMode ;
typedef  int /*<<< orphan*/  JsonFormatFlags ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_FORMAT_NEWLINE ; 
 int /*<<< orphan*/  JSON_FORMAT_PRETTY ; 
 int /*<<< orphan*/  JSON_FORMAT_SEQ ; 
 int /*<<< orphan*/  JSON_FORMAT_SSE ; 
#define  OUTPUT_JSON_PRETTY 130 
#define  OUTPUT_JSON_SEQ 129 
#define  OUTPUT_JSON_SSE 128 

JsonFormatFlags output_mode_to_json_format_flags(OutputMode m) {

        switch (m) {

        case OUTPUT_JSON_SSE:
                return JSON_FORMAT_SSE;

        case OUTPUT_JSON_SEQ:
                return JSON_FORMAT_SEQ;

        case OUTPUT_JSON_PRETTY:
                return JSON_FORMAT_PRETTY;

        default:
                return JSON_FORMAT_NEWLINE;
        }
}