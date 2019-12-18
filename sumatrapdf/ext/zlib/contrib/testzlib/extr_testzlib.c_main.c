#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {unsigned char* next_in; unsigned char* next_out; long total_in; long avail_in; int avail_out; long total_out; } ;
typedef  TYPE_1__ z_stream ;
struct TYPE_16__ {int /*<<< orphan*/  QuadPart; } ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  double DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BeginCountPerfCounter (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BeginCountRdtsc (TYPE_2__*) ; 
 double GetMsecSincePerfCounter (TYPE_2__,int /*<<< orphan*/ ) ; 
 TYPE_2__ GetResRdtsc (TYPE_2__,int /*<<< orphan*/ ) ; 
 double GetTickCount () ; 
 scalar_t__ ReadFileMemory (char*,long*,unsigned char**) ; 
 int /*<<< orphan*/  TRUE ; 
 int Z_DEFAULT_COMPRESSION ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int /*<<< orphan*/  Z_SYNC_FLUSH ; 
 int atol (char*) ; 
 int deflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deflateEnd (TYPE_1__*) ; 
 int /*<<< orphan*/  deflateInit (TYPE_1__*,int) ; 
 int inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inflateEnd (TYPE_1__*) ; 
 int /*<<< orphan*/  inflateInit (TYPE_1__*) ; 
 scalar_t__ malloc (long) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,long) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* min (long,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ realloc (unsigned char*,long) ; 

int main(int argc, char *argv[])
{
    int BlockSizeCompress=0x8000;
    int BlockSizeUncompress=0x8000;
    int cprLevel=Z_DEFAULT_COMPRESSION ;
    long lFileSize;
    unsigned char* FilePtr;
    long lBufferSizeCpr;
    long lBufferSizeUncpr;
    long lCompressedSize=0;
    unsigned char* CprPtr;
    unsigned char* UncprPtr;
    long lSizeCpr,lSizeUncpr;
    DWORD dwGetTick,dwMsecQP;
    LARGE_INTEGER li_qp,li_rdtsc,dwResRdtsc;

    if (argc<=1)
    {
        printf("run TestZlib <File> [BlockSizeCompress] [BlockSizeUncompress] [compres. level]\n");
        return 0;
    }

    if (ReadFileMemory(argv[1],&lFileSize,&FilePtr)==0)
    {
        printf("error reading %s\n",argv[1]);
        return 1;
    }
    else printf("file %s read, %u bytes\n",argv[1],lFileSize);

    if (argc>=3)
        BlockSizeCompress=atol(argv[2]);

    if (argc>=4)
        BlockSizeUncompress=atol(argv[3]);

    if (argc>=5)
        cprLevel=(int)atol(argv[4]);

    lBufferSizeCpr = lFileSize + (lFileSize/0x10) + 0x200;
    lBufferSizeUncpr = lBufferSizeCpr;

    CprPtr=(unsigned char*)malloc(lBufferSizeCpr + BlockSizeCompress);

    BeginCountPerfCounter(&li_qp,TRUE);
    dwGetTick=GetTickCount();
    BeginCountRdtsc(&li_rdtsc);
    {
        z_stream zcpr;
        int ret=Z_OK;
        long lOrigToDo = lFileSize;
        long lOrigDone = 0;
        int step=0;
        memset(&zcpr,0,sizeof(z_stream));
        deflateInit(&zcpr,cprLevel);

        zcpr.next_in = FilePtr;
        zcpr.next_out = CprPtr;


        do
        {
            long all_read_before = zcpr.total_in;
            zcpr.avail_in = min(lOrigToDo,BlockSizeCompress);
            zcpr.avail_out = BlockSizeCompress;
            ret=deflate(&zcpr,(zcpr.avail_in==lOrigToDo) ? Z_FINISH : Z_SYNC_FLUSH);
            lOrigDone += (zcpr.total_in-all_read_before);
            lOrigToDo -= (zcpr.total_in-all_read_before);
            step++;
        } while (ret==Z_OK);

        lSizeCpr=zcpr.total_out;
        deflateEnd(&zcpr);
        dwGetTick=GetTickCount()-dwGetTick;
        dwMsecQP=GetMsecSincePerfCounter(li_qp,TRUE);
        dwResRdtsc=GetResRdtsc(li_rdtsc,TRUE);
        printf("total compress size = %u, in %u step\n",lSizeCpr,step);
        printf("time = %u msec = %f sec\n",dwGetTick,dwGetTick/(double)1000.);
        printf("defcpr time QP = %u msec = %f sec\n",dwMsecQP,dwMsecQP/(double)1000.);
        printf("defcpr result rdtsc = %I64x\n\n",dwResRdtsc.QuadPart);
    }

    CprPtr=(unsigned char*)realloc(CprPtr,lSizeCpr);
    UncprPtr=(unsigned char*)malloc(lBufferSizeUncpr + BlockSizeUncompress);

    BeginCountPerfCounter(&li_qp,TRUE);
    dwGetTick=GetTickCount();
    BeginCountRdtsc(&li_rdtsc);
    {
        z_stream zcpr;
        int ret=Z_OK;
        long lOrigToDo = lSizeCpr;
        long lOrigDone = 0;
        int step=0;
        memset(&zcpr,0,sizeof(z_stream));
        inflateInit(&zcpr);

        zcpr.next_in = CprPtr;
        zcpr.next_out = UncprPtr;


        do
        {
            long all_read_before = zcpr.total_in;
            zcpr.avail_in = min(lOrigToDo,BlockSizeUncompress);
            zcpr.avail_out = BlockSizeUncompress;
            ret=inflate(&zcpr,Z_SYNC_FLUSH);
            lOrigDone += (zcpr.total_in-all_read_before);
            lOrigToDo -= (zcpr.total_in-all_read_before);
            step++;
        } while (ret==Z_OK);

        lSizeUncpr=zcpr.total_out;
        inflateEnd(&zcpr);
        dwGetTick=GetTickCount()-dwGetTick;
        dwMsecQP=GetMsecSincePerfCounter(li_qp,TRUE);
        dwResRdtsc=GetResRdtsc(li_rdtsc,TRUE);
        printf("total uncompress size = %u, in %u step\n",lSizeUncpr,step);
        printf("time = %u msec = %f sec\n",dwGetTick,dwGetTick/(double)1000.);
        printf("uncpr  time QP = %u msec = %f sec\n",dwMsecQP,dwMsecQP/(double)1000.);
        printf("uncpr  result rdtsc = %I64x\n\n",dwResRdtsc.QuadPart);
    }

    if (lSizeUncpr==lFileSize)
    {
        if (memcmp(FilePtr,UncprPtr,lFileSize)==0)
            printf("compare ok\n");

    }

    return 0;
}