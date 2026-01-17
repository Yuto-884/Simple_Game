// 入力処理を担当するクラス

#pragma once

#include <Windows.h>
#include <cstdint>
#include <array>

//---------------------------------------------------------------------------------
/**
 * @brief	入力処理クラス
 * 簡易シングルトンパターンで作成する
 */
class Input final {
public:
    //---------------------------------------------------------------------------------
    /**
     * @brief	インスタンスの取得
     * @return	インスタンスの参照
     */
    static Input& instance() noexcept {
        static Input instance;
        return instance;
    }

    //---------------------------------------------------------------------------------
    /**
     * @brief	キー情報の取得
     * @param	key		キーの識別子
     * @return	入力されていればtrue
     */
    [[nodiscard]] bool getKey(uint16_t sKey) const noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	キー情報の取得
     * @param	key		キーの識別子
     * @return	入力したらtrue
     */
    [[nodiscard]] bool getTrigger(uint16_t sKey) const noexcept;


    //---------------------------------------------------------------------------------
    /**
     * @brief	キー情報の更新
     * @param	pState	ハードから設定されたキー情報配列のポインタ
     * @return
     */
    void updateKeyState(void* pState) noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	キー情報の更新
     * @return
     */
    void updatePrevKeyState() noexcept;


private:
    // シングルトンパターンにするため、コンストラクタとデストラクタを private にする

    //---------------------------------------------------------------------------------
    /**
     * @brief    コンストラクタ
     */
    Input() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief    デストラクタ
     */
    ~Input() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief	コピーとムーブの禁止
     */
    Input(const Input& r) = delete;
    Input& operator=(const Input& r) = delete;
    Input(Input&& r) = delete;
    Input& operator=(Input&& r) = delete;

private:
    std::array<byte, 256> keyState_{};			/// ハードから設定されたキー情報配列
    std::array<byte, 256> prevKeyState_{};		/// ハードから設定されたキー情報配列
};
