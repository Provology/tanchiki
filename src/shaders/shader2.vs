#version 330 core
    layout (location = 0) in vec3 aPos;
	out vec4 vertexColor;
	uniform float offset;
    void main()
    {
        gl_Position = vec4(aPos.x + offset, -aPos.y, aPos.z, 1.0);
        vertexColor = gl_Position;
    }