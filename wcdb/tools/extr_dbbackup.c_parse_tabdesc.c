#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* table; char* condition; } ;
typedef  TYPE_1__ mm_backup_tabdesc ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MMBAK_LOG_ERROR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int g_num_tabdesc ; 
 TYPE_1__* g_tabdesc ; 
 char* g_tabdesc_buffer ; 
 scalar_t__ malloc (long) ; 
 int /*<<< orphan*/  print_log (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void parse_tabdesc(const char *path)
{
	FILE *fp = fopen(path, "r");
	if (!fp) goto bail;
	
	// get file length
	fseek(fp, 0, SEEK_END);
	long file_len = ftell(fp) + 1;
	fseek(fp, 0, SEEK_SET);
	
	// read whole file into buffer
	g_tabdesc_buffer = (char *) malloc(file_len);
	if (!g_tabdesc_buffer) goto bail;
	char *p = g_tabdesc_buffer;
	int count = 0;
	while (!feof(fp) && !ferror(fp) && p - g_tabdesc_buffer < file_len)
	{
		char *ret = fgets(p, g_tabdesc_buffer + file_len - p, fp);
		if (ret)
		{
			count++;
			char c;
			while (c = *p++)
			{
				if (c == '\n')
				{
					*(p - 1) = '\0';
					break;
				}
			}
		}
	}
	fclose(fp);
	fp = NULL;
	
	// translate strings to tabdesc
	g_tabdesc = (mm_backup_tabdesc *) calloc(count, sizeof(mm_backup_tabdesc));
	if (!g_tabdesc) goto bail;
	
	p = g_tabdesc_buffer;
	
	int i;
	for (i = 0; i < count; i++)
	{
		g_tabdesc[i].table = p;
		char c;
		while (c = *p++)
		{
			if (c == '|')
			{
				*(p - 1) = '\0';
				g_tabdesc[i].condition = p;
			}
		}
	}
	g_num_tabdesc = count;
	return;
		
bail:
	print_log(MMBAK_LOG_ERROR, "Cannot parse table descriptor.");
	if (fp) fclose(fp);
	exit(1);
}