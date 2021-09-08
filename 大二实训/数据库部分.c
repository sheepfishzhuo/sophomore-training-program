//-----------数据库函数区---------------
void my_sql_init(void)
{
    //打开数据库
    sqlite3* db;
    sqlite3_open("book.db",&db);
    //看你要做什么
    //获取你需要的数据
    //组一个sql语句
    char sql1[100] = "create table user (name text,id text, rmb int,passwd text);";
    //看是读还是写---建表--写
    char *errmsg = NULL;
    sqlite3_exec(db,sql1,NULL,NULL,&errmsg);
    //发给数据库
    //关闭数据库
    sqlite3_close(db);
}



//----------回调函数区中的window_user_menu_to_window_user_cx窗口-----------------
void window_user_menu_to_window_user_cx(GtkButton* button,gpointer user_data)
{
    //先查询余额，设置到label上
    sqlite3* db;
    sqlite3_open("book.db",&db);

    const char * id = gtk_entry_get_text(GTK_ENTRY(entry_login_id));
    char sql1[100] = "";//定义一个字符数组用于存储你组合的sql语句
    sprintf(sql1,"select rmb from user where id = \'%s\';",id);//进行组合
    char **table = NULL;
    int r = 0, c = 0;
    char *errmsg = NULL;
    sqlite3_get_table(db,sql1,&table,&r,&c,&errmsg);
    //因为我们查询一列
    //因此我们的结果集应该是2行1列
    //第一行是列名称“rmb”   table[0]
    //第二行就是我们的rmb的值  table[1]
    //所以我们用的余额这个值就是table[1]
    if (r!=0)
    {
        //我们table[1]就是我们的余额的值
        char haha[200] = "";
        sprintf(haha,"<span foreground='red' font_desc='27'>%s</span>",table[1]);
        gtk_label_set_markup(GTK_LABEL(label_user_cx_yue),haha);
        sqlite3_close(db);
    }
    
    //显示下一个页面
    gtk_widget_show_all(window_user_cx);
    //隐藏当前的页面
    gtk_widget_hide_all(window_user_menu);
}



//-----------数据库操作的回调函数----------
void user_do_zc_zc(GtkButton* button,gpointer user_data)
{
    sqlite3* db;
    sqlite3_open("book.db",&db);

    const char * id = gtk_entry_get_text(GTK_ENTRY(entry_zc_id));
    const char * passwd = gtk_entry_get_text(GTK_ENTRY(entry_zc_passwd));
    const char * name = gtk_entry_get_text(GTK_ENTRY(entry_zc_name));
    
    char sql1[100] = "";//定义一个字符数组用于存储你组合的sql语句
    sprintf(sql1,"select *from user where id = \'%s\';",id);//进行组合
    char **table = NULL;
    int r = 0, c = 0;
    char *errmsg = NULL;
    sqlite3_get_table(db,sql1,&table,&r,&c,&errmsg);
    if(r!=0)//说明有效数据行不为0 也就是查询到了
    {
        gtk_entry_set_text(GTK_ENTRY(entry_zc_id),"您注册过了，请直接登录");
        sqlite3_close(db);
        return;
    }
    char sql2[100] = "";
    sprintf(sql2,"insert into user values (\'%s\',\'%s\',0,\'%s\');",name,id,passwd);
    //name text,id text, rmb int,passwd text
    sqlite3_exec(db,sql2,NULL,NULL,&errmsg);
    if(errmsg!=NULL)
        printf("%s\n", errmsg);
    gtk_entry_set_text(GTK_ENTRY(entry_zc_id),"注册成功");
        
    sqlite3_close(db);
}
void user_do_login_login(GtkButton* button,gpointer user_data)
{
    sqlite3* db;
    sqlite3_open("book.db",&db);

    const char * id = gtk_entry_get_text(GTK_ENTRY(entry_login_id));
    const char * passwd = gtk_entry_get_text(GTK_ENTRY(entry_login_passwd));
    
    char sql1[100] = "";//定义一个字符数组用于存储你组合的sql语句
    sprintf(sql1,"select *from user where id = \'%s\' and passwd = \'%s\';",id,passwd);//进行组合
    char **table = NULL;
    int r = 0, c = 0;
    char *errmsg = NULL;
    sqlite3_get_table(db,sql1,&table,&r,&c,&errmsg);
    if (r != 0 )//查询到了就登录成功
    {
        gtk_widget_show_all(window_user_menu);
        gtk_widget_hide_all(window_login);
        sqlite3_close(db);
        return;
    }
    gtk_entry_set_text(GTK_ENTRY(entry_login_id),"您输入的账号或密码有误");
    sqlite3_close(db);
}
void user_do_ck(GtkButton* button,gpointer user_data)
{
    //打开数据库
    // 获取需要的数据
    // 组合一个sql语句
    // 发给数据库
    // 关闭数据库
    sqlite3* db;
    sqlite3_open("book.db",&db);

    const char * id = gtk_entry_get_text(GTK_ENTRY(entry_login_id));
    const char * ck_rmb = gtk_entry_get_text(GTK_ENTRY(entry_ck_rmb));
    //先查询余额
    char sql1[100] = "";//定义一个字符数组用于存储你组合的sql语句
    sprintf(sql1,"select rmb from user where id = \'%s\';",id);//进行组合
    char **table = NULL;
    int r = 0, c = 0;
    char *errmsg = NULL;
    sqlite3_get_table(db,sql1,&table,&r,&c,&errmsg);
    if (r!=0)
    {
        //然后相加
        //然后修改到数据库中
        int rmb_new = atoi(table[1]) + atoi(ck_rmb);
        //atoi表示将数字字符串转为int
        char sql2[200] = "";
        sprintf(sql2,"update user set rmb = %d where id = \'%s\';",rmb_new,id);
        sqlite3_exec(db,sql2,NULL,NULL,&errmsg);
        //注意转账或取款的时候需要判断结果是否小于0
        sqlite3_close(db);
        gtk_entry_set_text(GTK_ENTRY(entry_ck_rmb),"充值成功");
    }
    
}