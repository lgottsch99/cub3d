#ifndef MAPS_H
#define MAPS_H

typedef struct s_img
{
    void *img_ptr;
    char *pixels_ptr;
    int bpp;
    int endian;
    int line_length;
}   t_img;



#endif
