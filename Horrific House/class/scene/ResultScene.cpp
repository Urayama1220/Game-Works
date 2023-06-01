#include<DxLib.h>
#include "ResultScene.h"
#include "../common/manager/ImageMng.h"
#include "../common/manager/ModelMng.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include"SceneExpansion/buffer/ResultCBuffer.h"
#include "../input/PadInput.h"
#include "../input/KeyInput.h"
#include "../tmx/TmxObj.h"
#include "SceneExpansion/UI/ResultUI.h"
#include"../camera/Camera.h"
#include"../common/OriginalShader.h"
#include "../../_debug/_DebugConOut.h"

//�����ʒu
constexpr VECTOR CAMERA_INIT_POS = { 0, 400, -400 };                    //�J����
constexpr VECTOR CLIFF_INIT_POS = { -470.0f, -440.0f, -2270.0f };       //�R
constexpr VECTOR WATER_INIT_POS = { 0, 200, 0 };                        //��
constexpr VECTOR TAREGET_INIT_POS = { 0, 400, 400 };                    //�����_
constexpr VECTOR GRASS_INIT_POS = { 8, 175, 0 };                        //��
constexpr float ADD_ROTATE = 0.0001f;                                   //��]���Z�l

//�L���[�u�e�N�X�`��
constexpr int CUBE_TEXTURE_NUM = 6; //��
constexpr int CUBE_SIZE = 512;      //�e�N�X�`���T�C�Y

ResultScene::ResultScene(ControllerType type)
{
    contorollerType_ = type;
    Init();
    DrawScreen();
}

ResultScene::~ResultScene()
{
    Release();
}

void ResultScene::Init(void)
{
    MV1SetScale(lpModelMng.GetID("./resource/model/stage/dome/Skydome.mv1")[0], VGet(50, 50, 50));
    MV1SetPosition(lpModelMng.GetID("./resource/model/stage/water100.mv1")[0], WATER_INIT_POS);
    MV1SetPosition(lpModelMng.GetID("./resource/model/stage/cliff.mv1")[0], CLIFF_INIT_POS);
    if (contorollerType_ == ControllerType::Pad)
    {
        controller_ = std::make_unique<PadInput>();
    }
    else
    {
        controller_ = std::make_unique<KeyInput>();
    }
    resultUI_ = std::make_unique<ResultUI>();
    camera_ = std::make_unique<Camera>(Vector3(0.0f, Deg2RadF(180.0f), 0.0f));	//�J����
    cBuffer_ = std::make_unique<ResultCBuffer>();
    stepCount_ = 0.0f;
    skyRotate_ = 0.0f;

    SetCubeMapTextureCreateFlag(true);
    cubeTexture_ = MakeScreen(CUBE_SIZE, CUBE_SIZE, true);
    SetCubeMapTextureCreateFlag(false);

    CreateCubeMap();
    MV1SetPosition(lpModelMng.GetID("./resource/model/stage/grass.mv1")[0], GRASS_INIT_POS);

    int vs = LoadVertexShader("./resource/shader/vs/Sea_vs.vso");
    int ps = LoadPixelShader("./resource/shader/ps/Sea_ps.pso");
    origShader_ = std::make_unique<OriginalShader>(vs, ps);
}

UniqueScene ResultScene::Update(UniqueScene scene)
{
    controller_->Update();
    resultUI_->Update();
    cBuffer_->Update(stepCount_, Vector3(0.0f, 0.0f, 0.0f));

    //�J����
    DrawScreen();
    MV1SetRotationXYZ(lpModelMng.GetID("./resource/model/stage/dome/Skydome.mv1")[0], VGet(Deg2RadF(180.0f), skyRotate_, 0.0f));
    stepCount_ += lpSceneMng.GetDeltaTime();
    skyRotate_ += ADD_ROTATE;
    return UpdateScene(scene);
}

void ResultScene::DrawScreen(void)
{
    CreateCubeMap();
    SetDrawScreen(screenID_);
    ClsDrawScreen();

    //�J��������(�I�u�W�F�N�g�`��O�ɏ���)
    SetCameraPositionAndTarget_UpVecY(CAMERA_INIT_POS, TAREGET_INIT_POS);

    MV1DrawModel(lpModelMng.GetID("./resource/model/stage/dome/Skydome.mv1")[0]);
    MV1DrawModel(lpModelMng.GetID("./resource/model/stage/cliff.mv1")[0]);


    float scale = 0.4f;
    MV1SetPosition(lpModelMng.GetID("./resource/model/stage/grass.mv1")[0], GRASS_INIT_POS);
    MV1SetScale(lpModelMng.GetID("./resource/model/stage/grass.mv1")[0],VGet(scale, scale, scale));
    MV1DrawModel(lpModelMng.GetID("./resource/model/stage/grass.mv1")[0]);

    origShader_->Draw(lpModelMng.GetID("./resource/model/stage/water100.mv1")[0], cubeTexture_);

    resultUI_->Draw();

#ifdef _DEBUG
    //DrawFormatString(0, 0, 0xffffff, "x:%f\n,y:%f\n,z:%f\n", pos.x, pos.y, pos.z);
#endif	//_DEBUG
}

void ResultScene::Release(void)
{
    DeleteGraph(cubeTexture_);
}

void ResultScene::CreateCubeMap(void)
{
    //����`�悷��ۂɎg�p����J�����̒����_�Ə����
    //�����_
    VECTOR targetPos[CUBE_TEXTURE_NUM] = {};
    targetPos[0] = VGet(1.0f, 0.0f, 0.0f);
    targetPos[1] = VGet(-1.0f, 0.0f, 0.0f);
    targetPos[2] = VGet(0.0f, 1.0f, 0.0f);
    targetPos[3] = VGet(0.0f, -1.0f, 0.0f);
    targetPos[4] = VGet(0.0f, 0.0f, 1.0f);
    targetPos[5] = VGet(0.0f, 0.0f, -1.0f);

    //�����
    VECTOR upVec[CUBE_TEXTURE_NUM] = {};
    upVec[0] = VGet(0.0f, 1.0f, 0.0f);
    upVec[1] = VGet(0.0f, 1.0f, 0.0f);
    upVec[2] = VGet(0.0f, 0.0f, -1.0f);
    upVec[3] = VGet(0.0f, 0.0f, 1.0f);
    upVec[4] = VGet(0.0f, 1.0f, 0.0f);
    upVec[5] = VGet(0.0f, 1.0f, 0.0f);

    //����`�悷��ʂ̐������J��Ԃ�
    for (int i = 0; i < CUBE_TEXTURE_NUM; i++)
    {
        //SetDrawScreen�Ɠ���
        SetRenderTargetToShader(0, cubeTexture_, i);
        ClearDrawScreen();

        //�J�����̉�p��90�x
        SetupCamera_Perspective(Deg2RadF(90.0f));

        //�͈�
        SetCameraNearFar(1.0f, 10000.0f);

        //�J�����̐ݒ�
        SetCameraPositionAndTargetAndUpVec(VGet(0.0f, 0.0f, 0.0f), targetPos[i], upVec[i]);

        MV1SetScale(lpModelMng.GetID("./resource/model/stage/dome/Skydome.mv1")[0], VGet(30.0f, 30.0f, 30.0f));
        MV1SetRotationXYZ(lpModelMng.GetID("./resource/model/stage/dome/Skydome.mv1")[0], VGet(Deg2RadF(180.0f), skyRotate_, 0.0f));
        MV1DrawModel(lpModelMng.GetID("./resource/model/stage/dome/Skydome.mv1")[0]);
    }

    //60�x�ɖ߂�
    SetupCamera_Perspective(Deg2RadF(60.0f));
}

UniqueScene ResultScene::UpdateScene(UniqueScene& scene)
{
    switch (resultUI_->GetHitUICol())
    {
    case ResultColUI::reTitle:
        return std::make_unique<TitleScene>();
        break;
    default:
        break;
    }
    //�����Ȃ���Ό��̃V�[����Ԃ�
    return  std::move(scene);
}