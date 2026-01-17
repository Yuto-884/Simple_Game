// 形状ベースクラス

#include "shape.h"
#include <cassert>


//---------------------------------------------------------------------------------
/**
 * @brief	ポリゴンの生成
 * @return	成功すれば true
 */
[[nodiscard]] bool Shape::create() noexcept {
    // 頂点バッファの生成
    if (!createVertexBuffer()) {
        return false;
    }
    // インデックスバッファの生成
    if (!createIndexBuffer()) {
        return false;
    }

    return true;
}

//---------------------------------------------------------------------------------
/**
 * @brief	ポリゴンの描画
 * @param	commandList	コマンドリスト
 */
void Shape::draw(const CommandList& commandList) noexcept {
    // 頂点バッファの設定
    commandList.get()->IASetVertexBuffers(0, 1, &vertexBufferView_);
    // インデックスバッファの設定
    commandList.get()->IASetIndexBuffer(&indexBufferView_);
    // プリミティブ形状の設定
    commandList.get()->IASetPrimitiveTopology(topology_);
    // 描画コマンド
    commandList.get()->DrawIndexedInstanced(indexCount_, 1, 0, 0, 0);
}