#pragma once
#include <memory>
#include "../common/Vector2.h"
#include "../Input/imput_Scene/Imput.h"
#include <list>
#include "../Choice.h"
using UniqueInput = std::shared_ptr<Imput>;
class BaseScene;
using uniqueScene = std::shared_ptr<BaseScene>;
using Stagelist = std::list<Stage>;
static constexpr int ChipSize = 48;
static constexpr int VolumeSE = 100;
enum class Scene
{
	Title,
	Game,
	Result,
	Select,
	Setup,
	HalfwayScene,
	Transition,
	GoResultScene,
	MAX
};

class BaseScene
{
public:
	BaseScene();
	virtual~BaseScene();
	virtual uniqueScene Update(uniqueScene ownScene) = 0;
	virtual void Draw();
	virtual bool Init(void) = 0 ;
	virtual void DrawOwnScreen() = 0;
	//���Ɖ��̉��͂���Ă邱�Ƃ͓���
	virtual Scene GetSceneID(void) = 0;//�V�[���̎擾�A�ݒ�
	double Offset_;	//�I�t�Z�b�g
private:
protected:
	int screenID_;		//�`��p
	Vector2 screenSize_;	//��ʃT�C�Y�擾�p�ϐ�
	
	UniqueInput imput_;
	Stagelist ClearStagelist_;
};

