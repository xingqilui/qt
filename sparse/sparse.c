/*
============================================================================
Name        : Sparse.c
Author      : CHENLEI
Version     : 1.01
Copyright   : Your copyright notice
Description : Hello World in C, Ansi-style
============================================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SUCCESS          1
#define FAILED          0

#define NAMELEN         32
#define LENLEN               4
#define BUFLEN          10240
#define HEXBIT          2
#define CFGCODEMAX          32

#define SCMDCODE		"CMDCODE"
#define SOUTERHEAD		"OUTERHEAD"
#define SINNERHEAD		"INNERHEAD"
#define SINNERBODY		"INNERBODY"

#define SOUTERDIMNUM	"OUTERDIMNUM"
#define SINNERDIMNUM	"INNERDIMNUM"

#define MAINHEADLEN		24

#define ntoh16(n) (((unsigned short)(n) >> 8) | ((unsigned short)(n) << 8))

#define PRINTERROR(_fmt, ...)	printf("ERROR: "_fmt"\r\n", ##__VA_ARGS__);

typedef enum tagConfigHead
{
     INVALIDCFG,
     CMDCODE,
     OUTERHEAD,
     INNERHEAD,
     INNERBODY
}CFGHEAD_E;

typedef enum tagCondition
{
     ISINVALID,
     ISNOTEND,
     ISEND,          /* 一条cmdCode记录结束 */
     ISOVER          /* 所有cmdCode记录结束 */
}CONDITION_E;

typedef struct TlvStruct
{
     int     length;
     char     name[NAMELEN];

}TLV_S ;

typedef struct ConfigInfo
{
     int        cmdCode;
     char       cmdName[NAMELEN];

     TLV_S      stOuterHead[8];
     TLV_S      stInnerHead[8];
     TLV_S      stInnerBody[16];
     int		outerHeadLen;
     int		innerHeadLen;
     int		innerBodyLen;

}CONFIG_S ;


int g_messageLen = 0;

int checkDimNum(int outerDimNum, int innerDimNum, CONFIG_S *pstConfig)
{
	int length = 0;

	length = MAINHEADLEN +
			 pstConfig->outerHeadLen +
			 outerDimNum * (pstConfig->innerHeadLen + innerDimNum * pstConfig->innerBodyLen);

	if (length > g_messageLen)
	{
		PRINTERROR("DimNum is wrong! outerDimNum %d, innerDimNum %d\n", outerDimNum, innerDimNum);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/* 所有实际输出都用此函数，方便以后输出到其他终端(文本文档)，现在输出在stdout */
unsigned char * printBit( char *head, unsigned char *pSrc, int length)
{
     printf("%s : ", head);

     while(length--)
          printf( "%02x", ( unsigned char)*pSrc++);

     printf("\n");
     return pSrc;
}

unsigned char * printMainHead( unsigned char *pSrc, unsigned short *pCmdCode)
{
     /* 考虑内存对齐因素 */
     printBit("\n[MainHead]", NULL, 0);

     pSrc = printBit("DetAddr", pSrc, 4);
     pSrc = printBit("SrcAddr", pSrc, 4);
     pSrc = printBit("CallId", pSrc, 4);
     pSrc = printBit("CmdCode", pSrc, 2);     *pCmdCode = ntoh16(*((unsigned short *)pSrc-1));
     pSrc = printBit("Reply", pSrc, 1);
     pSrc = printBit("ExResult", pSrc, 2);
     pSrc = printBit("Reserved1", pSrc, 1);
     pSrc = printBit("MsgLength", pSrc, 4);
     pSrc = printBit("Reserved2", pSrc, 2);

     return pSrc;
}

unsigned char * printOuterHead( unsigned char *pSrc, TLV_S *pstOuterHead, unsigned short *pOuterDimNum)
{
     printBit("\n[OuterHead]", NULL, 0);

     while(0 != pstOuterHead-> length)
     {
           if (0 == strcmp( SOUTERDIMNUM, pstOuterHead->name))
           {
                *pOuterDimNum = ntoh16(*( unsigned short*)pSrc);
           }

           pSrc = printBit(pstOuterHead->name, pSrc, pstOuterHead->length);

           pstOuterHead++;
     }

     return pSrc;
}

unsigned char * printInnerHead( unsigned char *pSrc, TLV_S *pstInnerHead, unsigned short *pInnerDimNum)
{
     printBit("\n[InnerHead]", NULL, 0);

     while(0 != pstInnerHead-> length)
     {
            if (0 == strcmp( SINNERDIMNUM, pstInnerHead->name))
           {
                *pInnerDimNum = ntoh16(*( unsigned short*)pSrc);
           }

           pSrc = printBit(pstInnerHead->name, pSrc, pstInnerHead->length);

           pstInnerHead++;
     }

     return pSrc;
}

unsigned char * printInnerBody( unsigned char *pSrc, TLV_S *pstInnerBody)
{
     printBit("\n[InnerBody]", NULL, 0);

     while(0 != pstInnerBody->length)
     {
           pSrc = printBit(pstInnerBody->name, pSrc, pstInnerBody->length);

           pstInnerBody++;
     }

     return pSrc;
}

void printResult(unsigned char *pSrc, CONFIG_S *pstConfig)
{
    int i, j;
    unsigned short cmdCode = 0;
    unsigned short outerDimNum = 0;
    unsigned short innerDimNum = 0;

	if (g_messageLen < MAINHEADLEN)
	{
		PRINTERROR("Sport message length %d is too short!", g_messageLen);
		return;
	}

    pSrc = printMainHead(pSrc, &cmdCode);
    while(0 != pstConfig->cmdCode)
    {
    	if (cmdCode == pstConfig->cmdCode)
    		break;

    	pstConfig++;
    }

	if (0 == pstConfig->cmdCode)
	{
		PRINTERROR("Configuration is not support this cmdCode:%x\n", cmdCode);
		return;
	}

	pSrc = printOuterHead(pSrc, &pstConfig->stOuterHead[0], &outerDimNum);
	for (i = 0; i < outerDimNum; i++)
	{
	   pSrc = printInnerHead(pSrc, &pstConfig->stInnerHead[0], &innerDimNum);

	   if (EXIT_FAILURE == checkDimNum(outerDimNum, innerDimNum, pstConfig))
		   return;

	   /* 内循环没有head，则只输出一个body */
	   if (0 == innerDimNum)
			innerDimNum = 1;

	   for (j = 0; j < innerDimNum; j++)
	   {
			pSrc = printInnerBody(pSrc, &pstConfig->stInnerBody[0] );
	   }
	}

	return;
}

/* 将十六进制字符串转换为实际值字符串  010203ab => /0x01 /0x02 /0x03 /0xab */
unsigned char * convertStrtoHex( const char *pSrc, unsigned char *pDst)
{
     unsigned char hex[HEXBIT + 1];
     unsigned long lHex;
     unsigned char *pScan;

     hex[HEXBIT] = '\0';
     pScan = pDst;

     while('\0' != *pSrc)
     {
          hex[0] = *pSrc++;
          hex[1] = *pSrc++;
          lHex = strtol(hex, NULL, 16);

          *pScan++ = ( unsigned char)( unsigned short)lHex;
     }

     return pDst;
}

/* 手动配置 */
void initConfig( CONFIG_S *pstConfig)
{
     /* Main Head */
     pstConfig->cmdCode = 0x1E1D;
     strcpy(pstConfig-> cmdName, "BindPort");

     /* OuterHead */
     strcpy( pstConfig-> stOuterHead[0]. name, "OpType");
     pstConfig->stOuterHead[0].length = 2;
     strcpy( pstConfig-> stOuterHead[1]. name, "OUTERDIMNUM");
     pstConfig->stOuterHead[1].length = 2;

     /* Inner Head */
     strcpy(pstConfig-> stInnerHead[0]. name, "AclID");
     pstConfig->stInnerHead[0].length = 2;
     strcpy(pstConfig-> stInnerHead[1]. name, "RuleID");
     pstConfig->stInnerHead[1].length = 2;
     strcpy(pstConfig-> stInnerHead[2]. name, "INNERDIMNUM");
     pstConfig->stInnerHead[2].length = 2;

     /* Inner Body */
     strcpy(pstConfig-> stInnerBody[0]. name, "ProID");
     pstConfig->stInnerBody[0].length = 2;
     strcpy(pstConfig-> stInnerBody[1]. name, "AssembleFlag");
     pstConfig->stInnerBody[1].length = 1;
     strcpy(pstConfig-> stInnerBody[2]. name, "ValueType");
     pstConfig->stInnerBody[2].length = 1;
     strcpy(pstConfig-> stInnerBody[3]. name, "ProValue");
     pstConfig->stInnerBody[3].length = 8;

}

int cfgHeadType(char *pCfgWord)
{
     int cfgHeadType;

     if (0 == strcmp(pCfgWord, SCMDCODE))
     {
          cfgHeadType = CMDCODE;
     }
     else if (0 == strcmp(pCfgWord, SOUTERHEAD))
     {
          cfgHeadType = OUTERHEAD;
     }
     else if (0 == strcmp(pCfgWord, SINNERHEAD))
     {
          cfgHeadType = INNERHEAD;
     }
     else if (0 == strcmp(pCfgWord, SINNERBODY))
     {
          cfgHeadType = INNERBODY;
     }
     else
     {
          cfgHeadType = INVALIDCFG;
     }

     return cfgHeadType;
}

char* setCmdCode(char *pSrc, CONFIG_S *pConfig)
{
     char *pScan = pSrc;
     char word[NAMELEN] = "\0";
     char hex[LENLEN + 1] = "\0";
     int  i = 0;
     unsigned long code = 0;

     while('<' != *pScan++) {}

     while(':' != *pScan)
          word[i++] = *pScan++;
     word[i] = '\0';
     pScan++;

     i = 0;
     while('>' != *pScan)
        hex[i++] = *pScan++;
     hex[i] = '\0';
     pScan++;

     code = strtol(hex, NULL, 16);

     strcpy(pConfig->cmdName, word);
     pConfig->cmdCode = (int)code;

     return pScan;
}

char* setCfgBody(char *pSrc, CONDITION_E *peFlag, TLV_S *pTlv)
{
          char *pScan = pSrc;
          char word[NAMELEN] = "\0";
          char len[LENLEN + 1] = "\0";
         int  i = 0;

         len[HEXBIT] = '\0';

         while('<' != *pScan++) {}

         while(':' != *pScan)
              word[i++] = *pScan++;
         word[i] = '\0';
         pScan++;

          i = 0;
          while('>' != *pScan)
             len[i++] = *pScan++;
          len[i] = '\0';
          pScan++;

         strcpy(pTlv->name, word);
         pTlv->length = atoi(len);

         while(('[' != *pScan) && ('\0' != *pScan) && ('<' != *pScan))
              pScan++;

         if ('<' == *pScan)
              *peFlag = ISNOTEND;
         else if ('[' == *pScan)
              *peFlag = ISEND;

         return pScan;
}

char* getNextCfgBody(char *pSrc, CFGHEAD_E eCfgHead, int bodyNum, CONDITION_E *peFlag, CONFIG_S *pConfig)
{
     char *pScan = pSrc;

     if ('\0' == *pScan)
    {
          *peFlag = ISOVER;
          return pScan;
    }

     switch(eCfgHead)
     {
          case CMDCODE:
               pScan = setCmdCode(pScan, pConfig);
               *peFlag = ISEND;
               break;

          case OUTERHEAD:
               pScan = setCfgBody(pScan, peFlag, &pConfig->stOuterHead[bodyNum]);
               break;

          case INNERHEAD:
               pScan = setCfgBody(pScan, peFlag, &pConfig->stInnerHead[bodyNum]);
               break;

          case INNERBODY:
               pScan = setCfgBody(pScan, peFlag, &pConfig->stInnerBody[bodyNum]);
               break;

          default:
               break;
     }

     return pScan;
}

char* getNextCfgHead(char *pSrc, CFGHEAD_E *peCfgHead, CONDITION_E *peFlag, CONFIG_S *pConfig)
{
     char *pScan = pSrc;
     char word[NAMELEN] = "\0";
     int i = 0;

     if ('\0' == *pScan)
     {
         *peFlag = ISOVER;
         return pScan;
     }

     while('[' != *pScan++) {}

     while(']' != *pScan)
         word[i++] = *pScan++;
     word[i] = '\0';
     pScan++;

     *peCfgHead = cfgHeadType(word);

     while(('<' != *pScan) && ('[' != *pScan) && ('\0' != *pScan))
          pScan++;

     if ((CMDCODE == *peCfgHead) && (INVALIDCFG !=  *peFlag))
     {
	   *peFlag = ISEND;
	   pScan = pSrc;
     }
     else if ('<' == *pScan)
          *peFlag = ISNOTEND;

     return pScan;
}

void setCfgLen(CONFIG_S *pConfig)
{
	int i;

	i = 0;
	while(0 != pConfig->stOuterHead[i].length)
		pConfig->outerHeadLen +=  pConfig->stOuterHead[i++].length;

	i = 0;
	while(0 != pConfig->stInnerHead[i].length)
			pConfig->innerHeadLen +=  pConfig->stInnerHead[i++].length;

	i = 0;
	while(0 != pConfig->stInnerBody[i].length)
			pConfig->innerBodyLen +=  pConfig->stInnerBody[i++].length;

	return;
}

int checkCfg(CONFIG_S *pConfig)
{
     if ((0 == pConfig->cmdCode) ||
          (0 == pConfig->stOuterHead[0].length) ||
          (0 == pConfig->stInnerBody[0].length))
     {
    	 PRINTERROR("configuration is wrong: CmdCode, OuterHead, InnerBody must be all set!\n");
          return EXIT_FAILURE;
     }

     if ((0 != pConfig->stInnerHead[0].length) &&
          (0 == pConfig->stInnerBody[0].length))
     {
    	 PRINTERROR("configuration is wrong: When InnerHead is set, InnerBody must be set!\n");
          return EXIT_FAILURE;
     }

     return EXIT_SUCCESS;
}

int setConfig(char *cfgBuf, CONFIG_S *pConfig)
{
     char 			*pScan = cfgBuf;
     CFGHEAD_E		eCfgHead =  INVALIDCFG;
     CONDITION_E 	eHeadFlag = ISINVALID;
     CONDITION_E 	eBodyFlag = ISINVALID;
     int 			cmdCodeNum, bodyNum;

     for(cmdCodeNum = 0; cmdCodeNum < CFGCODEMAX; cmdCodeNum++)
     {
    	  eHeadFlag = ISINVALID;

          pScan = getNextCfgHead(pScan, &eCfgHead, &eHeadFlag, pConfig);
          while((eHeadFlag != ISEND) && (eHeadFlag != ISOVER))
          {
               bodyNum = 0;
               eBodyFlag = ISINVALID;

               pScan = getNextCfgBody(pScan, eCfgHead, bodyNum, &eBodyFlag, pConfig);
               while((eBodyFlag != ISEND) && (eBodyFlag != ISOVER))
               {
            	   bodyNum++;
            	   pScan = getNextCfgBody(pScan, eCfgHead, bodyNum, &eBodyFlag, pConfig);
               }

               pScan = getNextCfgHead(pScan, &eCfgHead, &eHeadFlag, pConfig);
          }

          setCfgLen(pConfig);

          if (ISOVER == eHeadFlag)
               break;

          if (EXIT_FAILURE == checkCfg(pConfig))
        	  return EXIT_FAILURE;

          pConfig++;
     }

     return EXIT_SUCCESS;
}

int getConfig(char *cfgBuf)
{
     FILE *fp = NULL;
     char *pScan = cfgBuf;
     char  c = '\0';

     fp = fopen("config.txt", "rb");
     if (NULL == fp)
     {
          PRINTERROR("Open config.txt failed!");
          return EXIT_FAILURE;
     }

     while(EOF != (c = fgetc(fp)))
     {
          *pScan++ = c;
     }

     *pScan = '\0';

     fclose(fp);
     return EXIT_SUCCESS;
}

int main()
{
     int  ret;
     char cmdBuf[BUFLEN] = "\0";
     char cfgBuf[BUFLEN] = "\0";
     unsigned char  pBuf[BUFLEN] = {0};

     CONFIG_S stConfig[CFGCODEMAX];

     memset(&stConfig, 0, sizeof(CONFIG_S) * CFGCODEMAX);

     ret = getConfig(cfgBuf);
     if (EXIT_FAILURE == ret)
     {
    	 PRINTERROR("Get configuration failed!\n");
         return EXIT_FAILURE;
     }

     ret = setConfig(cfgBuf, &stConfig[0]);
     if (EXIT_FAILURE == ret)
     {
    	 PRINTERROR("Set configuration failed!\n");
         return EXIT_FAILURE;
     }

     printf("Sport message interpreter version 1.01\r\n");
     printf("Input Sport message:\n");
     scanf("%s", cmdBuf);
     //printf(" : %s\n", cmdBuf);

     (void) convertStrtoHex(cmdBuf, pBuf);
     //(void) printBit("", pBuf, strlen(cmdBuf)/2);

     /* 获取一下目标报文长度，解析时用来检查长度错误 */
     g_messageLen = strlen(cmdBuf) / 2;

     printResult(pBuf, &stConfig[0]);

     printf("\r\nInput ENTRY:\r\n");
     system("pause");

     return EXIT_SUCCESS;
}
