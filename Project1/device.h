// デバイスクラス

#pragma once

#include "DXGI.h"
#include <d3d12.h>
#include <wrl/client.h>
//#include "../util.h"

//---------------------------------------------------------------------------------
/**
 * @brief	デバイスクラス
 * 簡易シングルトンパターンで作成する
 */
class Device final {
public:
    //---------------------------------------------------------------------------------
    /**
     * @brief	インスタンスの取得
     * @return	インスタンスの参照
     */
    static Device& instance() noexcept {
        static Device instance;
        return instance;
    }

    //---------------------------------------------------------------------------------
    /**
     * @brief	デバイスを作成する
     * @return	作成出来た場合は true
     */
    [[nodiscard]] bool create() noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	デバイスを取得する
     * @return	dx12 デバイスのポインタ
     */
    [[nodiscard]] ID3D12Device* get() const noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	DXGI インスタンスを取得する
     * @return	DXGI インスタンスの参照
     */
    [[nodiscard]] const DXGI& dxgi() const noexcept;


private:
    //---------------------------------------------------------------------------------
    /**
     * @brief    コンストラクタ
     */
    Device() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief    デストラクタ
     */
    ~Device() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief	コピーとムーブの禁止
     */
    Device(const Device& r) = delete;
    Device& operator=(const Device& r) = delete;
    Device(Device&& r) = delete;
    Device& operator=(Device&& r) = delete;

private:
    DXGI                                 dxgiInstance_{};  /// DXGI インスタンス
    Microsoft::WRL::ComPtr<ID3D12Device> device_{};        /// デバイス
};