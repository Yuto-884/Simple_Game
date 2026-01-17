// カメラ制御クラス

#pragma once

#include "object.h"
#include <DirectXMath.h>

namespace game {

    //---------------------------------------------------------------------------------
    /**
     * @brief	カメラ制御クラス
     */
    class Camera final : public Object {
    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief    コンストラクタ
         */
        Camera() = default;

        //---------------------------------------------------------------------------------
        /**
         * @brief    デストラクタ
         */
        virtual ~Camera() = default;

    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief    カメラを初期化する
         */
        virtual void initialize() noexcept override;

        //---------------------------------------------------------------------------------
        /**
         * @brief    カメラを更新する
         */
        virtual void update() noexcept override;

    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief	描画用バッファの作成
         */
        virtual void createDrawBuffer() noexcept override;

        //---------------------------------------------------------------------------------
        /**
         * @brief	描画用バッファの更新
         */
        virtual void updateDrawBuffer() noexcept override;

    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief   カメラのビュー行列を取得する
         * @return	ビュー行列
         */
        [[nodiscard]] DirectX::XMMATRIX XM_CALLCONV viewMatrix() const noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief   プロジェクション行列を取得する
         * @return	プロジェクション行列
         */
        [[nodiscard]] DirectX::XMMATRIX XM_CALLCONV projection() const noexcept;

    private:
        DirectX::XMMATRIX view_{};        /// ビュー行列
        DirectX::XMMATRIX projection_{};  /// 射影行列

        // カメラのパラメータ
        DirectX::XMFLOAT3 position_{};  /// カメラの位置
        DirectX::XMFLOAT3 target_{};    /// カメラの注視点
        DirectX::XMFLOAT3 up_{};        /// カメラの上方向
    };
}  // namespace game

