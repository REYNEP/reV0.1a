#version 450

const vec2 positions[6] = vec2[6](
    vec2( 0.5f, 0.5f),  // 0
    vec2(-0.5f, 0.5f),  // 1
    vec2( 0.5f,-0.5f),  // 2

    vec2(-0.5f,-0.5f),  // 3
    vec2(-0.5f, 0.5f),  // 2
    vec2( 0.5f,-0.5f)   // 1
);

void main()
{
    //int x = gl_VertexIndex / 3;
    //gl_Position = vec4(positions[gl_VertexIndex - (x * 3) + x], 0.0f, 1.0f);

    gl_Position = vec4(positions[gl_VertexIndex], 0.0f, 1.0f);
}