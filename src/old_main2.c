#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include"shader_module.h"
#include"texture_module.h"

// constants
#define SCR_WIDTH 800
#define SCR_HEIGHT 600

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
float vertices_triangle[] = {// TODO
	// first triangle{}
    -0.5f, -0.5f, 0.0f, // left
     0.0f, -0.5f, 0.0f, // right
    -0.25f,  0.5f, 0.0f, // top
};
float vertices_triangle2[] = {// TODO
	// second triangle
	 0.0f, -0.5f, 0.0f, // left
     0.5f, -0.5f, 0.0f, // right
     0.25f, 0.5f, 0.0f, // top
	// // first triangle{}
	// -0.9f, -0.5f, 0.0f,  // left 
	// -0.0f, -0.5f, 0.0f,  // right
	// -0.45f, 0.5f, 0.0f,  // top 
	// // second triangle
	// 0.0f, -0.5f, 0.0f,  // left
	// 0.9f, -0.5f, 0.0f,  // right
	// 0.45f, 0.5f, 0.0f   // top 
};

float vertices_square[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};  

float vertices_color[] = {
	// position			 color
     0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// left
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// right
     0.25f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,// top
};

float vertices_textur[] = {
	// position	 color		  texture coord
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // bottom left
    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top left
};

float texCoords[] = {
	0.0f, 0.0f,	  // lower-left
	1.0f, 0.0f,   // lower-right
	0.5f, 1.0f    // top-center corner
};

int loop(unsigned int loc_shaderProgram, unsigned int loc_VAO)// TODO
{
	// [...]
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	float offsetValue = greenValue;
	int vertexColorLocation = glGetUniformLocation(loc_shaderProgram, "ourColor");
	int vertexOffsetLocation = glGetUniformLocation(loc_shaderProgram, "offset");

	// ..:: Drawing code (in render loop) :: ..
	// 4. draw the object
	glUseProgram(loc_shaderProgram);
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);// color change
	glUniform1f(vertexOffsetLocation, greenValue);// offset change
	glBindVertexArray(loc_VAO);
	// seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// glBindVertexArray(0); // no need to unbind it every time

	return (0);
}

int main (void)
{
	// glfw: initialize and configure
    // ------------------------------
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// glfw window creation
    // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(window);

	// glad: load all OpenGL function pointers
    // ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return (-1);
	}

	// glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    // build and compile our shader program
    // ------------------------------------
  	unsigned int shaderProgram;//TODO create shader program object
	shaderProgram = build_shader(
		"/home/ruslan/Desktop/PROJ/ping_pong/src/shaders/shader2.vs", // shader1
		"/home/ruslan/Desktop/PROJ/ping_pong/src/shaders/shader2.fs"  // shader3
		);
   // link shader2
	unsigned int shaderProgram2;//TODO create shader program object
	shaderProgram2 = build_shader(
		"/home/ruslan/Desktop/PROJ/ping_pong/src/shaders/shader.vs", 
		"/home/ruslan/Desktop/PROJ/ping_pong/src/shaders/shader1.fs"
		);
	unsigned int shaderProgram_col;//TODO create shader program object
	shaderProgram_col = build_shader(
		"/home/ruslan/Desktop/PROJ/ping_pong/src/shaders/shader.vs", 
		"/home/ruslan/Desktop/PROJ/ping_pong/src/shaders/shader.fs"
		);


	// glUseProgram(shaderProgram);//TODO shaders ready

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	unsigned int VBO[3];// TODO create vertex buffer object
	glGenBuffers(3, VBO);

	unsigned int VAO[3];
	// unsigned int VAO_SQ;// TODO create vertex array object
	glGenVertexArrays(3, VAO);
	// glGenVertexArrays(1, &VAO_SQ);

	// ..:: Initialization code (done once (unless your object frequently changes)) :: ..
	// 1. bind Vertex Array Object
	glBindVertexArray(VAO[0]);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_color), vertices_color, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// 3. then set our vertex attributes pointers

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// ..:: Initialization code :: ..
	// 1. bind Vertex Array Object
	// glBindVertexArray(VAO_SQ);
	glBindVertexArray(VAO[2]);
	// // 2. copy our vertices array in a vertex buffer for OpenGL to use
	// glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_square), vertices_square, GL_STATIC_DRAW);
	// // 3. copy our index array in a element buffer for OpenGL to use
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// // 4. then set the vertex attributes pointers
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindTexture(GL_TEXTURE, texture);
	glBindVertexArray(VAO);




	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER , GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER , GL_LINEAR);
	// float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	int width, height, color_channels;
	printf("lol\n");
	unsigned char *data = texture_unpack(
		"/home/ruslan/Downloads/banana.png",
		&width, &height, &color_channels);
	
	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		// glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Failed to create texture\n");
	}
	texture_free(data);





    // render loop
    // -----------
	while(!glfwWindowShouldClose(window))
	{
		// input
        // -----
		processInput(window);

		// render
        // ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		loop(shaderProgram, VAO[0]);

		loop(shaderProgram_col, VAO[1]);
		// squre_loop(shaderProgram, VAO_SQ);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();    
	}

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(2, VAO);
    // glDeleteVertexArrays(1, &VAO_SQ);
    glDeleteBuffers(2, VBO);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgram2);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();

	return(0);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

