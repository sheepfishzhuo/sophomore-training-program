//打印的头文件
#include <stdio.h>
//使用了数据库，sqlite的头文件
#include "sqlite3.h"

int main(int argc, char const *argv[])
{
	//打开数据库准备一个句柄（打开数据库放入句柄，后面对句柄操作就是对数据库操作）
	//因此这个句柄相当于我们学过的文件描述符
	//--------------打开数据库---------------
	sqlite3 *db;
	sqlite3_open("yyz.db",&db);//在这一行之后db中就有东西了
	//下面对db操作就是对数据库haha.db文件操作
	
	//-----------功能1-------新建表--------
	printf("请输入你想创建的表的名称：");
	char table_name[30] = "";//字符数组用于存放字符串，初始化使用空的字符串
	scanf("%s",table_name);
	//我们组合一个sql语句字符串，创建一个字符数组用于存储这个sql语句字符串
	char sql1[100] = "";
	sprintf(sql1,"create table %s (id int,name text);",table_name);
	//printf("111%s111", table_name);
	//将tablename以%s的格式放在“”之间，然后将“”之间的所有内容打印到屏幕
	//同理sprintf表示将table_name以%s格式放在那个位置，然后将“”之间的所有内容放入sql1中进行存储

	char * errmsg = NULL;//定义一个指针存放错误信息字符串的首地址的指针
	sqlite3_exec(db,sql1,NULL,NULL,&errmsg);
	//我们errmsg本身是NULL空指针，如果26行的sql语句有错误
	//26行结束之后errmsg中就有内容了
	if(errmsg != NULL)
		printf("sql语句错误信息：%s\n", errmsg);

	else
		printf("没有出现任何问题\n");

	//-------------功能2:插入id、name-----
	int id = 0;
	char name[20] = "";
	printf("请输入id：\n");
	scanf("%d",&id);
	printf("请输入name：\n");
	scanf("%s",name);//不用&因为name就是这个数组的地址
	char sql2[100] = "";
	sprintf(sql2,"insert into %s values(%d,\'%s\');",table_name,id,name);
	//注意。\'\'表示双引号
	errmsg  = NULL;
	sqlite3_exec(db,sql2,NULL,NULL,&errmsg);


	//-------------功能3:查询id对应的name
	printf("请输入id：\n");
	scanf("%d",&id);
	char sql3[100] = "";
	sprintf(sql3,"select name from %s where id = %d;",table_name,id);

	char **table = NULL;//结果集表
	int r = 0 , c = 0;//行、列
	sqlite3_get_table(db,sql3,&table,&r,&c,&errmsg);
	if(r!=0)//说明查询到了
		//查询到了之后使用的时候最好先画图（结果集图）
		//通过画图我们发现table[1]是我们用的数据
		printf("id为%d的name为：%s\n",id,table[1]);



	//-------------关闭数据库----------------
	sqlite3_close(db);
	

	return 0;
}