#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ marker; int /*<<< orphan*/  s; scalar_t__ restart_interval; } ;
typedef  TYPE_1__ jpeg ;

/* Variables and functions */
 int /*<<< orphan*/  EOI (int) ; 
 scalar_t__ MARKER_none ; 
 int /*<<< orphan*/  SCAN_load ; 
 scalar_t__ SOS (int) ; 
 int /*<<< orphan*/  at_eof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_jpeg_header (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int get8 (int /*<<< orphan*/ ) ; 
 scalar_t__ get8u (int /*<<< orphan*/ ) ; 
 int get_marker (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_entropy_coded_data (TYPE_1__*) ; 
 int /*<<< orphan*/  process_marker (TYPE_1__*,int) ; 
 int /*<<< orphan*/  process_scan_header (TYPE_1__*) ; 

__attribute__((used)) static int decode_jpeg_image(jpeg *j)
{
   int m;
   j->restart_interval = 0;
   if (!decode_jpeg_header(j, SCAN_load)) return 0;
   m = get_marker(j);
   while (!EOI(m)) {
      if (SOS(m)) {
         if (!process_scan_header(j)) return 0;
         if (!parse_entropy_coded_data(j)) return 0;
         if (j->marker == MARKER_none ) {
            // handle 0s at the end of image data from IP Kamera 9060
            while (!at_eof(j->s)) {
               int x = get8(j->s);
               if (x == 255) {
                  j->marker = get8u(j->s);
                  break;
               } else if (x != 0) {
                  return 0;
               }
            }
            // if we reach eof without hitting a marker, get_marker() below will fail and we'll eventually return 0
         }
      } else {
         if (!process_marker(j, m)) return 0;
      }
      m = get_marker(j);
   }
   return 1;
}