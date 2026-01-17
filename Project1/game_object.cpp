// オブジェクトクラス

#include "game_object.h"
#include "shape_container.h"
#include <cmath>

namespace {
    //---------------------------------------------------------------------------------
    /**
     * @brief	ゲームオブジェクトコンスタントバッファ用データ構造体
     */
    struct ConstBufferData {
        DirectX::XMMATRIX world_{};  /// ワールド行列
        DirectX::XMFLOAT4 color_{};  /// カラー(RGBA)
    };
}  // namespace

namespace game {
    //---------------------------------------------------------------------------------
    /**
     * @brief	オブジェクトの初期化
     */
    void GameObject::initialize() noexcept {
        createDrawBuffer();
    }

    //---------------------------------------------------------------------------------
    /**
     * @brief	描画コマンド設定
     * @param	commandList	コマンドリスト
     * @param	slot		スロット番号
     */
    void GameObject::setDrawCommand(const CommandList& commandList, UINT slot) noexcept {
        Object::setDrawCommand(commandList, slot);
        ShapeContainer::instance().draw(commandList, shapeId_);
    }

    //---------------------------------------------------------------------------------
    /**
     * @brief	描画用バッファの作成
     */
    void GameObject::createDrawBuffer() noexcept {
        if (!constantBuffer_.create(sizeof(ConstBufferData))) {
            assert(false && "GameObject コンスタントバッファの作成に失敗しました");
        }
    }

    //---------------------------------------------------------------------------------
    /**
     * @brief	描画用バッファの更新
     */
    void GameObject::updateDrawBuffer() noexcept {
        Object::updateConstantBuffer(ConstBufferData{ DirectX::XMMatrixTranspose(world_), color_ });
    }

    //---------------------------------------------------------------------------------
    /**
     * @brief	オブジェクトハンドルの設定
     * @param	handle	オブジェクトハンドル
     */
    void GameObject::setHandle(UINT64 handle) noexcept {
        handle_ = handle;
    }


    //---------------------------------------------------------------------------------
    /**
     * @brief	オブジェクトハンドルの取得
     * @return  オブジェクトハンドル
     */
    [[nodiscard]] UINT64 GameObject::handle() const noexcept {
        return handle_;
    }


    //---------------------------------------------------------------------------------
    /**
     * @brief	座標とカラーの設定
     * @param	pos		座標
     * @param	rot		回転
     * @param	scale	スケール
     * @param	color	カラー
     * @param	shapeId	形状識別子
     */
    void GameObject::set(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rot, DirectX::XMFLOAT3 scale, DirectX::XMFLOAT4 color, UINT64 shapeId) noexcept {
        // ワールド行列の計算
        DirectX::XMMATRIX matScale = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
        DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
        DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
        world_ = matScale * rotation * translation;

        // カラーの設定
        color_ = color;
        // 形状識別子の設定
        shapeId_ = shapeId;

        // 衝突判定用の半径を設定
        radius_ = (scale.x + scale.y + scale.z) / (3.0f * 2.0f);
    }

    //---------------------------------------------------------------------------------
    /**
     * @brief	ワールド行列の取得
     * @return  ワールド行列
     */
    [[nodiscard]] DirectX::XMMATRIX GameObject::world() const noexcept {
        return world_;
    }

    //---------------------------------------------------------------------------------
    /**
     * @brief	カラーの取得
     * @return  カラー
     */
    [[nodiscard]] DirectX::XMFLOAT4 GameObject::color() const noexcept {
        return color_;
    }
}  // namespace game