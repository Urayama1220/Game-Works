#pragma once
#include "BaseScene.h"
#define lpSceneMng SceneMng::GetInstance()
#include "../Input/imput_Scene/Imput.h"
using UniqueInput = std::shared_ptr<Imput>;
class SceneMng
{
public:
	//静的シングルトン
	static SceneMng& GetInstance()
	{
		static SceneMng s_Instance;
		return s_Instance;
	};
	//動的シングルトン
	//static void Create(void)
	//{
	//	if (!s_Instance)//nullだったら入る
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
	//動的シングルトン
	/*static SceneMng* s_Instance;*/	//ユニークポインターにするとDestroyを忘れても消してくれる　
	//任意のデリーたを別途呼べるようにする必要がある

	bool SysInit();
	void Update(void);
	void Draw(void);
	bool initFlag_ = 0 ;
	SceneMng();
	~SceneMng();
	uniqueScene scene_;
	UniqueInput imput_;


};


