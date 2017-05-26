/**
 * This work copyright Chao Sun(qq:296449610) and licensed under
 * a Creative Commons Attribution 3.0 Unported License(https://creativecommons.org/licenses/by/3.0/).
 */

#include "../common/buffer.h"
#include "../common/codec-utils.h"

#include "rcv-message.h"

namespace netty {
    namespace net {
        bool RcvMessage::DecodeMsgHeader(common::Buffer *buffer, Header *header) {
            if (buffer->AvailableLength() < RcvMessage::HeaderSize()) {
                return false;
            }

            // 只简单校验MAGIC NO和payload size
            uint32_t offset = 0;
            header->magic = ByteOrderUtils::ReadUInt32(buffer->Pos + offset);
            if (header->magic != MESSAGE_MAGIC_NO) {
                return false;
            }
            offset += sizeof(header->magic);
            header->id.ts = ByteOrderUtils::ReadUInt64(buffer->Pos + offset);
            offset += sizeof(uint64_t);
            header->id.seq = ByteOrderUtils::ReadUInt32(buffer->Pos + offset);
            offset += sizeof(header->id.seq);
            header->len = ByteOrderUtils::ReadUInt32(buffer->Pos + offset);

            return header->len <= MAX_MSG_PAYLOAD_SIZE;
        }
    } // namespace net
} // namespace netty

