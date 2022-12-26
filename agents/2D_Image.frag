#version 450

layout (location = 0) smooth in vec2 I_TextureUV;	// Interpolated TextureUV as per PIXEL (a.k.a Fragment) .... (Barycentric Interpolation)
layout (location = 0) out vec4 outFragColor;

layout(set = 0, binding = 0) uniform sampler2D U_Image;

void main()
{
    //outFragColor = vec4(texture(U_Image, I_TextureUV).xyz, 1.0f);
    outFragColor = vec4(I_TextureUV, 1.0f, 1.0f); // 😜
}