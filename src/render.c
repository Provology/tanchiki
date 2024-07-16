#include "render.h"
#include"linear_algebra.h"
#include"transformations.h"


static float projection_matrix[4][4] = {0.0f}; // TODO make static const projection matrix

void create_ortho_proj(float left, float right, float bottom, float top)
{
    create_mat4(projection_matrix, 1.0f);
    projection_matrix[0][0] = 2.0 / (right - left);
    projection_matrix[1][1] = 2.0 / (top - bottom);
    projection_matrix[0][3] = -1 * (right + left) / (right - left);
    projection_matrix[1][3] = -1 * (top + bottom) / (top - bottom);

//    matrix_print("proj", projection_matrix);
    printf("l = %f, r = %f, t = %f, b = %f\n", left, right, top, bottom);
 //   float projection[4][4] = {
 //       {2.0/(800.0 - 0.0), 0.0f, 0.0f, -(800.0 + 0.0)/(800.0 - 0.0)},
 //       {0.0f, 2.0/(600.0 - 0.0), 0.0f, -(600.0 + 0.0)/(600.0 - 0.0)},
 //       {0.0f, 0.0f, -2.0/(-1.0 - 1.0), -(1.0 + (-1.0))/(1.0 - (-1.0))},
 //       {0.0f, 0.0f, 0.0f, 1.0f}
 //       };
}

void DrawSprite(unsigned int shaderProgram_tex, t_vbuff *vbuff, int texture, float position[3], float size[3], float angle, float color[3])
{
    float model[4][4] = {0.0f};
//    float projection_matrix[4][4] = {0.0f}; // TODO make static const projection matrix

//    create_ortho_proj(projection_matrix, 0.0f, 600.0f, 0.0f, 600.0f); 
//    printf("shader3=%d\n", shaderProgram_tex);
//    printf("vbuff=%d\n", vbuff->VBO);
    // prepare transformations
    glBindTexture(GL_TEXTURE_2D, texture);
    glUseProgram(shaderProgram_tex);
    create_mat4(model, 1.0f);
    translate(model, position); 
    rotate_centr(model, size, angle);
    scale(model, size); // last scale z = 1.0f

    transform(shaderProgram_tex, model, "model");
    transform(shaderProgram_tex, projection_matrix, "projection");
    // render textured quad
    glUniform3fv(glGetUniformLocation(shaderProgram_tex, "spriteColor"), 1, color);
    glUniform1i(glGetUniformLocation(shaderProgram_tex, "image"), 0);

//	float copy[4][4] = {{0.0}};
//	memcpy(copy, projection_matrix, 16 * sizeof(float));
//    multiply_matrix(copy, model);
//    matrix_print("proj_copy", copy);
//    matrix_print("proj", projection_matrix);
//    matrix_print("model", model);

//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, texture);

      glBindVertexArray(vbuff->VAO);
      glDrawArrays(GL_TRIANGLES, 0, 6);
//      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//    glBindVertexArray(0);
}


