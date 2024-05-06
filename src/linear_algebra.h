#ifndef LINEAR_ALGEBRA_H 
#define LINEAR_ALGEBRA_H 

typedef struct s_vec3{
    float x;
    float y;
    float z;
} t_vec3;


typedef struct s_mat4{
    float col1[4];
    float col2[4];
    float col3[4];
    float col4[4];
} t_mat4;

void create_mat4(float matrix[4][4], float arg);
void rotate(float trans[4][4], float radians, float *vec_rotate);
void scale(float trans[4][4], float *vec_scale);
float radians(float degree);
void array_converter(float trans[4][4], float *array);
void translate(float trans[4][4], float *vec_trans);
void matrix_print(const char *name, float trans[4][4]);

//void create_mat4(t_mat4 *matrix, float arg);
//void rotate(mat4 *trans, float radians, vec3 *vec_rotate);
//void scale(mat4 *trans, vec3 *vec_scale);

#endif //LINEAR_ALGEBRA_H 
