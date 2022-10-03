#include "BasicShaderHeader.hlsli"

[maxvertexcount(6)]
void main(
	triangle VSOutput input[3] : SV_POSITION,
	inout TriangleStream< GSOutput > output
)
{
	GSOutput element;
	for (uint i = 0; i < 3; i++)
	{
		element.svpos = input[i].svpos;
		element.normal = input[i].normal;
		element.uv = input[i].uv;
		output.Append(element);
	}

	output.RestartStrip();

	for (uint i = 0; i < 3; i++)
	{
		element.svpos = input[i].svpos + float4(20.0f, 0, 0, 0);
		element.normal = input[i].normal;
		element.uv = input[i].uv * 5.0f;
		output.Append(element);
	}
}