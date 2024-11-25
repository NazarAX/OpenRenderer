
#if defined(VERTEX)

layout(location = 0) in vec3 position; // Vertex position


uniform float uCol;

out float fragColor; // Color to pass to the fragment shader

void main() {
    fragColor = uCol;
    gl_Position = vec4(position, 1.0); // Set the vertex position
}

#endif

#if defined(FRAGMENT)

out vec4 color; // Output color
in float fragColor;

void main() {
    color = vec4(0.0, fragColor, 1.0, 1.0); // Use the passed color directly
}

#endif
