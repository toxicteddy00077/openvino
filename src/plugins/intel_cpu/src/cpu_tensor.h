// Copyright (C) 2018-2025 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include <cstddef>
#include <memory>
#include <mutex>

#include "cpu_memory.h"
#include "openvino/core/shape.hpp"
#include "openvino/core/strides.hpp"
#include "openvino/core/type/element_type.hpp"
#include "openvino/runtime/itensor.hpp"

namespace ov::intel_cpu {

class Tensor : public ITensor {
public:
    // Only plain data format is supported.
    explicit Tensor(MemoryPtr memptr);

    void set_shape(ov::Shape shape) override;

    const ov::element::Type& get_element_type() const override;

    const ov::Shape& get_shape() const override;

    size_t get_size() const override;

    size_t get_byte_size() const override;

    const ov::Strides& get_strides() const override;

    void* data() override;
    void* data(const element::Type& type) override;
    const void* data() const override;
    const void* data(const element::Type& type) const override;

    MemoryPtr get_memory() {
        return m_memptr;
    }

private:
    void update_strides() const;

    MemoryPtr m_memptr;

    ov::element::Type m_element_type;
    mutable ov::Shape m_shape;
    mutable ov::Strides m_strides;
    mutable std::mutex m_lock;
};

std::shared_ptr<ITensor> make_tensor(MemoryPtr mem);

}  // namespace ov::intel_cpu
