#include <stdio.h>
#include "sqlite3.h"

//-------------其他函数区------------
//------------------封装好的mygetch------------------
//获取键盘输入的一个键值，而且是没有回车、没有回显
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
char mygetch()
{
        struct termios oldt, newt;
        char ch;
        tcgetattr( STDIN_FILENO, &oldt );
        newt = oldt;
        newt.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newt );
        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
        return ch;
}
//-----------进入管理员系统-----------
void to_admin_cd(void)
{
    printf("\n");
    printf("\n");
    printf("您已经进入到管理员系统\n");
    printf("按下“1”，注册成为管理员\n");
    printf("按下“2”，管理员登录\n");
    printf("按下“0”，返回上一层\n");
    char i = mygetch();
    if (i =='0')
        return;
    else if (i == '1')
    {
        //调用一个函数进行注册
        printf("请输入您注册的账号：\n");
        char id[20] = "";
        scanf("%s",id);
        printf("请输入您注册的密码：\n");
        char passwd[20] = "";
        scanf("%s",passwd);
        //注册就是查询有没有注册，如果没有就插入（注册），如果有就算了
        sqlite3* db;
        sqlite3_open("vip.db",&db);//打开数据库sqlite3_open
        char sql1[100] = "";
        sprintf(sql1,"select *from admin where id = \'%s\';",id);
        char **table = NULL;
        int r = 0 , c = 0;
        char *errmsg = NULL;
        sqlite3_get_table(db,sql1,&table, &r,&c,&errmsg);
        if (r!=0)
        {
            printf("当前管理员账户已经注册，请登录\n");
            sqlite3_close(db);
            return;
        }
        char sql2[100] = "";
        sprintf(sql2,"insert into admin values(\'%s\',\'%s\');",id,passwd);
        sqlite3_exec(db,sql2,NULL,NULL,&errmsg);
        sqlite3_close(db);

    }
    else if (i == '2')
    {
        //调用一个函数进行登录
        printf("请输入您登录的账号：\n");
        char id[20] = "";
        scanf("%s",id);
        printf("请输入您登录的密码：\n");
        char passwd[20] = "";
        scanf("%s",passwd);
        sqlite3* db;
        sqlite3_open("vip.db",&db);//打开数据库sqlite3_open
        char sql1[100] = "";
        sprintf(sql1,"select * from admin where id = \'%s\' and passwd = \'%s\';",id,passwd);
        char **table = NULL;
        int r = 0 , c = 0;
        char *errmsg = NULL;
        sqlite3_get_table(db,sql1,&table,&r,&c,&errmsg);
        if(r!=0)
            printf("登录成功\n");
        else
            printf("登录失败\n");

    }
    else
        printf("您输入有误，正在自动返回.....\n");


}


//-------------数据库操作区---------------
//----初始化数据库------------------------
void sqlite_my_init(void)
{
    sqlite3* db;
    sqlite3_open("vip.db",&db);//打开数据库sqlite3_open
    //思考我们要做什么？增、删、改、查询
    //创建表---增加---写操作
    //需要的东西：admin==id-text \ passwd-text
    //user==taocan-text\time-time
    //vip==tel-text\passwd-text\yue-int
    char sql1[100] = "create table admin (id text,passwd text);";
    char sql2[100] = "create table user (taocan text,time time);";
    char sql3[100] = "create table vip (tel text,passwd text,yue int)";
    //看一下sql语句是读还是写sqlite3_exec
    char *errmsg  = NULL;
    sqlite3_exec(db,sql1,NULL,NULL,&errmsg);
    sqlite3_exec(db,sql2,NULL,NULL,&errmsg);
    sqlite3_exec(db,sql3,NULL,NULL,&errmsg);
    sqlite3_close(db);
}



//--------------主函数区-----------------
int main(int argc, char const *argv[])
{
    sqlite_my_init();//我们调用了一个函数：数据库初始化（创建数据表的）
    while(1)
    {

        printf("\n");
        printf("\n");
        // system("clear"); 
        printf("欢迎光临江哥哥洗浴中心\n");
        printf("管理员使用请按“1”\n");
        printf("VIP会员使用请按“2”\n");
        printf("非会员使用请按“3”\n");
        printf("退出系统请按“0”\n");
        char i = mygetch();
        
        if (i =='0')
        {
            return 0;
        }
        else if (i == '1')
        {
            printf("正在进入管理员系统.....\n");
            to_admin_cd();//进入管理员程序
        }
        else if (i == '2')
        {
            printf("正在进入VIP系统.....\n");
        }
        else if (i == '3')
        {
            printf("正在进入非会员系统.....\n");
        }
        else
            printf("请重新输入\n");
    }
    return 0;
}