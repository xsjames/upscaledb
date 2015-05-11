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

/*
 * Test gateway for LsnManager
 *
 * @exception_safe: nothrow
 * @thread_safe: no
 */
 
#ifndef HAM_LSN_MANAGER_TEST_H
#define HAM_LSN_MANAGER_TEST_H

#include "0root/root.h"

#include "2lsn_manager/lsn_manager.h"

#ifndef HAM_ROOT_H
#  error "root.h was not included"
#endif

namespace hamsterdb {

struct LsnManagerTest
{
  // Constructor
  LsnManagerTest(LsnManager *lsn_manager)
    : m_state(lsn_manager->m_state) {
  }

  // Returns the current lsn
  uint64_t lsn() const {
    return (m_state);
  }

  uint64_t &m_state;
};

} // namespace hamsterdb

#endif /* HAM_LSN_MANAGER_TEST_H */
