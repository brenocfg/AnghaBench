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
 unsigned char* print_byte_range (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_decode_line (unsigned char*,int,int,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void print_db_header(void){
  unsigned char *aData;
  aData = print_byte_range(0, 100, 0);
  printf("Decoded:\n");
  print_decode_line(aData, 16, 2, "Database page size");
  print_decode_line(aData, 18, 1, "File format write version");
  print_decode_line(aData, 19, 1, "File format read version");
  print_decode_line(aData, 20, 1, "Reserved space at end of page");
  print_decode_line(aData, 24, 4, "File change counter");
  print_decode_line(aData, 28, 4, "Size of database in pages");
  print_decode_line(aData, 32, 4, "Page number of first freelist page");
  print_decode_line(aData, 36, 4, "Number of freelist pages");
  print_decode_line(aData, 40, 4, "Schema cookie");
  print_decode_line(aData, 44, 4, "Schema format version");
  print_decode_line(aData, 48, 4, "Default page cache size");
  print_decode_line(aData, 52, 4, "Largest auto-vac root page");
  print_decode_line(aData, 56, 4, "Text encoding");
  print_decode_line(aData, 60, 4, "User version");
  print_decode_line(aData, 64, 4, "Incremental-vacuum mode");
  print_decode_line(aData, 68, 4, "Application ID");
  print_decode_line(aData, 72, 4, "meta[8]");
  print_decode_line(aData, 76, 4, "meta[9]");
  print_decode_line(aData, 80, 4, "meta[10]");
  print_decode_line(aData, 84, 4, "meta[11]");
  print_decode_line(aData, 88, 4, "meta[12]");
  print_decode_line(aData, 92, 4, "Change counter for version number");
  print_decode_line(aData, 96, 4, "SQLite version number");
}