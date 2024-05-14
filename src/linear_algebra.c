#include <math.h>
#include <string.h>
#include <stdio.h>
#include "linear_algebra.h"

#define PI 3.14159265359

void add_matrix(float matr1[4][4], float matr2[4][4])
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			matr1[i][j] += matr2[i][j];
		}
	}
}

void multiply_matrix(float matr1[4][4], float matr2[4][4])
{
	float copy[4][4] = {{0.0}};
	float val;

	memcpy(copy, matr1, 16 * sizeof(float));
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			val = 0.0;
			for(int k = 0; k < 4; k++)
			{
				val += copy[i][k] * matr2[k][j];
			}
			matr1[i][j] = val;
		}
	}
}

void create_mat4(float matrix[4][4], float arg)
{
	memset(matrix, 0, 16 * sizeof(float));
	for(int i = 0; i < 4; i++)
	{
		matrix[i][i] = arg;
	}
}

void create_vec3(float vec3[3], float arg)
{
	memset(vec3, 0, 3 * sizeof(float));
	for(int i = 0; i < 3; i++)
	{
		vec3[i] = arg;
	}
}

void rotate(float trans[4][4], float radians, float *vec_rotate)
{
	float rot[4][4] = {{0.0}};
	float cos_val = cos(radians);
	float sin_val = sin(radians);
	(void)vec_rotate;

	for(int i = 0; i < 4; i++)
	{
		rot[i][i] = 1.0;	
	}
	rot[0][0] = cos_val;	
	rot[0][1] = -sin_val;	
	rot[1][0] = sin_val;	
	rot[1][1] = cos_val;

	multiply_matrix(trans, rot);
}

void scale(float trans[4][4], float *vec_scale)
{
	float scale_m[4][4] = {{0.0}};

	for(int i = 0; i < 3; i++)
	{
		scale_m[i][i] = vec_scale[i];	
	}	
	scale_m[3][3] = 1.0;
	multiply_matrix(trans, scale_m);
}

void translate(float trans[4][4], float *vec_trans)
{
	float tl_m[4][4] = {{0}};
	for(int i = 0; i < 3; i++)
	{
		tl_m[i][i] = 1.0;
		tl_m[i][3] = vec_trans[i];
//		trans[i][i] = 1.0;
//		trans[i][3] = vec_trans[i];
	}
	tl_m[3][3] = 1.0;
//	trans[3][3] = 1.0;

	multiply_matrix(trans, tl_m);
	//multiply_matrix(tl_m, trans);
	//memcpy(trans, tl_m, 16 * sizeof(float));
}

void array_converter(float trans[4][4], float *array)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			array[4*i + j] = trans[i][j];
		}
	}
}

float radians(float degree)
{
	return(degree * (PI / 180));
}

void matrix_print(const char *name, float trans[4][4])
{
    for(int i = 0; i < 4; i++)
    {
	    for(int j = 0; j < 4; j++)
	    {
		    printf("%s %d = %f\n",name, 4 * i + j, trans[i][j]);
	    }
    }
}


