#pragma once
#include "BaseScene.h"
#define lpSceneMng SceneMng::GetInstance()
#include "../Input/imput_Scene/Imput.h"
using UniqueInput = std::shared_ptr<Imput>;
class SceneMng
{
public:
	//�ÓI�V���O���g��
	static SceneMng& GetInstance()
	{
		static SceneMng s_Instance;
		return s_Instance;
	};
	//���I�V���O���g��
	//static void Create(void)
	//{
	//	if (!s_Instance)//null�����������
	//	{
	//		s_Instance = new SceneMng();
	//	}
	//};
	//static void Destroy(void)
	//{
	//		delete s_Instance;
	//		s_Instance = nullptr;
	//}
	void Run(void);
	
	
private:
	//���I�V���O���g��
	/*static SceneMng* s_Instance;*/	//���j�[�N�|�C���^�[�ɂ����Destroy��Y��Ă������Ă����@
	//�C�ӂ̃f���[����ʓr�Ăׂ�悤�ɂ���K�v������

	bool SysInit();
	void Update(void);
	void Draw(void);
	bool initFlag_ = 0 ;
	SceneMng();
	~SceneMng();
	uniqueScene scene_;
	UniqueInput imput_;


};


