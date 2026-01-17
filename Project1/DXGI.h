// DXGI 制御クラス

#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl/client.h>

//---------------------------------------------------------------------------------
/**
 * @brief	DXGI 制御クラス
 */
class DXGI final {
public:
    //---------------------------------------------------------------------------------
    /**
     * @brief    コンストラクタ
     */
    DXGI() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief    デストラクタ
     */
    ~DXGI() = default;

    //---------------------------------------------------------------------------------
    /**
     * @brief	ディスプレイアダプタの設定
     * @return	ディスプレイの情報が正しく取得できた場合は true
     */
    [[nodiscard]] bool setDisplayAdapter() noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	dxgi ファクトリーを取得する
     * @return	dxgi ファクトリーのポインタ
     */
    [[nodiscard]] IDXGIFactory4* factory() const noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	ディスプレイアダプターを取得する
     * @return	ディスプレイアダプターのポインタ
     */
    [[nodiscard]] IDXGIAdapter1* displayAdapter() const noexcept;

private:
    Microsoft::WRL::ComPtr<IDXGIFactory4> dxgiFactory_{};  /// DXGIを作成するファクトリー
    Microsoft::WRL::ComPtr<IDXGIAdapter1> dxgiAdapter_{};  /// ディスプレイモード取得用アダプタ
};
