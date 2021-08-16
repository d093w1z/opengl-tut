#section vertex
#version 130 

in vec2 position;

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
}

#section fragment
#version 130 

out vec4 outColor;

void main()
{
    outColor = vec4(1.0, 0.0, 0.0, 1.0);
}
