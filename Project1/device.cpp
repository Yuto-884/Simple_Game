// デバイスクラス

#include "device.h"
#include <cassert>

// ライブラリのリンク
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxguid.lib")

//---------------------------------------------------------------------------------
/**
 * @brief	デバイスを作成する
 * @param	dxgi	DXGI クラスのインスタンス
 * @return	作成出来た場合は true
 */
[[nodiscard]] bool Device::create() noexcept {
    // DXGI の生成
    if (!dxgiInstance_.setDisplayAdapter()) {
        assert(false && "DXGIのアダプタ設定に失敗しました");
        return false;
    }

    // デバイス作成
    const auto hr = D3D12CreateDevice(dxgiInstance_.displayAdapter(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device_));
    if (FAILED(hr)) {
        assert(false && "デバイス作成に失敗");
        return false;
    }

    return true;
}

//---------------------------------------------------------------------------------
/**
 * @brief	デバイスを取得する
 * @return	dx12 デバイスのポインタ
 */
[[nodiscard]] ID3D12Device* Device::get() const noexcept {
    if (!device_) {
        assert(false && "デバイスが未作成です");
    }

    return device_.Get();
}

//---------------------------------------------------------------------------------
/**
 * @brief	DXGI インスタンスを取得する
 * @return	DXGI インスタンスの参照
 */
[[nodiscard]] const DXGI& Device::dxgi() const noexcept {
    return dxgiInstance_;
}


