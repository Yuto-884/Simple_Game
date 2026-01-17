// 弾制御クラス

#pragma once

#include "game_object.h"

namespace game {

    //---------------------------------------------------------------------------------
    /**
     * @brief	弾制御
     */
    class Bullet : public GameObject {
    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief    コンストラクタ
         */
        Bullet() = default;
        // コンストラクタ継承
        using GameObject::GameObject;


        //---------------------------------------------------------------------------------
        /**
         * @brief    デストラクタ
         */
        virtual ~Bullet() = default;

    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief	オブジェクトの初期化
         */
        virtual void initialize() noexcept override;

        //---------------------------------------------------------------------------------
        /**
         * @brief	オブジェクトの更新
         */
        virtual void update() noexcept override;

    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief	ヒットした時の処理
         */
        virtual void onHit() noexcept override;

        //---------------------------------------------------------------------------------
        /**
         * @brief	ヒットする対象
         */
        [[nodiscard]] virtual UINT64 hitTargetTypeId() noexcept override;
    };
}  // namespace game
