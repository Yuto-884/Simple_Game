// 入力処理を担当するクラス

#include "input.h"

//---------------------------------------------------------------------------------
/**
 * @brief	キー情報の取得
 * @param	key		キーの識別子
 * @return	入力されていればtrue
 */
[[nodiscard]] bool Input::getKey(uint16_t sKey) const noexcept {
    return (keyState_[sKey] & 0x80);
}

//---------------------------------------------------------------------------------
/**
 * @brief	キー情報の取得
 * @param	key		キーの識別子
 * @return	入力したらtrue
 */
[[nodiscard]] bool Input::getTrigger(uint16_t sKey) const noexcept {
    return ((keyState_[sKey] & 0x80) && !(prevKeyState_[sKey] & 0x80));
}

//---------------------------------------------------------------------------------
/**
 * @brief	キー情報の更新
 * @param	pState	ハードから設定されたキー情報配列のポインタ
 * @return
 */
void Input::updateKeyState(void* pState) noexcept {
    memcpy_s(keyState_.data(), keyState_.size(), pState, keyState_.size());
}

//---------------------------------------------------------------------------------
/**
 * @brief	キー情報の更新
 * @return
 */
void Input::updatePrevKeyState() noexcept {
    memcpy_s(prevKeyState_.data(), prevKeyState_.size(), keyState_.data(), keyState_.size());
}
