// 形状ベースクラス

#pragma once

#include "device.h"
#include "command_list.h"
#include <DirectXMath.h>

//---------------------------------------------------------------------------------
/**
 * @brief	形状ベースクラス
 */
class Shape {
public:
    //---------------------------------------------------------------------------------
    /**
     * @brief	コンスタントバッファ用データ構造体
     */
    struct ConstBufferData {
        DirectX::XMMATRIX world_{};  /// ワールド行列
        DirectX::XMFLOAT4 color_{};  /// カラー(RGBA)
    };

public:
    //---------------------------------------------------------------------------------
    /**
     * @brief    コンストラクタ
     */
    Shape() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief    デストラクタ
     */
    virtual ~Shape() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief	ポリゴンの生成
     * @return	成功すれば true
     */
    [[nodiscard]] bool create() noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	ポリゴンの描画
     * @param	commandList	コマンドリスト
     */
    void draw(const CommandList& commandList) noexcept;

protected:
    //---------------------------------------------------------------------------------
    /**
     * @brief	頂点バッファの生成
     * @return	成功すれば true
     */
    [[nodiscard]] virtual bool createVertexBuffer() noexcept = 0;

    //---------------------------------------------------------------------------------
    /**
     * @brief	インデックスバッファの生成
     * @return	成功すれば true
     */
    [[nodiscard]] virtual bool createIndexBuffer() noexcept = 0;

protected:
    Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuffer_{};      /// 頂点バッファ
    Microsoft::WRL::ComPtr<ID3D12Resource> indexBuffer_{};       /// インデックスバッファ
    D3D12_VERTEX_BUFFER_VIEW               vertexBufferView_{};  /// 頂点バッファビュー
    D3D12_INDEX_BUFFER_VIEW                indexBufferView_{};   /// インデックスバッファビュー
    D3D_PRIMITIVE_TOPOLOGY                 topology_{};          /// プリミティブトポロジー
    UINT                                   indexCount_{};        /// インデックス数
};