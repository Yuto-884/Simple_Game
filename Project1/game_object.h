// ゲームクラス

#pragma once

#include <DirectXMath.h>
#include "object.h"

namespace game {

    //---------------------------------------------------------------------------------
    /**
     * @brief	オブジェクトクラス
     */
    class GameObject : public Object {
    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief    コンストラクタ
         */
        GameObject() = default;
        GameObject(UINT64 parent) : parent_(parent) {}

        //---------------------------------------------------------------------------------
        /**
         * @brief    デストラクタ
         */
        virtual ~GameObject() = default;

    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief	オブジェクトの初期化
         */
        virtual void initialize() noexcept override;

        //---------------------------------------------------------------------------------
        /**
         * @brief	オブジェクトの更新
         */
        virtual void update() noexcept override {};

        //---------------------------------------------------------------------------------
        /**
         * @brief	描画コマンド設定
         * @param	commandList	コマンドリスト
         * @param	slot		スロット番号
         */
        virtual void setDrawCommand(const CommandList& commandList, UINT slot) noexcept override;

    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief	描画用バッファの作成
         */
        virtual void createDrawBuffer() noexcept override;

        //---------------------------------------------------------------------------------
        /**
         * @brief	描画用バッファの更新
         */
        virtual void updateDrawBuffer() noexcept override;

    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief	ヒットした時の処理
         */
        virtual void onHit() noexcept {};

        //---------------------------------------------------------------------------------
        /**
         * @brief	ヒットする対象
         */
        [[nodiscard]] virtual UINT64 hitTargetTypeId() noexcept { return {}; }

    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief	オブジェクトハンドルの設定
         * @param	handle	オブジェクトハンドル
         */
        void setHandle(UINT64 handle) noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief	オブジェクトハンドルの取得
         * @return  オブジェクトハンドル
         */
        [[nodiscard]] UINT64 handle() const noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief	座標とカラーの設定
         * @param	pos		座標
         * @param	rot		回転
         * @param	scale	スケール
         * @param	color	カラー
         * @param	shapeId	形状識別子
         */
        void set(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rot, DirectX::XMFLOAT3 scale, DirectX::XMFLOAT4 color, UINT64 shapeId) noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief	ワールド行列の取得
         * @return  ワールド行列
         */
        [[nodiscard]] DirectX::XMMATRIX world() const noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief	カラーの取得
         * @return  カラー
         */
        [[nodiscard]] DirectX::XMFLOAT4 color() const noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief	半径の取得
         * @return  半径
         */
        [[nodiscard]] float radius() noexcept { return radius_; };


    protected:
        DirectX::XMMATRIX world_ = DirectX::XMMatrixIdentity();                /// ワールド行列
        DirectX::XMFLOAT4 color_ = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);  /// カラー(RGBA)
        UINT64            shapeId_{};                                          /// 形状識別子
        UINT64            handle_{};                                           /// ゲームオブジェクトハンドル
        UINT64            parent_{};                                           /// 親オブジェクトハンドル
        float             radius_{};                                           /// 当たり判定用半径
    };
}  // namespace game
