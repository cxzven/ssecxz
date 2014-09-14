/**************************************************************************************************/
/* Copyright (C) mc2lab.com, SSE@USTC, 2014-2015                                                  */
/*                                                                                                */
/*  FILE NAME             :  menu.c                                                               */
/*  PRINCIPAL AUTHOR      :  Cuixinzhe                                                            */
/*  SUBSYSTEM NAME        :  menu                                                                 */
/*  MODULE NAME           :  menu                                                                 */
/*  LANGUAGE              :  C                                                                    */
/*  TARGET ENVIRONMENT    :  ANY                                                                  */
/*  DATE OF FIRST RELEASE :  2014/09/09                                                           */
/*  DESCRIPTION           :  This is a menu program                                               */
/**************************************************************************************************/

/*
 * Revision log:
 *
 * Created by Cuixinzhe, 2014/09/14
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define CMD_NUM 10
#define DESC_LEN 1024
#define CMD_MAX_LEN 128
 
int Help(); 

/* data struct and its operations*/
typedef struct DataNode
{
    char *cmd;
    char *desc;
    int (*handler)();
    struct DataNode *next;
}tDataNode;

 
tDataNode *FindCmd(tDataNode *head,char *cmd)
{
	
    if(head == NULL||cmd == NULL)
    {
        return NULL;
    }
    tDataNode *p = head;
    while(p != NULL)
        {
 	    if(strcmp(p->cmd,cmd) == 0)
            {
                return p;
 	    }
 	    p = p->next;
 	
 	}
 	return NULL;
}
 
int ShowAllCmd(tDataNode *head)
{
    tDataNode *p = NULL;
    printf("Menu list:\n");
    p = head;
        while(p != NULL)
        {
            printf("%s - %s\n",p->cmd,p->desc);
 	    p = p->next;
        }
}
 

/* menu program */
static tDataNode head[] = 
{
    {"help","This is help cmd!",Help,&head[1]},
    {"version","The program is v1.0",NULL,&head[2]},
    {"del","This is del cmd!",NULL,NULL}
};
 
int main()
{
    tDataNode *p = NULL;
    /*cmd line begins*/
    p = head;	
    while(1)
    {
        char cmd[CMD_MAX_LEN];
        printf("Please input a cmd:\n");
 	scanf("%s",cmd);
 	p = head;
 	tDataNode *p = FindCmd(head,cmd);
 	if(p == NULL)
        {
 	    printf("This is a wrong cmd!\n");
 	    break;
 	}
 	while(p != NULL)
        {
 	    if(p->handler != NULL&&strcmp(p->cmd,cmd) == 0)
            {
 	        p->handler();
 		break;
 	    }
 	    else if(p->handler == NULL&&strcmp(p->cmd,cmd) == 0)
            {
 	        printf("%s - %s\n",p->cmd,p->desc);
 		break;
 	    }
 	    p = p->next;
 	}
    }
 	
}
int Help()
{
    ShowAllCmd(head);
    return 0;
}
