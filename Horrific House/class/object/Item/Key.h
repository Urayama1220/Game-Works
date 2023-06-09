#pragma once
#include "Item.h"

class OriginalShader;

class Key
	: public Item
{
public:
    Key(std::string name,Vector3 bPos, Vector3 aPos, Vector3 angle,Vector3 scale,ItemID keyid, int num);
    ~Key();

    //初期化
    void Init(void)override;

    //更新
    void Update(void)override;

    //描画
    void Draw(void)override;
    void Draw(bool cameraflag);
    //開放
    void Release(void)override;

    ItemID GetItemID(void)override { return itemId_; };
private:
    void Move(void);
    //シェーダ
    std::unique_ptr<OriginalShader> origShader_;
    ItemMove moveState_;
    ItemAnim animState_;
        //サインカーブのカウント
    float count_;
};

