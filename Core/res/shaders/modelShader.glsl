
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

    vFragPos = vec3(uModel * vec4(aPosition, 1.0f));

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

uniform int uNumLights;
uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform float uLightIntensity;




void main()
{
    // Calculate light direction (from light to fragment position)
    vec3 lightDir = normalize(uLightPos - vFragPos);

    // Calculate the diffuse strength (dot product between light direction and surface normal)
    float diffuseStrength = max(0.0, dot(lightDir, vNormal));

    // Compute the diffuse lighting contribution
    vec3 diffuse = diffuseStrength * uLightColor * uLightIntensity;

    // Sample the texture color
    vec4 texColor = texture(uTexture, vTexCoord);

    // Combine texture color with diffuse lighting
    FragColor = texColor;
}

#endif