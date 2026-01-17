// レンダーターゲット制御クラス

#include "render_target.h"
#include <cassert>

namespace {
    constexpr auto heapType_ = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
}

//---------------------------------------------------------------------------------
/**
 * @brief    デストラクタ
 */
RenderTarget::~RenderTarget() {
    renderTargets_.clear();
}

//---------------------------------------------------------------------------------
/**
 * @brief	バックバッファを生成する
 * @param	swapChain	スワップチェイン
 * @return	生成の成否
 */
[[nodiscard]] bool RenderTarget::createBackBuffer(const SwapChain& swapChain) noexcept {
    // スワップチェインの設定を取得
    const auto& desc = swapChain.getDesc();

    // レンダーターゲットリソースのサイズを設定
    renderTargets_.resize(desc.BufferCount);

    // ディスクリプターヒープの取得
    auto heap = DescriptorHeapContainer::instance().get(heapType_);

    // ディスクリプターヒープのハンドルを取得
    auto handle = heap->GetCPUDescriptorHandleForHeapStart();

    // バックバッファの生成
    for (uint8_t i = 0; i < desc.BufferCount; ++i) {
        const auto hr = swapChain.get()->GetBuffer(i, IID_PPV_ARGS(&renderTargets_[i]));
        if (FAILED(hr)) {
            assert(false && "バックバッファの取得に失敗しました");
            return false;
        }

        // レンダーターゲットビューを作成してディスクリプタヒープのハンドルと関連付ける
        Device::instance().get()->CreateRenderTargetView(renderTargets_[i].Get(), nullptr, handle);

        // 次のハンドルへ移動
        handle.ptr += Device::instance().get()->GetDescriptorHandleIncrementSize(heapType_);
    }

    return true;
}

//---------------------------------------------------------------------------------
/**
 * @brief	ビュー（ディスクリプタハンドル）を取得する
 * @return	ディスクリプタハンドル
 */
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE RenderTarget::getCpuDescriptorHandle(UINT index) const noexcept {

    if (index >= renderTargets_.size() || !renderTargets_[index]) {
        assert(false && "不正なレンダーターゲットです");
    }

    // ディスクリプターヒープの取得
    auto heap = DescriptorHeapContainer::instance().get(heapType_);

    // ディスクリプタヒープのハンドルを取得
    auto handle = heap->GetCPUDescriptorHandleForHeapStart();

    // インデックスに応じてハンドルを移動
    handle.ptr += index * Device::instance().get()->GetDescriptorHandleIncrementSize(heapType_);
    return handle;
}

//---------------------------------------------------------------------------------
/**
 * @brief	レンダーターゲットを取得する
 * @param	index	インデックス
 */
[[nodiscard]] ID3D12Resource* RenderTarget::get(UINT index) const noexcept {
    if (index >= renderTargets_.size() || !renderTargets_[index]) {
        assert(false && "不正なレンダーターゲットです");
        return nullptr;
    }
    return renderTargets_[index].Get();
}