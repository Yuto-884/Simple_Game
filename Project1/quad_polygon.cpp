// 四角形ポリゴンクラス

#include "quad_polygon.h"
#include <cassert>

namespace {

    //---------------------------------------------------------------------------------
    /**
     * @brief    頂点バッファフォーマット
     */
    struct Vertex {
        DirectX::XMFLOAT3 position;  // 頂点座標（x, y, z）
        DirectX::XMFLOAT4 color;     // 頂点色（r, g, b, a）
    };
}  // namespace


//---------------------------------------------------------------------------------
/**
 * @brief	頂点バッファの生成
 * @return	成功すれば true
 */
[[nodiscard]] bool QuadPolygon::createVertexBuffer() noexcept {
    // 頂点データ
    Vertex vertices[] = {
        { {-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}, // 左上頂点
        {  {0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}, // 右上頂点
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}, // 左下頂点
        { {0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}, // 右下頂点
    };

    // 頂点データのサイズ
    const auto vertexBufferSize = sizeof(vertices);

    // ヒープの設定を指定
    // CPU からアクセス可能なメモリを利用する為の設定
    D3D12_HEAP_PROPERTIES heapProperty{};
    heapProperty.Type = D3D12_HEAP_TYPE_UPLOAD;
    heapProperty.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProperty.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heapProperty.CreationNodeMask = 1;
    heapProperty.VisibleNodeMask = 1;

    // どんなリソースを作成するかの設定
    D3D12_RESOURCE_DESC resourceDesc{};
    resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    resourceDesc.Alignment = 0;
    resourceDesc.Width = vertexBufferSize;
    resourceDesc.Height = 1;
    resourceDesc.DepthOrArraySize = 1;
    resourceDesc.MipLevels = 1;
    resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
    resourceDesc.SampleDesc.Count = 1;
    resourceDesc.SampleDesc.Quality = 0;
    resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

    // 頂点バッファの生成
    auto res = Device::instance().get()->CreateCommittedResource(
        &heapProperty,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&vertexBuffer_));
    if (FAILED(res)) {
        assert(false && "頂点バッファの作成に失敗");
        return false;
    }

    // 頂点バッファにデータを転送する
    // CPU からアクセス可能なアドレスを取得
    Vertex* data{};

    // バッファをマップ（CPUからアクセス可能にする）
    // vertexBuffer_ を直接利用するのではなく、data を介して更新するイメージ
    res = vertexBuffer_->Map(0, nullptr, reinterpret_cast<void**>(&data));
    if (FAILED(res)) {
        assert(false && "頂点バッファのマップに失敗");
        return false;
    }

    // 頂点データをコピー
    memcpy_s(data, vertexBufferSize, vertices, vertexBufferSize);

    // コピーが終わったのでマップ解除（CPUからアクセス不可にする）
    // ここまで来たら GPU が利用するメモリ領域（VRAM）にコピー済みなので、vertices は不要になる
    vertexBuffer_->Unmap(0, nullptr);

    // 頂点バッファビューの設定
    vertexBufferView_.BufferLocation = vertexBuffer_->GetGPUVirtualAddress();  // 頂点バッファのアドレス
    vertexBufferView_.SizeInBytes = vertexBufferSize;                       // 頂点バッファのサイズ
    vertexBufferView_.StrideInBytes = sizeof(Vertex);                         // 1頂点あたりのサイズ

    // トポロジーの設定
    topology_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;  // 四角形を描画するので TRIANGLESTRIP

    return true;
}

//---------------------------------------------------------------------------------
/**
 * @brief	インデックスバッファの生成
 * @return	成功すれば true
 */
[[nodiscard]] bool QuadPolygon::createIndexBuffer() noexcept {
    uint16_t indices[] = {
        0, 1, 2, 3  // 頂点インデックス（TRIANGLESTRIP なので Z オーダー（順番）で指定する）
    };

    // インデックスデータのサイズ
    const auto indexBufferSize = sizeof(indices);

    // ヒープの設定を指定
    D3D12_HEAP_PROPERTIES heapProperty{};
    heapProperty.Type = D3D12_HEAP_TYPE_UPLOAD;
    heapProperty.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProperty.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heapProperty.CreationNodeMask = 1;
    heapProperty.VisibleNodeMask = 1;

    // リソースの設定を行う
    D3D12_RESOURCE_DESC resourceDesc{};
    resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    resourceDesc.Alignment = 0;
    resourceDesc.Width = indexBufferSize;
    resourceDesc.Height = 1;
    resourceDesc.DepthOrArraySize = 1;
    resourceDesc.MipLevels = 1;
    resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
    resourceDesc.SampleDesc.Count = 1;
    resourceDesc.SampleDesc.Quality = 0;
    resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

    // インデックスバッファの生成
    auto res = Device::instance().get()->CreateCommittedResource(
        &heapProperty,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&indexBuffer_));
    if (FAILED(res)) {
        assert(false && "インデックスバッファの作成に失敗");
        return false;
    }

    // インデックスバッファにデータを転送する
    uint16_t* data{};
    res = indexBuffer_->Map(0, nullptr, reinterpret_cast<void**>(&data));
    if (FAILED(res)) {
        assert(false && "インデックスバッファのマップに失敗");
        return false;
    }

    memcpy_s(data, indexBufferSize, indices, indexBufferSize);
    // ここまで来たら GPU が利用するメモリ領域（VRAM）にコピー済みなので、indices は不要になる
    indexBuffer_->Unmap(0, nullptr);

    // インデックスバッファビュー作成
    indexBufferView_.BufferLocation = indexBuffer_->GetGPUVirtualAddress();
    indexBufferView_.SizeInBytes = indexBufferSize;
    indexBufferView_.Format = DXGI_FORMAT_R16_UINT;  // indices の型が 16bit 符号なし整数なので R16_UINT

    // インデックス数の設定
    indexCount_ = _countof(indices);

    return true;
}