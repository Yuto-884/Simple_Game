// 敵制御クラス

#include "enemy.h"
#include "shape_container.h"
#include "triangle_polygon.h"

namespace game {
    //---------------------------------------------------------------------------------
    /**
     * @brief	敵の初期化
     */
    void Enemy::initialize() noexcept {
        GameObject::initialize();

        auto triId = ShapeContainer::instance().create<TrianglePolygon>();
        set({ 0.0f, 0.0f, 30.0f }, { 0.0f, 0.0f, 0.0f }, { 10.0f, 10.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1 }, triId);
    }

    //---------------------------------------------------------------------------------
    /**
     * @brief	敵の更新
     */
    void Enemy::update() noexcept {
    }


    //---------------------------------------------------------------------------------
    /**
     * @brief	ヒットした時の処理
     */
    void Enemy::onHit() noexcept {
        color_.y *= 0.95f;
        color_.z *= 0.95f;
    }


}  // namespace game