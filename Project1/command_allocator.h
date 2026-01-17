// コマンドアロケータ制御クラス

#pragma once

#include "device.h"

//---------------------------------------------------------------------------------
/**
 * @brief	コマンドアロケータ制御クラス
 */
class CommandAllocator final {
public:
    //---------------------------------------------------------------------------------
    /**
     * @brief    コンストラクタ
     */
    CommandAllocator() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief    デストラクタ
     */
    ~CommandAllocator() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief	コマンドアロケータ作成
     * @param	type	コマンドリストのタイプ
     * @return	成功すれば true
     */
    [[nodiscard]] bool create(const D3D12_COMMAND_LIST_TYPE type) noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	コマンドアロケータをリセットする
     */
    void reset() noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	コマンドアロケータを取得する
     * @return	コマンドアロケータのポインタ
     */
    [[nodiscard]] ID3D12CommandAllocator* get() const noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	コマンドリストのタイプを取得する
     * @return	コマンドリストのタイプ
     */
    [[nodiscard]] D3D12_COMMAND_LIST_TYPE getType() const noexcept;

private:
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator_{};  /// コマンドアロケータ
    D3D12_COMMAND_LIST_TYPE                        type_{};              /// コマンドリストのタイプ
};
