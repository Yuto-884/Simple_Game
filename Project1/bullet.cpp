// 弾制御クラス

#include "bullet.h"
#include "enemy.h"

#include "shape_container.h"
#include "quad_polygon.h"

#include "game_object_manager.h"

namespace game {
    //---------------------------------------------------------------------------------
    /**
     * @brief	オブジェクトの初期化
     */
    void Bullet::initialize() noexcept {
        GameObject::initialize();

        auto quadId = ShapeContainer::instance().create<QuadPolygon>();

        DirectX::XMFLOAT3 parentPos{};
        if (auto parent = GameObjectManager::instance().gameObject(parent_)) {
            DirectX::XMStoreFloat3(&parentPos, parent.value()->world().r[3]);
        }
        set(parentPos, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 0.3f }, quadId);
    }

    //---------------------------------------------------------------------------------
    /**
     * @brief	オブジェクトの更新
     */
    void Bullet::update() noexcept {
        GameObject::update();

        constexpr float moveSpeed = 0.3f;
        // 入力処理
        DirectX::XMFLOAT3 pos{};
        pos.z += moveSpeed;
        // ワールド行列の更新
        world_ = DirectX::XMMatrixMultiply(world_, DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z));

        GameObjectManager::instance().registerHit(handle());
    }

    //---------------------------------------------------------------------------------
    /**
     * @brief	ヒットした時の処理
     */
    void Bullet::onHit() noexcept {
        GameObjectManager::instance().registerDelete(handle());
    }

    //---------------------------------------------------------------------------------
    /**
     * @brief	ヒットする対象
     */
    [[nodiscard]] UINT64 Bullet::hitTargetTypeId() noexcept {
        return id::get<Enemy>();
    }

}  // namespace game
