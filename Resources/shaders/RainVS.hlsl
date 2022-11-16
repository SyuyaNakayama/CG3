#include "Rain.hlsli"

VSOutput main(float4 pos : POSITION, float scale : TEXCOORD, float4 color : COLOR)
{
	VSOutput output; // ピクセルシェーダーに渡す値
	output.pos = pos;
	return output;
}