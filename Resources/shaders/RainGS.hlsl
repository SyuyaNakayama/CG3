#include "Rain.hlsli"

// 四角形の頂点数
static const uint vnum = 2;

// センターからのオフセット
static const float4 offset_array[vnum] =
{
	float4(-0.5f,-0.5f,0,0), // 左下
	float4(-0.5f,+0.5f,0,0), // 左上
};

// 点の入力から四角形を出力
[maxvertexcount(vnum)]
void main(
	point VSOutput input[1] : SV_POSITION,
	inout LineStream< GSOutput > output
)
{
	GSOutput element;
	for (uint i = 0; i < vnum; i++)
	{
		// ビルボード回転
		float4 offset = offset_array[i];
		offset = mul(matBillboard, offset);
		element.svpos = input[0].pos + offset;
		element.svpos = mul(mat, element.svpos);
		output.Append(element);
	}
}