#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <stdio.h>
#include"shader_module.h"


// constants
#define SCR_WIDTH 800
#define SCR_HEIGHT 600


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
	"out vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);"
    "}\0";

// const char *vertexShaderSource_col = "#version 330 core\n"
// 	"layout (location = 0) in vec3 aPos;\n"
// 	"layout (location = 1) in vec3 aColor;\n"

// 	"out vec3 ourColor;\n"

// 	"void main()\n"
// 	"{\n"
// 		"gl_Position = vec4(aPos, 1.0);\n"
// 		"ourColor = aColor;\n"
// 	"}\0";


const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec4 vertexColor;\n"
	"void main()\n"
	"{\n"
	// "    FragColor = vec4(0.7f, 0.5f, 0.2f, 1.0f);\n"
	"	FragColor = vertexColor;\n"
	"}\0";

const char *fragmentShaderSource3 = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"uniform vec4 ourColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = ourColor;\n"
	"}\0";

// const char *fragmentShaderSource_col = "#version 330 core\n"
// 	"out vec4 FragColor;\n"
// 	"in vec3 ourColor;\n"

// 	"void main()\n"
// 	"{\n"
// 		"FragColor = vec4(ourColor, 1.0);\n"
// 	"}\0";


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

float vertices_color[] = {// TODO
	// first triangle{}
     0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// left
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// right
     0.25f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,// top
};

int loop(unsigned int loc_shaderProgram, unsigned int loc_VAO)// TODO
{
	// [...]
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	int vertexColorLocation = glGetUniformLocation(loc_shaderProgram, "ourColor");

	// ..:: Drawing code (in render loop) :: ..
	// 4. draw the object
	glUseProgram(loc_shaderProgram);
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);// color change
	glBindVertexArray(loc_VAO);
	// seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// glBindVertexArray(0); // no need to unbind it every time

	return (0);
}

// int squre_loop(unsigned int loc_shaderProgram, unsigned int loc_VAO)
// {
// 	glUseProgram(loc_shaderProgram);
// 	glBindVertexArray(loc_VAO);
// 	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
// 	glBindVertexArray(0);

// 	return (0);
// }

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
    // vertex shader
	unsigned int vertexShader;// TODO compilation of shaders
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

    // check for shader compile errors
	int  success;// TODO error processing
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
	}

	// unsigned int vertexShader_col;// TODO compilation of shaders
	// vertexShader_col = glCreateShader(GL_VERTEX_SHADER);

	// glShaderSource(vertexShader_col, 1, &vertexShaderSource_col, NULL);
	// glCompileShader(vertexShader_col);

	// glGetShaderiv(vertexShader_col, GL_COMPILE_STATUS, &success);
	// if(!success)
	// {
	// 	glGetShaderInfoLog(vertexShader_col, 512, NULL, infoLog);
	// 	printf("ERROR::SHADER_COL::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
	// }

   // fragment shader
	unsigned int fragmentShader;// TODO compilation of shaders
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource3, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
	}

	// fragment shader
	unsigned int fragmentShader2;// TODO compilation of shaders
	fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);

	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
		printf("ERROR::SHADER2::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
	}

	// unsigned int fragmentShader_col;// TODO compilation of shaders
	// fragmentShader_col = glCreateShader(GL_FRAGMENT_SHADER);
	// glShaderSource(fragmentShader_col, 1, &fragmentShaderSource_col, NULL);
	// glCompileShader(fragmentShader_col);

	// glGetShaderiv(fragmentShader_col, GL_COMPILE_STATUS, &success);
	// if(!success)
	// {
	// 	glGetShaderInfoLog(fragmentShader_col, 512, NULL, infoLog);
	// 	printf("ERROR::SHADER_COL::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
	// }

    // link shaders
	unsigned int shaderProgram;//TODO create shader program object
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

    // check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) 
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
	}

	// glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);  

   // link shader2
	unsigned int shaderProgram2;//TODO create shader program object
	shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);

    // check for linking errors
	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
	if(!success) 
	{
		glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
		printf("ERROR::SHADER2::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader2);  

	unsigned int shaderProgram_col;//TODO create shader program object
	// shaderProgram_col = glCreateProgram();
	// glAttachShader(shaderProgram_col, vertexShader_col);
	// glAttachShader(shaderProgram_col, fragmentShader_col);
	// glLinkProgram(shaderProgram_col);

    // // check for linking errors
	// glGetProgramiv(shaderProgram_col, GL_LINK_STATUS, &success);
	// if(!success) 
	// {
	// 	glGetProgramInfoLog(shaderProgram_col, 512, NULL, infoLog);
	// 	printf("ERROR::SHADER_COL::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
	// }

	// glDeleteShader(vertexShader_col);
	// glDeleteShader(fragmentShader_col);


	shaderProgram_col = build_vertex_shader(
		"/home/utkinrn/Desktop/PROJ/ping_pong/src/shader.vs", 
		"/home/utkinrn/Desktop/PROJ/ping_pong/src/shader.fs"
		);


	// glUseProgram(shaderProgram);//TODO shaders ready

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	unsigned int VBO[2];// TODO create vertex buffer object
	glGenBuffers(2, VBO);
	// 0. copy our vertices array in a buffer for OpenGL to use
	// glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// // 1. then set the vertex attributes pointers
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// glEnableVertexAttribArray(0);  
	// 2. use our shader program when we want to render an object
	// glUseProgram(loc_shaderProgram);
	// 3. now draw the object 
	// someOpenGLFunctionThatDrawsOurTriangle();   






	unsigned int VAO[2];
	// unsigned int VAO_SQ;// TODO create vertex array object
	glGenVertexArrays(2, VAO);
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
	// glBindBuffer(GL_ARRAY_BUFFER, 0);

	// unsigned int EBO;
	// glGenBuffers(1, &EBO);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// ..:: Initialization code :: ..
	// 1. bind Vertex Array Object
	// glBindVertexArray(VAO_SQ);
	// // 2. copy our vertices array in a vertex buffer for OpenGL to use
	// glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_square), vertices_square, GL_STATIC_DRAW);
	// // 3. copy our index array in a element buffer for OpenGL to use
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// // 4. then set the vertex attributes pointers
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// glEnableVertexAttribArray(0);


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

		// draw our first triangle
		// glUseProgram(shaderProgram);
		// float timeValue = glfwGetTime();
		// float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		// int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		// glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
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
