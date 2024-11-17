
#if defined(VERTEX)

layout(location = 0) in vec2 position; // Vertex position

out vec4 fragColor; // Color to pass to the fragment shader

void main() {
    gl_Position = vec4(position, 0.0, 1.0); // Set the vertex position
}

#endif

#if defined(FRAGMENT)

out vec4 color; // Output color

void main() {
    color = vec4(1.0, 0.5, 0.0, 1.0); // Use the passed color directly
}

#endif
