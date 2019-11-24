#ifndef BMP_PARSER__H
# define BMP_PARSER__H

# define BMP_R_BUFF 4096
# define BMP_HEADER_SIZE 54
# define BMP_DIB_HEADER_SIZE 40
# define BMP_MAGIC_VALUE 0x4D42 
# define BMP_NUM_PLANE 1
# define BMP_COMPRESSION 0
# define BMP_NUM_COLORS 0
# define BMP_IMPORTANT_COLORS 0
# define BMP_BITS_PER_PIXEL 24
# define BMP_BITS_PER_BYTE 8

#include <wolf3d.h>

typedef struct		s_bmp_h				// Total: 54 bytes
{
	uint16_t		type;				// Magic identifier: 0x4d42
	uint32_t		size;				// File size in bytes
	uint16_t		reserved1;			// Not used
	uint16_t		reserved2;			// Not used
	uint32_t		offset;				// Offset to image data in bytes from beginning of file (54 bytes)
	uint32_t		dib_header_size;	// DIB Header size in bytes (40 bytes)
	int32_t			width_px;			// Width of the image
	int32_t			height_px;			// Height of image
	uint16_t		num_planes;			// Number of color planes
	uint16_t		bits_per_pixel;		// Bits per pixel
	uint32_t		compression;		// Compression type
	uint32_t		image_size_bytes;	// Image size in bytes
	int32_t			x_resolution_ppm;	// Pixels per meter
	int32_t			y_resolution_ppm;	// Pixels per meter
	uint32_t		num_colors;			// Number of colors
	uint32_t		important_colors;	// Important colors
}					t_bmp_h;

typedef struct		s_bmp_color_h
{
	uint32_t		red_mask;			// Bit mask for the red channel 0x00ff0000
	uint32_t		green_mask;			// Bit mask for the green channel 0x0000ff00
	uint32_t		blue_mask;			// Bit mask for the blue channel 0x000000ff
	uint32_t		alpha_mask;			// Bit mask for the alpha channel 0xff000000
	uint32_t		color_space_type;	// Default "sRGB" (0x73524742)
	uint32_t		unused[16];			// Unused data for sRGB color space
}					t_bmp_color_h;

typedef struct		s_bmp_image
{
	t_bmp_h			head;				// bmp file header (t_bmp_h)
	t_bmp_color_h	c_head;				// bmp file color header (t_bmp_color_h)
	unsigned char	*data;				// pixels(maybe uint8_t for old)
}					t_bmp_image;

#endif
