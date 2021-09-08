#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
 
guint timer = 0;//定时器id
 
void set_widget_font_size(GtkWidget *widget, int size, int is_button)  
{  
            GtkWidget *labelChild;    
            PangoFontDescription *font;    
            gint fontSize = size;    
          
            font = pango_font_description_from_string("Sans");//"Sans"字体名     
            pango_font_description_set_size(font, fontSize*PANGO_SCALE);//设置字体大小     
          
            if(is_button){  
                labelChild = gtk_bin_get_child(GTK_BIN(widget));//取出GtkButton里的label    
            }else{  
                labelChild = widget;  
            }  
          
            //设置label的字体，这样这个GtkButton上面显示的字体就变了  
            gtk_widget_modify_font(GTK_WIDGET(labelChild), font);  
            pango_font_description_free(font);  
}  
 
 
gboolean deal_time( gpointer* label )   
{  
    char buf[5] = "";  
    static int num = 60;  
    num--;  
    sprintf(buf, "%d", num);  
    gtk_label_set_text(GTK_LABEL(label), buf);  
  
    if(0 == num){  
        num = 61;  
        g_source_remove(timer); // 移除定时器   
    }  
  
    return TRUE;//尽量返回TRUE  
}  
  
 
 
int main(int argc,char *argv[])
{
        //1.gtk环境初始化
        gtk_init(&argc, &argv);
 
        //2.创建一个窗口
        GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        //设置窗口标题
        gtk_window_set_title(GTK_WINDOW(window), "倒计时");
        //设置窗口宽度
        gtk_container_set_border_width(GTK_CONTAINER(window), 0);
 
 
        //3.设置窗口默认大小
        gtk_window_set_default_size(GTK_WINDOW(window), 320, 400);
 
        //设置窗口在显示器中间位置
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
        g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
 
        //4.倒计时显示区
        GtkWidget *label = gtk_label_new("60");
        set_widget_font_size(label, 230, FALSE);
        gtk_container_add(GTK_CONTAINER(window), label);
 
        //定时器的创建，label传给回调函数
        timer = g_timeout_add(1000, (GSourceFunc)deal_time, (gpointer)label);
 
        //显示所有窗口
        gtk_widget_show_all(window);
 
        //主事件
        gtk_main();
 
 
        return 0;
}