#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  date; int /*<<< orphan*/  time; } ;
struct TYPE_5__ {TYPE_1__ dir_ent; } ;
typedef  TYPE_2__ DOS_FILE ;

/* Variables and functions */
 int /*<<< orphan*/  date_dos2unix (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 

__attribute__((used)) static char *file_stat(DOS_FILE * file)
{
    static char temp[100];
    struct tm *tm;
    char tmp[100];
    time_t date;

    date =
	date_dos2unix(le16toh(file->dir_ent.time), le16toh(file->dir_ent.date));
    tm = localtime(&date);
    strftime(tmp, 99, "%H:%M:%S %b %d %Y", tm);
    sprintf(temp, "  Size %u bytes, date %s", le32toh(file->dir_ent.size), tmp);
    return temp;
}