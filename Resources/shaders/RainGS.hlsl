#include "Rain.hlsli"

// �l�p�`�̒��_��
static const uint vnum = 2;

// �Z���^�[����̃I�t�Z�b�g
static const float4 offset_array[vnum] =
{
	float4(-0.5f,-0.5f,0,0), // ����
	float4(-0.5f,+0.5f,0,0), // ����
};

// �_�̓��͂���l�p�`���o��
[maxvertexcount(vnum)]
void main(
	point VSOutput input[1] : SV_POSITION,
	inout LineStream< GSOutput > output
)
{
	GSOutput element;
	for (uint i = 0; i < vnum; i++)
	{
		// �r���{�[�h��]
		float4 offset = offset_array[i];
		offset = mul(matBillboard, offset);
		element.svpos = input[0].pos + offset;
		element.svpos = mul(mat, element.svpos);
		output.Append(element);
	}
}