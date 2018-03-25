#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 light_pos = vec2(100.0,0.0);

in DATA
{
 vec4 position;
 vec2 uv;
 float tid;
 vec4 colour;
}fs_in;

uniform sampler2D textures[32];

void main()
{
float intensity = 1/length(fs_in.position.xy-light_pos);
vec4 texColor = fs_in.colour;

if(fs_in.tid > 0.0)
{
int tid = int(fs_in.tid - 0.5);
texColor = texture(textures[tid], fs_in.uv);

}


color = texColor;

if(light_pos.x != 100.0)
{
color = texColor * intensity;
}



}