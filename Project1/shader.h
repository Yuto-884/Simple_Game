// シェーダクラス

#pragma once

#include "device.h"

//---------------------------------------------------------------------------------
/**
 * @brief	シェーダクラス
 */
class Shader final {
public:
    //---------------------------------------------------------------------------------
    /**
     * @brief    コンストラクタ
     */
    Shader() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief    デストラクタ
     */
    ~Shader() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief	シェーダを作成する
     * @return	成功すれば true
     */
    [[nodiscard]] bool create() noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	頂点シェーダを取得する
     * @return	頂点シェーダのデータ
     */
    [[nodiscard]] ID3DBlob* vertexShader() const noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	ピクセルシェーダを取得する
     * @return	ピクセルシェーダのデータ
     */
    [[nodiscard]] ID3DBlob* pixelShader() const noexcept;

private:
    Microsoft::WRL::ComPtr<ID3DBlob> vertexShader_{};  /// 頂点シェーダ
    Microsoft::WRL::ComPtr<ID3DBlob> pixelShader_{};   /// ピクセルシェーダ
};