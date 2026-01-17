// ディスクリプターヒープ制御クラス

#pragma once

#include <d3d12.h>
#include <unordered_map>
#include <optional>
#include <memory>

class DescriptorHeap;  /// 前方宣言

//---------------------------------------------------------------------------------
/**
 * @brief	ディスクリプタヒープ制御クラス
 * 簡易シングルトンパターンで作成する
 */
class DescriptorHeapContainer final {
public:
    //---------------------------------------------------------------------------------
    /**
     * @brief	インスタンスの取得
     * @return	インスタンスの参照
     */
    static DescriptorHeapContainer& instance() noexcept {
        static DescriptorHeapContainer instance;
        return instance;
    }

    //---------------------------------------------------------------------------------
    /**
     * @brief	ディスクリプタヒープを生成する
     * @param	type			ディスクリプタヒープのタイプ
     * @param	numDescriptors	ディスクリプタの数
     * @param	shaderVisible	シェーダーからアクセス可能かどうか
     * @return	生成の成否
     */
    [[nodiscard]] bool create(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible = false) noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	解放予約されているディスクリプタを解放する
     */
    void applyPendingFree() noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	ディスクリプタヒープを取得する
     * @param	tyep タイプ
     * @return	ディスクリプタヒープのポインタ
     */
    [[nodiscard]] ID3D12DescriptorHeap* get(D3D12_DESCRIPTOR_HEAP_TYPE type) const noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	ディスクリプタを確保する
     * @param	tyep タイプ
     * @return	確保したディスクリプタインデックス
     */
    [[nodiscard]] std::optional<UINT> allocateDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE type) noexcept;

    //---------------------------------------------------------------------------------
    /**
     * @brief	開放予定のディスクリプタを登録する
     * @param	tyep タイプ
     */
    void releaseDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT descriptorIndex) noexcept;

private:
    //---------------------------------------------------------------------------------
    /**
     * @brief    コンストラクタ
     */
    DescriptorHeapContainer();

    //---------------------------------------------------------------------------------
    /**
     * @brief    デストラクタ
     */
    ~DescriptorHeapContainer();

    //---------------------------------------------------------------------------------
    /**
     * @brief	コピーとムーブの禁止
     */
    DescriptorHeapContainer(const DescriptorHeapContainer& r) = delete;
    DescriptorHeapContainer& operator=(const DescriptorHeapContainer& r) = delete;
    DescriptorHeapContainer(DescriptorHeapContainer&& r) = delete;
    DescriptorHeapContainer& operator=(DescriptorHeapContainer&& r) = delete;

private:
    std::unordered_map<UINT, std::unique_ptr<DescriptorHeap>> map_{};  /// 種類毎のデスクリプタマップ
};