// スワップチェイン制御クラス

#pragma once

#include "command_queue.h"

//---------------------------------------------------------------------------------
/**
 * @brief	スワップチェイン制御クラス
 */
class SwapChain final {
public:
    //---------------------------------------------------------------------------------
    /**
     * @brief    コンストラクタ
     */
    SwapChain() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief    デストラクタ
     */
    ~SwapChain() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief	スワップチェインの生成
     * @param	commandQueue	コマンドキュークラスのインスタンス
     * @return	生成の成否
     */
    [[nodiscard]] bool create(const CommandQueue& commandQueue) noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	スワップチェインを取得する
     * @return	スワップチェインのポインタ
     */
    [[nodiscard]] IDXGISwapChain3* get() const noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	スワップチェインの設定を取得する
     * @return	スワップチェインの設定
     */
    [[nodiscard]] const DXGI_SWAP_CHAIN_DESC1& getDesc() const noexcept;

private:
    Microsoft::WRL::ComPtr<IDXGISwapChain3> swapChain_{};      /// スワップチェイン
    DXGI_SWAP_CHAIN_DESC1                   swapChainDesc_{};  /// スワップチェインの設定
};