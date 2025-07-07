#version 460 core
out vec4 FragColor;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_UseTexture;

uniform sampler2D u_Texture;

void main() {
    vec4 texColor = texture(u_Texture, v_TexCoord);
    FragColor = mix(v_Color, texColor, v_UseTexture); // 0 = color only, 1 = texture only
}
