// ���_�V�F�[�_�[�̓���
struct VS_INPUT
{
	float3 Position        : POSITION;			// ���W( ���[�J����� )
	float3 Normal          : NORMAL;			// �@��( ���[�J����� )
	float4 Diffuse         : COLOR0;			// �f�B�t���[�Y�J���[
	float4 Specular        : COLOR1;			// �X�y�L�����J���[
	float4 TexCoords0      : TEXCOORD0;		// �e�N�X�`�����W
	float4 TexCoords1      : TEXCOORD1;		// �T�u�e�N�X�`�����W
};

// ���_�V�F�[�_�[�̏o��
struct VS_OUTPUT
{
	float4 Diffuse         : COLOR0;		// �f�B�t���[�Y�J���[
	float4 Specular        : COLOR1;		// �X�y�L�����J���[
	float2 TexCoords0      : TEXCOORD0;	// �e�N�X�`�����W
	float4 Position        : SV_POSITION;	// ���W( �v���W�F�N�V������� )
};


// ��{�p�����[�^
struct DX_D3D11_VS_CONST_BUFFER_BASE
{
	float4x4		AntiViewportMatrix;				// �A���`�r���[�|�[�g�s��
	float4x4		ProjectionMatrix;					// �r���[�@���@�v���W�F�N�V�����s��
	float4x3		ViewMatrix;						// ���[���h�@���@�r���[�s��
	float4x3		LocalWorldMatrix;					// ���[�J���@���@���[���h�s��

	float4		ToonOutLineSize;						// �g�D�[���̗֊s���̑傫��
	float		DiffuseSource;							// �f�B�t���[�Y�J���[( 0.0f:�}�e���A��  1.0f:���_ )
	float		SpecularSource;						// �X�y�L�����J���[(   0.0f:�}�e���A��  1.0f:���_ )
	float		MulSpecularColor;						// �X�y�L�����J���[�l�ɏ�Z����l( �X�y�L�������������Ŏg�p )
	float		Padding;
};

// ���̑��̍s��
struct DX_D3D11_VS_CONST_BUFFER_OTHERMATRIX
{
	float4		ShadowMapLightViewProjectionMatrix[3][4];			// �V���h�E�}�b�v�p�̃��C�g�r���[�s��ƃ��C�g�ˉe�s�����Z��������
	float4		TextureMatrix[3][2];								// �e�N�X�`�����W����p�s��
};

// ��{�p�����[�^
cbuffer cbD3D11_CONST_BUFFER_VS_BASE				: register(b1)
{
	DX_D3D11_VS_CONST_BUFFER_BASE				g_Base;
};

// ���̑��̍s��
cbuffer cbD3D11_CONST_BUFFER_VS_OTHERMATRIX			: register(b2)
{
	DX_D3D11_VS_CONST_BUFFER_OTHERMATRIX		g_OtherMatrix;
};



// main�֐�
VS_OUTPUT main(VS_INPUT VSInput)
{
	float3 light = normalize(float3(1, 1, 1));
	VS_OUTPUT VSOutput;
	float4 lLocalPosition;
	float4 lWorldPosition;
	float4 lViewPosition;


	// ���_���W�ϊ� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )

	// ���[�J�����W�̃Z�b�g
	lLocalPosition.xyz = VSInput.Position + VSInput.Normal;
	lLocalPosition.w = 1.0f;

	// ���W�v�Z( ���[�J�����r���[���v���W�F�N�V���� )
	lWorldPosition = float4(mul(lLocalPosition, g_Base.LocalWorldMatrix), 1.0f);

	lViewPosition = float4(mul(lWorldPosition, g_Base.ViewMatrix), 1.0f);

	VSOutput.Position = mul(lViewPosition, g_Base.ProjectionMatrix);

	// ���_���W�ϊ� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )



	// �o�̓p�����[�^�Z�b�g ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )

	// �e�N�X�`�����W�ϊ��s��ɂ��ϊ����s�������ʂ̃e�N�X�`�����W���Z�b�g
	VSOutput.TexCoords0 = VSInput.TexCoords0;

	// �o�̓p�����[�^�Z�b�g ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )
	VSOutput.Diffuse = float4(1, 0.5, 0, 1);//VSInput.Diffuse*(max(saturate(dot(VSInput.Normal,light)),0.3));
	VSOutput.Specular = VSInput.Specular;

	// �o�̓p�����[�^��Ԃ�
	return VSOutput;
}