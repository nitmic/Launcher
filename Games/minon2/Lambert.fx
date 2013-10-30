//===================================================================
//							global
//===================================================================
//���[���h�A�r���[�A�ˉe���W�ϊ��}�g���b�N�X
float4x4 g_WVP;
//�Ɩ��̕����x�N�g��
float4   g_LightDir;
//�����ɑ΂���}�e���A���B0.0f�`1.0f�̒l�������A1.0f�̂Ƃ��ł������Ȃ�B
float4   g_Ambient = (float4)1.0f;
//�I�u�W�F�N�g�̃e�N�X�`���[�B�O�������IDirect3DDevice9::SetTexture�֐��Őݒ肷��B
sampler s0 : register(s0);

struct VS_INPUT_MESH
{
	float4 pos : POSITION;
	float4 normal : NORMAL;
	float2 tex : TEXCOORD0;
};

struct VS_OUTPUT 
{
	float4 pos   : POSITION;
	float2 tex   : TEXCOORD0;
	float3 normal: TEXCOORD1;
};

//=======================================================================
//					vertex shader
//=======================================================================


VS_OUTPUT VS(VS_INPUT_MESH i)
{
	VS_OUTPUT O = (VS_OUTPUT)0;
	
	O.pos = mul(i.pos, g_WVP);
	O.tex = i.tex.xy;
	O.normal = normalize(i.normal.xyz);
	return O;
}

//=========================================================================
//					pixel shader
//=========================================================================

float4 PSLambert(VS_OUTPUT i) : COLOR0
{
	float4 Out = (float4)0;
	float p = dot(i.normal, -g_LightDir.xyz);
	Out = p * tex2D( s0, i.tex );
	return Out;
};
float4 PSHalfLambert(VS_OUTPUT i) : COLOR0
{
	float4 Out = (float4)0;

	float p = dot(i.normal, -g_LightDir.xyz);
	p = p * 0.5f + 0.7f;
	p = p * p;
	Out = p * tex2D( s0, i.tex );
	return Out;
};
//===========================================================================
//						technique
//===========================================================================
Technique LambertMesh
{
	Pass P0//�����o�[�g
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PSLambert();
	}
	Pass P1//�n�[�t�����o�[�g
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PSHalfLambert();
	}
};
