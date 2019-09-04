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
typedef  int off_t ;

/* Variables and functions */
 int O_RDONLY ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int _O_BINARY ; 
 int /*<<< orphan*/  _close (int) ; 
 int _lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _open (char*,int) ; 
 long _read (int,void*,int) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int process_pe (char*,int,void*,int) ; 

int process_file(char* filename)
{
	int file;
	void* p;
	off_t len;
	int iRetVal=0;

    //printf("LOADER: enter process_file()\n");
    file = _open(filename,O_RDONLY|_O_BINARY);
    if(file>0)
    {
        //printf("LOADER: opened %s as FD %x\n",filename,file);

        len = _lseek(file,0,SEEK_END);
        printf("LOADER: file %s is %u bytes\n",filename,(int)len);

        _lseek(file,0,SEEK_SET);

        p = malloc(len+16);
        if(p)
        {
			long count;
            //printf("LOADER: malloc'd @ %x\n",p);
            memset(p,0,len+16);
            if(len == (count = _read(file,p,len)))
            {
                //printf("LOADER: trying ELF format\n");
                iRetVal = process_pe(filename,file,p,len);
            }
        }
        _close(file);
    }
    else
    {
        printf("LOADER: file %s could not be opened\n",filename);
		iRetVal = 1;
    }

    //printf("LOADER: leave process_file()\n");
    return iRetVal;
}