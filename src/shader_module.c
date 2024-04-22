#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include"shader_module.h"

unsigned int shader_file_compile(unsigned int type, const char *Path)
{
    int fd = 0;
    int len = 0;
    char *shader_code = NULL;
    char buf[1000] = {0};
    unsigned int shader;
    int  success;// error processing
	char infoLog[512];

    fd = open(Path, O_RDONLY);
    if(fd)
    {
        len = read(fd, buf, sizeof(buf));
        // printf("len = %d\n", len);
    }
    close(fd);

    // printf("shader_code = %s\n", buf);


	shader = glCreateShader(type);

    shader_code = buf;
	glShaderSource(shader, 1, &shader_code, NULL);
	glCompileShader(shader);

    // check for shader compile errors
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("ERROR::SHADER::COMPILATION_FAILED\n%s\n%s\n", infoLog, Path);
	}

    return(shader);
}

unsigned int build_shader(const char *vertexPath, const char *fragmentPath)
{
    unsigned int vertexShader;
    unsigned int fragmentShader;// compilation of shaders
    unsigned int shaderProgram;// create shader program object
    int  success;// error processing
	char infoLog[512];

    vertexShader = shader_file_compile(GL_VERTEX_SHADER, vertexPath);
    fragmentShader = shader_file_compile(GL_FRAGMENT_SHADER, fragmentPath);

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

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

    return(shaderProgram);
}

// void use(void)
// {
//     glUseProgram(ID);
// }
