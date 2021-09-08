#include <stdio.h>
#include "sqlite3.h"
int main(int argc, char const *argv[])
{
	sqlite3 *db;
	int ret = sqlite3_open("admin.db",&db);
	if(ret != SQLITE_OK)
		printf("数据库打开失败\n");
	else 
		printf("数据库打开成功\n");

	ret = sqlite3_close(db);
	if(ret != SQLITE_OK)
		printf("数据库关闭失败\n");
	else 
		printf("数据库关闭成功\n");

	return 0;
}