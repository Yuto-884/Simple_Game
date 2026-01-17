// ルートシグネチャクラス

#pragma once

#include "device.h"

//---------------------------------------------------------------------------------
/**
 * @brief	ルートシグネチャクラス
 */
class RootSignature final {
public:
    //---------------------------------------------------------------------------------
    /**
     * @brief    コンストラクタ
     */
    RootSignature() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief    デストラクタ
     */
    ~RootSignature() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief	ルートシグネチャを作成する
     * @return	成功すれば true
     */
    [[nodiscard]] bool create() noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	ルートシグネチャを取得する
     * @return　ルートシグネチャ
     */
    [[nodiscard]] ID3D12RootSignature* get() const noexcept;

private:
    Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_{};  /// ルートシグネチャ
};
