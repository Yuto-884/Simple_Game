// カメラ制御クラス

#include "camera.h"
#include <cmath>

#include "input.h"

namespace {
    // 定数
    constexpr float eyeMoveSpeed_ = 0.06f;  // カメラ移動速度
    constexpr float destTargetToView_ = -5.0f;  // 注視点からカメラまでの距離

    //---------------------------------------------------------------------------------
    /**
     * @brief	コンスタントバッファ用データ構造体
     */
    struct ConstBufferData {
        DirectX::XMMATRIX view_{};        /// ビュー行列
        DirectX::XMMATRIX projection_{};  /// 射影行列
    };

}  // namespace

namespace game {
    //---------------------------------------------------------------------------------
    /**
     * @brief    カメラを初期化する
     */
    void Camera::initialize() noexcept {

        createDrawBuffer();

        // カメラの位置を設定
        position_ = DirectX::XMFLOAT3(0.0f, 1.5f, destTargetToView_);
        // カメラの注視点を設定
        target_ = DirectX::XMFLOAT3(0.0f, 0.0f, 10.0f);
        // カメラの上方向を設定
        up_ = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);

        // プロジェクション行列の設定
        projection_ = DirectX::XMMatrixPerspectiveFovLH(
            DirectX::XM_PIDIV4,  // 視野角45度
            1280.0f / 720.0f,    // アスペクト比
            0.1f,                // ニアクリップ
            100.0f               // ファークリップ
        );
    }

    //---------------------------------------------------------------------------------
    /**
     * @brief    カメラを更新する
     */
    void Camera::update() noexcept {
        // ビュー行列の計算
        view_ = DirectX::XMMatrixLookAtLH(
            DirectX::XMLoadFloat3(&position_),
            DirectX::XMLoadFloat3(&target_),
            DirectX::XMLoadFloat3(&up_));
    }

    //---------------------------------------------------------------------------------
    /**
     * @brief	描画用バッファの作成
     */
    void Camera::createDrawBuffer() noexcept {
        if (!constantBuffer_.create(sizeof(ConstBufferData))) {
            assert(false && "カメラ用コンスタントバッファの作成に失敗しました");
        }
    }

    //---------------------------------------------------------------------------------
    /**
     * @brief	描画用バッファの更新
     */
    void Camera::updateDrawBuffer() noexcept {
        Object::updateConstantBuffer(ConstBufferData{ DirectX::XMMatrixTranspose(view_), DirectX::XMMatrixTranspose(projection_) });
    }

    //---------------------------------------------------------------------------------
    /**
     * @brief   カメラのビュー行列を取得する
     * @return	ビュー行列
     */
    [[nodiscard]] DirectX::XMMATRIX XM_CALLCONV Camera::viewMatrix() const noexcept {
        return view_;
    }

    //---------------------------------------------------------------------------------
    /**
     * @brief   プロジェクション行列を取得する
     * @return	プロジェクション行列
     */
    [[nodiscard]] DirectX::XMMATRIX XM_CALLCONV Camera::projection() const noexcept {
        return projection_;
    }
}  // namespace game