// 三角形ポリゴンクラス

#pragma once

#include "shape.h"

//---------------------------------------------------------------------------------
/**
 * @brief	ポリゴンクラス
 */
class TrianglePolygon final : public Shape {

public:
    //---------------------------------------------------------------------------------
    /**
     * @brief    コンストラクタ
     */
    TrianglePolygon() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief    デストラクタ
     */
    ~TrianglePolygon() = default;

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
    [[nodiscard]] virtual bool createIndexBuffer() noexcept override;

};