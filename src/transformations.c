#include "transformations.h"

// LINEAR ALGEBRA PART
float vec_rotate[3] = {0.0f, 0.0f, 1.0f};
float vec_scale[3] = {0.5f, 0.5f, 0.5f};
float vec_tl[3] = {0.5f, -0.5f, 0.0f};


void transform(unsigned int shaderProgram_tex, float trans[4][4], const char *name)
{
     unsigned int transformLoc; 
     glUseProgram(shaderProgram_tex);
     transformLoc = glGetUniformLocation(shaderProgram_tex, name);
     glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &trans[0][0]);
}

void matrix_trans1(float trans[4][4])
{
	float angle = glfwGetTime();
        create_mat4(trans, 1.0f);
	translate(trans, vec_tl); 
//        rotate(trans, angle, vec_rotate);
//	matrix_print("kekvs", trans);
//	printf("angle = %f\n", angle);
}

void matrix_trans2(float trans[4][4])
{
	float vec_tl2[3] = {-0.5, 0.5, 0.0};
//	float scale_v = sin(glfwGetTime());
        create_mat4(trans, 1.0f);
//	create_vec3(vec_scale, scale_v);
	translate(trans, vec_tl2);
//	scale(trans, vec_scale);
//	matrix_print("kekvs", trans);
//	printf("angle = %f\n", angle);
}


