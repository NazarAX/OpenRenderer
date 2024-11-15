
#if defined(VERTEX)

layout(location = 0) in vec2 position; // Vertex position
layout(location = 1) in vec2 inTexCoord; // Texture coordinate

out vec2 texCoord;

void main() 
{
    gl_Position = vec4(position, 0.0, 1.0); // Set the vertex position
    texCoord = inTexCoord;
}

#endif

#if defined(FRAGMENT)

out vec4 color; // Output color
in vec2 texCoord;

uniform sampler2D inTexture;

void main() {
    color = texture(inTexture, texCoord);
}

#endif
