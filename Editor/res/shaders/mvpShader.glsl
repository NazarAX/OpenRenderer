

// Vertex Shader
#if defined(VERTEX)

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = projection * view * model * vec4(aPosition, 1.0f);
    ourColor = aColor;
    TexCoord = aTexCoord;
}

#endif

// Fragment Shader
#if defined(FRAGMENT)

in vec3 ourColor;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
    FragColor = texture(u_Texture, TexCoord); // Sample the texture
    // or if you want to use the color:
    // FragColor = vec4(ourColor, 1.0f);
}
#endif
