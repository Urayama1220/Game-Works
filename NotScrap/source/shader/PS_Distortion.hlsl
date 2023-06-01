struct PS_INPUT
{
	float4 diffuse : COLOR0;
	float4 specular : COLOR1;
	float2 uv : TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 color : SV_TARGET0;
};

SamplerState sam;
Texture2D screen : register(t0);
Texture2D noise : register(t1);

cbuffer ConstantBuffer : register(b5)
{
	float angle;
}

PS_OUTPUT main(PS_INPUT input)
{
	PS_OUTPUT output;
	//ノイズをサンプリング。uvを回転させて歪みを移動させる
	float4 p = noise.Sample(sam,float2(input.uv.x + cos(angle) * 0.05f,input.uv.y + sin(angle) * 0.05f));

	//-1~1にする
	p.xy = (p.xy * 2.0 - 1.0f) * 0.05f;

	//背景をサンプリングして加算
	output.color = screen.Sample(sam, input.uv + p.xy);

	return output;
}