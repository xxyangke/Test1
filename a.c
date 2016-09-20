#include <stdio.h>
#include <mysql/mysql.h>
#include <assert.h>
#include <stdlib.h>

typedef struct student
{
	int id;
	char name[20];
	char sex;
	int age;
	char tel[20];
	struct student* next; 
}STU;


int main()
{
	struct student s;
	char sql[1024];
	MYSQL db,*pdb;
	STU *head = NULL;
	STU *p;
	mysql_init(&db);//1
	pdb = mysql_real_connect(&db,"localhost","root","942655","aaa",0,NULL,0);//2
	if(pdb == NULL)
		printf("mysql connect failed\n");
	else
		printf("mysql connect success\n");
	while(1)//3 luru
	{
		p = (STU*)malloc(sizeof(STU));
		assert(p != NULL);	
		printf("请输入学生的学号、姓名、性别、年龄、电话\n");
		scanf("%d %s %c %d %s",&p->id,p->name,&p->sex,&p->age,p->tel);
		if(p->id == 0)
			break;
		p->next = head;
		head = p;
	}
	p = head;
	while(p != NULL)
	{
		sprintf(sql,"insert into students values(%d,\'%s\',\'%c\',%d,\'%s\');",p->id,p->name,p->sex,p->age,p->tel);
		if(mysql_query(&db,sql))//4
		{
			printf("insert failed\n");
			return -1;
		}
		p = p->next;
	}
/*	printf("请输入需要删除的学号\n");
	scanf("%d",&s.id);
	sprintf(sql,"delete from students where id = %d;",s.id);
	if(mysql_query(&db,sql))//4
	{
		printf("delete failed\n");
		return -2;
	}*/
	mysql_close(&db);//5

	return 0;
}




