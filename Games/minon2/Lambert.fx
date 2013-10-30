//===================================================================
//							global
//===================================================================
//ワールド、ビュー、射影座標変換マトリックス
float4x4 g_WVP;
//照明の方向ベクトル
float4   g_LightDir;
//環境光に対するマテリアル。0.0f～1.0fの値を持ち、1.0fのとき最も強くなる。
float4   g_Ambient = (float4)1.0f;
//オブジェクトのテクスチャー。外部からはIDirect3DDevice9::SetTexture関数で設定する。
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
	Pass P0//ランバート
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PSLambert();
	}
	Pass P1//ハーフランバート
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PSHalfLambert();
	}
};
