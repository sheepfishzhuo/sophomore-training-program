/*我们搞一个小练习（注册功能）
先创建一个数据库admin.db--admin(id text ,passwd text);
我们输入id输入一个passed
如果id注册过（在当前的表中存在）我们就打印已经注册
如果id没有注册，就注册一下（将id和对应的passwd插入）*/
#include <stdio.h>
#include "sqlite3.h"

int main(int argc, char const *argv[])
{
	//打开数据库
	sqlite3*db;
	sqlite3_open("admin.db",&db);
	//创建表
	char sql1[100] = "create table admin (id text,passwd text);";
	char *errmsg = NULL;
	sqlite3_exec(db,sql1,NULL,NULL,&errmsg);
	//让你输入id、passwd
	printf("请输入id：\n");
	char id[20] = "";
	scanf("%s",id);
	printf("请输入passwd：\n");
	char passwd[20] = "";
	scanf("%s",passwd);

	//看注册没有：查询在表中有没有这个id
	char sql2[100] = "";
	sprintf(sql2,"select *from admin where id = \'%s\';",id);
	char ** table = NULL;
	int r = 0 , c = 0;
	errmsg = NULL;
	sqlite3_get_table(db,sql2,&table,&r,&c,&errmsg);
	if(r!=0)//查询到了
	{
		printf("您已经注册过了\n");
		sqlite3_close(db);
		return 0 ;
	}
	char sql3[100] = "";
	sprintf(sql3,"insert into admin values (\'%s\',\'%s\');",id,passwd);
	sqlite3_exec(db,sql3,NULL,NULL,&errmsg);



	
	sqlite3_close(db);
	return 0;
}