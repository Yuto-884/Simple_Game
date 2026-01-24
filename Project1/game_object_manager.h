// ゲームオブジェクト管理クラス

#pragma once

#include "game_object.h"
#include <functional>
#include <typeinfo>


namespace game {

    //---------------------------------------------------------------------------------
    /**
     * @brief	ゲームオブジェクト管理クラス
     */
    class GameObjectManager final {
    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief	インスタンスの取得
         * @return	インスタンスの参照
         */
        static GameObjectManager& instance() noexcept {
            static GameObjectManager instance;
            return instance;
        }

    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief	管理オブジェクトの更新
         */
        void update() noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief	管理オブジェクトの後更新
         */
        void postUpdate() noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief	管理オブジェクトの描画
         * @param	commandList	コマンドリスト
         */
        void draw(const CommandList& commandList) noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief	管理オブジェクトのクリア
         */
        void clear() noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief	オブジェクト取得
         * @param	handle	オブジェクトハンドル
         * @return	オブジェクトのポインタ(存在しない場合はnullopt)
         */
        [[nodiscard]] std::optional<GameObject*> gameObject(UINT64 handle) noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief	衝突判定オブジェクトを登録
         * @param	handle	衝突オブジェクトハンドル
         */
        void registerHit(UINT64 handle) noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief	オブジェクト生成
         * @tparam	T		生成するオブジェクトの型
         * @tparam	Args	コンストラクタ引数の型
         * @param	args	コンストラクタ引数
         * @return	生成したオブジェクトのハンドル
         */
        template <typename T, typename... Args>
        [[nodiscard]] UINT64 createObject(Args&&... args) noexcept {
            static_assert(std::is_base_of<GameObject, T>::value, "GameObject ではない物を作ろうとしています");
            const auto handle = ++counter_;

            auto func = [... a = std::forward<Args>(args)]() mutable {
                auto p = std::make_unique<T>(std::move(a)...);
                p->setTypeId(typeid(T).hash_code());
                return p;
                };
            registerCreation(std::move(func), handle);

            return handle;
        }

        //---------------------------------------------------------------------------------
        /**
         * @brief	オブジェクト削除登録
         * @param	handle	削除オブジェクトハンドル
         */
        void registerDelete(UINT64 handle) noexcept;


    private:
        //---------------------------------------------------------------------------------
        /**
         * @brief	オブジェクト生成
         * @param	creation	生成関数
         * @param	handle		オブジェクトハンドル
         */
        void registerCreation(std::function<std::unique_ptr<GameObject>()> creation, const UINT64 handle) noexcept;

    private:
        //---------------------------------------------------------------------------------
        /**
         * @brief    コンストラクタ
         */
        GameObjectManager() = default;

        //---------------------------------------------------------------------------------
        /**
         * @brief    デストラクタ
         */
        ~GameObjectManager();

        //---------------------------------------------------------------------------------
        /**
         * @brief	コピーとムーブの禁止
         */
        GameObjectManager(const GameObjectManager& r) = delete;
        GameObjectManager& operator=(const GameObjectManager& r) = delete;
        GameObjectManager(GameObjectManager&& r) = delete;
        GameObjectManager& operator=(GameObjectManager&& r) = delete;

    private:
        UINT64 counter_{};
    };
}  // namespace game


