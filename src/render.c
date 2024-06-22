#include "render.h"
#include"linear_algebra.h"
#include"transformations.h"

void DrawSprite(unsigned int shaderProgram_tex, t_vbuff *vbuff, int texture, float position[3], float size[3], float angle, float color[3], unsigned int width, unsigned int height)
{
    float model[4][4] = {0.0f};
    float projection[4][4] = {0.0f};

    // prepare transformations
    glBindTexture(GL_TEXTURE_2D, texture);
    glUseProgram(shaderProgram_tex);
    create_mat4(model, 1.0f);
    create_ortho_proj(projection, 0.0f, width, 0.0f, height); 
    translate(model, position); 
    rotate_centr(model, size, angle);
    scale(model, size); // last scale z = 1.0f

    transform(shaderProgram_tex, model, "model");
    transform(shaderProgram_tex, projection, "projection");
    // render textured quad
    glUniform3fv(glGetUniformLocation(shaderProgram_tex, "spriteColor"), 1, color);
    glUniform1i(glGetUniformLocation(shaderProgram_tex, "image"), 0);

//    multiply_matrix(projection, model);
//    matrix_print("proj", projection);
//    matrix_print("model", model);

//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, texture);

      glBindVertexArray(vbuff->VAO);
      glDrawArrays(GL_TRIANGLES, 0, 6);
//      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//    glBindVertexArray(0);
}


