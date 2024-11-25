
#if defined(VERTEX)

layout(location = 0) in vec3 aPosition;   // Vertex position
layout(location = 3) in vec3 aNormal;     // Vertex normal
layout(location = 2) in vec2 aTexCoord;  // Texture coordinates

out vec3 vNormal;       // Pass normal to fragment shader
out vec2 vTexCoord;     // Pass texture coordinates to fragment shader
out vec3 vFragPos;      // Pass fragment position for lighting

uniform mat4 uModel;     // Model transformation matrix
uniform mat4 uView;      // View matrix
uniform mat4 uProjection; // Projection matrix

void main() {
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);

    vFragPos = vec3(uModel * vec4(aPosition, 1.0));

    // Pass the transformed normal
    vNormal = mat3(transpose(inverse(uModel))) * aNormal;

    // Pass texture coordinates as-is
    vTexCoord = aTexCoord;
}

#endif
#if defined(FRAGMENT)

uniform float uCol;


in vec3 vNormal;       // Interpolated normal
in vec2 vTexCoord;     // Interpolated texture coordinates
in vec3 vFragPos;      // Fragment position in world space

out vec4 FragColor;    // Output color

uniform sampler2D uTexture;    // Texture sampler

void main() {
    FragColor = texture2D(uTexture, vTexCoord);
}

#endif