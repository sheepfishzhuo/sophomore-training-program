//--------其他函数-----------
void chang_background(GtkWidget *widget, int w, int h, const gchar *path)
{   
    gtk_widget_set_app_paintable(widget, TRUE);     
    //允许窗口可以绘图  
    gtk_widget_realize(widget);     
    //避免背景图片重叠
    gtk_widget_queue_draw(widget);  
    GdkPixbuf *src_pixbuf = gdk_pixbuf_new_from_file(path, NULL);   
    //创建图片资源对象  
    GdkPixbuf *dst_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, w, h, GDK_INTERP_BILINEAR);     
    GdkPixmap *pixmap = NULL;   
    //创建pixmap图像    
    gdk_pixbuf_render_pixmap_and_mask(dst_pixbuf, &pixmap, NULL, 128);  
    //设置一张背景图
    gdk_window_set_back_pixmap(widget->window, pixmap, FALSE);  
    //释放资源  
    g_object_unref(src_pixbuf); 
    g_object_unref(dst_pixbuf); 
    g_object_unref(pixmap);
 }
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