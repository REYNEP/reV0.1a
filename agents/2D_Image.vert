#version 450

/**
 * [OUT]    gl_Position: window top-left [-1, -1], bottom-right [1,1]          (That last part, 0.0f, 1.0f... is really really important)
 *  [IN] gl_VertexIndex: STRIP: doesn't take any effect.... you get   3,4,5 for 2nd tri, 6,7,8 for 3rd TRI
 *
 * [OUT]    I_TextureUV: at this point, in this .vert shader.... think of this variable as.... we are ASSIGNing a particular Attribute to a vertex
 *                       Just like in Blender.... yk, those attributes 😄
 *                       and inside the .frag shader its asked to be SMOOTH-ly interpolated as per pixel....
 */

/**
      0----------3
      |          |
      |          |
      |          |
      1----------2
 */

const vec2 positions[6] = vec2[6](
    vec2(-0.5f,-0.5f),  // 0
    vec2(-0.5f, 0.5f),  // 1
    vec2( 0.5f, 0.5f),  // 2

    vec2( 0.5f, 0.5f),  // 2
    vec2( 0.5f,-0.5f),  // 3
    vec2(-0.5f,-0.5f)   // 0
);

const vec2 uv[6] = vec2[6](
    vec2( 0.0f, 0.0f),  // 0
    vec2( 0.0f, 1.0f),  // 1
    vec2( 1.0f, 1.0f),  // 2

    vec2( 1.0f, 1.0f),  // 2
    vec2( 1.0f, 0.0f),  // 3
    vec2( 0.0f, 0.0f)   // 0
);

layout (location = 0) smooth out vec2 Interpolated_UV;

void main() {
    gl_Position = vec4(positions[gl_VertexIndex], 0.0f, 1.0f);
    Interpolated_UV = uv[gl_VertexIndex];
}