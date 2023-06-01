#pragma once
#include "BaseScene.h"
#include "../tmx/TmxObj.h"

class Controller;
class ResultUI;
class Camera;
class ResultCBuffer;
class OriginalShader;
enum class ControllerType;

class ResultScene :
    public BaseScene
{
public:
    ResultScene(ControllerType type);
    ~ResultScene();

    // ������
    void Init(void) override;

    // �X�V
    UniqueScene Update(UniqueScene scene) override;

    // �`��
    void DrawScreen(void) override;

    //�j��
    void Release(void) override;

    //�V�[����ID��Ԃ�
    SceneID GetSceneID(void) override { return SceneID::Result; };
private:

    //�L���[�u�}�b�v�̐���
    void CreateCubeMap(void);
    //�V�[���؂�ւ��֐�
    UniqueScene UpdateScene(UniqueScene& scene);


   //�R���g���[�����
    std::unique_ptr<Controller> controller_;
    //�R���g���[���^�C�v
    ControllerType contorollerType_;

    //tmx
    //TmxObj tmxObj_;

    //�J�������
    std::unique_ptr<Camera> camera_;

    //�V�F�[�_
    std::unique_ptr<OriginalShader> origShader_;

    //UI
    std::unique_ptr<ResultUI> resultUI_;

    std::unique_ptr<ResultCBuffer> cBuffer_;

    float stepCount_;

    int cubeTexture_;

    float skyRotate_;
};
