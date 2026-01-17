// 四角形ポリゴンクラス

#pragma once

#include "shape.h"

//---------------------------------------------------------------------------------
/**
 * @brief	ポリゴンクラス
 */
class QuadPolygon final : public Shape {
public:
    //---------------------------------------------------------------------------------
    /**
     * @brief    コンストラクタ
     */
    QuadPolygon() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief    デストラクタ
     */
    ~QuadPolygon() = default;

private:
    //---------------------------------------------------------------------------------
    /**
     * @brief	頂点バッファの生成
     * @return	成功すれば true
     */
    [[nodiscard]] virtual bool createVertexBuffer() noexcept override;

    //---------------------------------------------------------------------------------
    /**
     * @brief	インデックスバッファの生成
     * @return	成功すれば true
     */
    [[nodiscard]] bool createIndexBuffer() noexcept override;
};