#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int marker; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ jpeg ;

/* Variables and functions */
 int MARKER_none ; 
 int SCAN_type ; 
 int /*<<< orphan*/  SOF (int) ; 
 int /*<<< orphan*/  SOI (int) ; 
 scalar_t__ at_eof (int /*<<< orphan*/ ) ; 
 int e (char*,char*) ; 
 int get_marker (TYPE_1__*) ; 
 int /*<<< orphan*/  process_frame_header (TYPE_1__*,int) ; 
 int /*<<< orphan*/  process_marker (TYPE_1__*,int) ; 

__attribute__((used)) static int decode_jpeg_header(jpeg *z, int scan)
{
   int m;
   z->marker = MARKER_none; // initialize cached marker to empty
   m = get_marker(z);
   if (!SOI(m)) return e("no SOI","Corrupt JPEG");
   if (scan == SCAN_type) return 1;
   m = get_marker(z);
   while (!SOF(m)) {
      if (!process_marker(z,m)) return 0;
      m = get_marker(z);
      while (m == MARKER_none) {
         // some files have extra padding after their blocks, so ok, we'll scan
         if (at_eof(z->s)) return e("no SOF", "Corrupt JPEG");
         m = get_marker(z);
      }
   }
   if (!process_frame_header(z, scan)) return 0;
   return 1;
}