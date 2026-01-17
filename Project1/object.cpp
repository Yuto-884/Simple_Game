// オブジェクト基底クラス

#include "object.h"

namespace game {

    //---------------------------------------------------------------------------------
    /**
     * @brief	描画コマンド設定
     */
    void Object::setDrawCommand(const CommandList& commandList, UINT slot) noexcept {
        // コンスタントバッファの設定
        commandList.get()->SetGraphicsRootDescriptorTable(
            slot,
            constantBuffer_.getGpuDescriptorHandle());
    }

}  // namespace game