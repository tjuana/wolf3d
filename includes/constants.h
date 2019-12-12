/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:21:47 by tjuana            #+#    #+#             */
/*   Updated: 2019/12/12 19:26:03 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H
# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920
# define TEXTURES_NUMBER 23
# define THREADS 10
# define TEX_W 64
# define TEX_H 64
# define ONE_ANIM 17
# define FULL_ANIM ONE_ANIM * 4 - 4
# define KEYS_NBR 66
# define MAX_DOORS_NBR 20


# define C_R 0x00FF0000
# define C_G 0x0000FF00
# define C_B 0x000000FF

typedef struct			s_const
{
	double				crs;
	double				srs;
	double				mcrs;
	double				msrs;
	double				camera_x_cnst;
	int					half_height;
}					t_const;
#endif

// // Errors
// #define LOADBMP_NO_ERROR 0

// #define LOADBMP_OUT_OF_MEMORY 1

// #define LOADBMP_FILE_NOT_FOUND 2
// #define LOADBMP_FILE_OPERATION 3

// #define LOADBMP_INVALID_FILE_FORMAT 4

// #define LOADBMP_INVALID_SIGNATURE 5
// #define LOADBMP_INVALID_BITS_PER_PIXEL 6


// // Components
// #define LOADBMP_RGB  3
// #define LOADBMP_RGBA 4


// #ifdef LOADBMP_IMPLEMENTATION
// #	define LOADBMP_API
// #else
// #	define LOADBMP_API extern
// #endif


// // LoadBMP uses raw buffers and support RGB and RGBA formats.
// // The order is RGBRGBRGB... or RGBARGBARGBA..., from top left
// // to bottom right, without any padding.


// LOADBMP_API unsigned int loadbmp_decode_file(
// 	const char *filename, unsigned char **imageData, unsigned int *width, unsigned int *height, unsigned int components);

// LOADBMP_API unsigned int loadbmp_encode_file(
// 	const char *filename, const unsigned char *imageData, unsigned int width, unsigned int height, unsigned int components);


// #ifdef LOADBMP_IMPLEMENTATION

// // Disable Microsoft Visual C++ compiler security warnings for fopen, strcpy, etc being unsafe
// #if defined(_MSC_VER) && (_MSC_VER >= 1310)
// #	pragma warning(disable: 4996)
// #endif

// #include <stdlib.h> /* malloc(), free() */
// #include <string.h> /* memset(), memcpy() */
// #include <stdio.h> /* fopen(), fwrite(), fread(), fclose() */


// LOADBMP_API unsigned int loadbmp_decode_file(
// 	const char *filename, unsigned char **imageData, unsigned int *width, unsigned int *height, unsigned int components)
// {
// 	FILE *f = fopen(filename, "rb");

// 	if (!f)
// 		return LOADBMP_FILE_NOT_FOUND;

// 	unsigned char bmp_file_header[14];
// 	unsigned char bmp_info_header[40];
// 	unsigned char bmp_pad[3];

// 	unsigned int w, h;
// 	unsigned char *data = NULL;

// 	unsigned int x, y, i, padding;

// 	memset(bmp_file_header, 0, sizeof(bmp_file_header));
// 	memset(bmp_info_header, 0, sizeof(bmp_info_header));

// 	if (fread(bmp_file_header, sizeof(bmp_file_header), 1, f) == 0)
// 	{
// 		fclose(f);
// 		return LOADBMP_INVALID_FILE_FORMAT;
// 	}

// 	if (fread(bmp_info_header, sizeof(bmp_info_header), 1, f) == 0)
// 	{
// 		fclose(f);
// 		return LOADBMP_INVALID_FILE_FORMAT;
// 	}

// 	if ((bmp_file_header[0] != 'B') || (bmp_file_header[1] != 'M'))
// 	{
// 		fclose(f);
// 		return LOADBMP_INVALID_SIGNATURE;
// 	}

// 	if ((bmp_info_header[14] != 24) && (bmp_info_header[14] != 32))
// 	{
// 		fclose(f);
// 		return LOADBMP_INVALID_BITS_PER_PIXEL;
// 	}

// 	w = (bmp_info_header[4] + (bmp_info_header[5] << 8) + (bmp_info_header[6] << 16) + (bmp_info_header[7] << 24));
// 	h = (bmp_info_header[8] + (bmp_info_header[9] << 8) + (bmp_info_header[10] << 16) + (bmp_info_header[11] << 24));
	
// 	if ((w > 0) && (h > 0))
// 	{
// 		data = (unsigned char*)malloc(w * h * components);

// 		if (!data)
// 		{
// 			fclose(f);
// 			return LOADBMP_OUT_OF_MEMORY;
// 		}

// 		for (y = (h - 1); y != -1; y--)
// 		{
// 			for (x = 0; x < w; x++)
// 			{
// 				i = (x + y * w) * components;

// 				if (fread(data + i, 3, 1, f) == 0)
// 				{
// 					free(data);

// 					fclose(f);
// 					return LOADBMP_INVALID_FILE_FORMAT;
// 				}

// 				data[i] ^= data[i + 2] ^= data[i] ^= data[i + 2]; // BGR -> RGB

// 				if (components == LOADBMP_RGBA)
// 					data[i + 3] = 255;
// 			}

// 			padding = ((4 - (w * 3) % 4) % 4);

// 			if (fread(bmp_pad, 1, padding, f) != padding)
// 			{
// 				free(data);

// 				fclose(f);
// 				return LOADBMP_INVALID_FILE_FORMAT;
// 			}
// 		}
// 	}

// 	(*width) = w;
// 	(*height) = h;
// 	(*imageData) = data;

// 	fclose(f);

// 	return LOADBMP_NO_ERROR;
// }


// LOADBMP_API unsigned int loadbmp_encode_file(
// 	const char *filename, const unsigned char *imageData, unsigned int width, unsigned int height, unsigned int components)
// {
// 	FILE *f = fopen(filename, "wb");

// 	if (!f)
// 		return LOADBMP_FILE_OPERATION;

// 	unsigned char bmp_file_header[14] = { 'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0 };
// 	unsigned char bmp_info_header[40] = { 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0 };
// 	const unsigned char bmp_pad[3] = { 0, 0, 0 };

// 	const unsigned int size = 54 + width * height * 3; // 3 as the BMP format uses 3 channels (red, green, blue and NO alpha)

// 	unsigned int x, y, i, padding;

// 	unsigned char pixel[3];

// 	bmp_file_header[2] = (unsigned char)(size);
// 	bmp_file_header[3] = (unsigned char)(size >> 8);
// 	bmp_file_header[4] = (unsigned char)(size >> 16);
// 	bmp_file_header[5] = (unsigned char)(size >> 24);

// 	bmp_info_header[4] = (unsigned char)(width);
// 	bmp_info_header[5] = (unsigned char)(width >> 8);
// 	bmp_info_header[6] = (unsigned char)(width >> 16);
// 	bmp_info_header[7] = (unsigned char)(width >> 24);

// 	bmp_info_header[8] = (unsigned char)(height);
// 	bmp_info_header[9] = (unsigned char)(height >> 8);
// 	bmp_info_header[10] = (unsigned char)(height >> 16);
// 	bmp_info_header[11] = (unsigned char)(height >> 24);

// 	if (fwrite(bmp_file_header, 14, 1, f) == 0)
// 	{
// 		fclose(f);
// 		return LOADBMP_FILE_OPERATION;
// 	}

// 	if (fwrite(bmp_info_header, 40, 1, f) == 0)
// 	{
// 		fclose(f);
// 		return LOADBMP_FILE_OPERATION;
// 	}

// 	for (y = (height - 1); y != -1; y--)
// 	{
// 		for (x = 0; x < width; x++)
// 		{
// 			i = (x + y * width) * components;

// 			memcpy(pixel, imageData + i, sizeof(pixel));

// 			pixel[0] ^= pixel[2] ^= pixel[0] ^= pixel[2]; // RGB -> BGR

// 			if (fwrite(pixel, sizeof(pixel), 1, f) == 0)
// 			{
// 				fclose(f);
// 				return LOADBMP_FILE_OPERATION;
// 			}
// 		}

// 		padding = ((4 - (width * 3) % 4) % 4);

// 		if (fwrite(bmp_pad, 1, padding, f) != padding)
// 		{
// 			fclose(f);
// 			return LOADBMP_FILE_OPERATION;
// 		}
// 	}

// 	fclose(f);

// 	return LOADBMP_NO_ERROR;
// }


// #endif

// #ifdef __cplusplus
// }
// #endif

// #endif

