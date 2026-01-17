#pragma once// オブジェクト基底クラス

#pragma once

#include "constant_buffer.h"
#include "command_list.h"
//#include "../util.h"

namespace game {
    //---------------------------------------------------------------------------------
    /**
     * @brief	オブジェクトクラス
     */
    class Object {
    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief    コンストラクタ
         */
        Object() = default;

        //---------------------------------------------------------------------------------
        /**
         * @brief    デストラクタ
         */
        virtual ~Object() = default;

        //---------------------------------------------------------------------------------
        /**
         * @brief	オブジェクトの初期化
         */
        virtual void initialize() noexcept {};

        //---------------------------------------------------------------------------------
        /**
         * @brief	オブジェクトの更新
         */
        virtual void update() noexcept {};

        //---------------------------------------------------------------------------------
        /**
         * @brief	描画コマンド設定
         * @param	commandList	コマンドリスト
         * @param	slot		スロット番号
         */
        virtual void setDrawCommand(const CommandList& commandList, UINT slot) noexcept;

    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief	描画用バッファの作成
         */
        virtual void createDrawBuffer() noexcept = 0;

        //---------------------------------------------------------------------------------
        /**
         * @brief	描画用バッファの更新
         */
        virtual void updateDrawBuffer() noexcept = 0;

    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief	オブジェクトタイプIDの取得
         * @return	オブジェクトタイプID
         */
        [[nodiscard]] UINT64 typeId() const noexcept {
            return typeId_;
        };

        //---------------------------------------------------------------------------------
        /**
         * @brief	オブジェクトタイプIDの設定
         * @param	id	オブジェクトタイプID
         */
        void setTypeId(UINT64 id) noexcept {
            typeId_ = id;
        };

    protected:
        //---------------------------------------------------------------------------------
        /**
         * @brief	コンスタントバッファ更新
         * @param	data　更新データ
         */
        template <class T>
        void updateConstantBuffer(const T& data) noexcept {
            std::byte* dst{};
            constantBuffer_.constantBuffer()->Map(0, nullptr, reinterpret_cast<void**>(&dst));
            memcpy_s(dst, sizeof(T), &data, sizeof(T));
            constantBuffer_.constantBuffer()->Unmap(0, nullptr);
        };

    protected:
        ConstantBuffer constantBuffer_{};  /// コンスタントバッファ
        UINT64         typeId_{};          /// オブジェクトタイプID
    };
}  // namespace game