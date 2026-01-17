// パイプラインステートオブジェクトクラス

#pragma once

#include "device.h"
#include "shader.h"
#include "root_signature.h"

//---------------------------------------------------------------------------------
/**
 * @brief	パイプラインステートオブジェクトクラス
 */
class PiplineStateObject final {
public:
    //---------------------------------------------------------------------------------
    /**
     * @brief    コンストラクタ
     */
    PiplineStateObject() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief    デストラクタ
     */
    ~PiplineStateObject() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief	パイプラインステートオブジェクトを作成する
     * @param	shader			シェーダクラスのインスタンス
     * @param	rootSignature	ルートシグネチャクラスのインスタンス
     * @return	成功すれば true
     */
    [[nodiscard]] bool create(const Shader& shader, const RootSignature& rootSignature) noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	パイプラインステートを取得する
     * @return	パイプラインステートのポインタ
     */
    [[nodiscard]] ID3D12PipelineState* get() const noexcept;

private:
    Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState_{};  /// パイプラインステート
};
