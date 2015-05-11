/*
 * Copyright (C) 2005-2015 Christoph Rupp (chris@crupp.de).
 * All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the property
 * of Christoph Rupp and his suppliers, if any. The intellectual and
 * technical concepts contained herein are proprietary to Christoph Rupp
 * and his suppliers and may be covered by Patents, patents in process,
 * and are protected by trade secret or copyright law. Dissemination of
 * this information or reproduction of this material is strictly forbidden
 * unless prior written permission is obtained from Christoph Rupp.
 */

#include "0root/root.h"

// Always verify that a file of level N does not include headers > N!
#include "2protobuf/protocol.h"
#include "4cursor/cursor_remote.h"
#include "4db/db_remote.h"
#include "4env/env_remote.h"

#ifndef HAM_ROOT_H
#  error "root.h was not included"
#endif

namespace hamsterdb {

void
RemoteCursor::close()
{
  SerializedWrapper request;
  request.id = kCursorCloseRequest;
  request.cursor_close_request.cursor_handle = m_remote_handle;

  SerializedWrapper reply;
  renv()->perform_request(&request, &reply);
  ham_assert(reply.id == kCursorCloseReply);
}

ham_status_t
RemoteCursor::do_overwrite(ham_record_t *record, uint32_t flags)
{
  SerializedWrapper request;
  request.id = kCursorOverwriteRequest;
  request.cursor_overwrite_request.cursor_handle = m_remote_handle;
  request.cursor_overwrite_request.flags = flags;

  if (record->size > 0) {
    request.cursor_overwrite_request.record.has_data = true;
    request.cursor_overwrite_request.record.data.size = record->size;
    request.cursor_overwrite_request.record.data.value = (uint8_t *)record->data;
  }
  request.cursor_overwrite_request.record.flags = record->flags;
  request.cursor_overwrite_request.record.partial_size = record->partial_size;
  request.cursor_overwrite_request.record.partial_offset = record->partial_offset;

  SerializedWrapper reply;
  renv()->perform_request(&request, &reply);
  ham_assert(reply.id == kCursorOverwriteReply);

  return (reply.cursor_overwrite_reply.status);
}

ham_status_t
RemoteCursor::do_get_duplicate_position(uint32_t *pposition)
{
  SerializedWrapper request;
  request.id = kCursorGetDuplicatePositionRequest;
  request.cursor_get_duplicate_position_request.cursor_handle = m_remote_handle;

  SerializedWrapper reply;
  renv()->perform_request(&request, &reply);
  ham_assert(reply.id == kCursorGetDuplicatePositionReply);

  ham_status_t st = reply.cursor_get_duplicate_position_reply.status;
  if (st == 0)
    *pposition = reply.cursor_get_duplicate_position_reply.position;
  return (st);
}

ham_status_t
RemoteCursor::do_get_duplicate_count(uint32_t flags, uint32_t *pcount)
{
  SerializedWrapper request;
  request.id = kCursorGetRecordCountRequest;
  request.cursor_get_record_count_request.cursor_handle = m_remote_handle;
  request.cursor_get_record_count_request.flags = flags;

  SerializedWrapper reply;
  renv()->perform_request(&request, &reply);
  ham_assert(reply.id == kCursorGetRecordCountReply);

  ham_status_t st = reply.cursor_get_record_count_reply.status;
  if (st == 0)
    *pcount = reply.cursor_get_record_count_reply.count;
  else
    *pcount = 0;
  return (st);
}

ham_status_t
RemoteCursor::do_get_record_size(uint64_t *psize)
{
  SerializedWrapper request;
  request.id = kCursorGetRecordSizeRequest;
  request.cursor_get_record_size_request.cursor_handle = m_remote_handle;

  SerializedWrapper reply;
  renv()->perform_request(&request, &reply);
  ham_assert(reply.id == kCursorGetRecordSizeReply);

  ham_status_t st = reply.cursor_get_record_size_reply.status;
  if (st == 0)
    *psize = reply.cursor_get_record_size_reply.size;
  return (0);
}

} // namespace hamsterdb
