#include"vertices.h"

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
//float vertices[] = {
//    // positions          // colors           // texture coords
//     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
//     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
//    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
//    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
//};

//unsigned int indices[] = {
//    0, 1, 3, // first triangle
//    1, 2, 3  // second triangle
//};

//    float vertices[] = {
//        // positions          // texture coords
//         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
//         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
//        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
//    };
//    unsigned int indices[] = {
//        0, 1, 3, // first triangle
//        1, 2, 3  // second triangle

// void vertices_buffer(t_vbuff *vbuff)
// {
//     unsigned int VBO, VAO, EBO;
// 
//     VBO = vbuff->VBO;
//     VAO = vbuff->VAO;
//     EBO = vbuff->EBO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);
//     glGenBuffers(1, &EBO);
// 
//     glBindVertexArray(VAO);
// 
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//     // position attribute
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
//     // color attribute
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//     glEnableVertexAttribArray(1);
//     // texture coord attribute
//     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//     glEnableVertexAttribArray(2);
//     vbuff->VBO = VBO;
//     vbuff->VAO = VAO;
//     vbuff->EBO = EBO;
// }

void initRenderData(t_vbuff *vbuff)
{
    // configure VAO/VBO
      static float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &vbuff->VAO);
    glGenBuffers(1, &vbuff->VBO);
    glGenBuffers(1, &vbuff->EBO);

    glBindVertexArray(vbuff->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, vbuff->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
}


