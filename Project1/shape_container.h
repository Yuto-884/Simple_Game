// 形状コンテナクラス

#pragma once

#include "shape.h"
#include <unordered_map>
#include <memory>
#include<typeinfo>

//---------------------------------------------------------------------------------
/**
 * @brief	形状コンテナクラス
 */
class ShapeContainer final {
public:
    //---------------------------------------------------------------------------------
    /**
     * @brief	インスタンスの取得
     * @return	インスタンスの参照
     */
    static ShapeContainer& instance() noexcept {
        static ShapeContainer instance;
        return instance;
    }

public:
    //---------------------------------------------------------------------------------
    /**
     * @brief	形状の生成と登録
     * @return	生成に成功したら登録識別子を返す
     */
    template <class T>
    [[nodiscard]] UINT64 create() noexcept {
        const UINT64 id = typeid(T).hash_code();

        if (shapes_.find(id) != shapes_.end()) {
            return id;
        }

        auto p = std::make_unique<T>();
        if (!p->create()) {
            assert(false && "形状の生成に失敗しました");
            return 0;
        }

        shapes_.emplace(id, std::move(p));
        return id;
    }


    //---------------------------------------------------------------------------------
    /**
     * @brief	ポリゴンの描画
     * @param	commandList	コマンドリスト
     * @param	形状識別子
     */
    void draw(const CommandList& commandList, UINT64 id) noexcept;

private:
    //---------------------------------------------------------------------------------
    /**
     * @brief    コンストラクタ
     */
    ShapeContainer() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief    デストラクタ
     */
    ~ShapeContainer() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief	コピーとムーブの禁止
     */
    ShapeContainer(const ShapeContainer&) = delete;
    ShapeContainer& operator=(const ShapeContainer&) = delete;
    ShapeContainer(ShapeContainer&&) = delete;
    ShapeContainer& operator=(ShapeContainer&&) = delete;

protected:
    std::unordered_map<UINT64, std::unique_ptr<Shape>> shapes_;  /// 形状コンテナ
};
