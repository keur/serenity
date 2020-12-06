/*
 * Copyright (c) 2020, the SerenityOS developers.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <AK/RefCounted.h>
#include <LibWeb/Bindings/Wrappable.h>

namespace Web::DOM {

class Range final
    : public RefCounted<Range>
    , public Bindings::Wrappable {
public:
    // using WrapperType = Bindings::RangeWrapper;

    static NonnullRefPtr<Range> create(Document& document)
    {
        return adopt(*new Range(document));
    }
    static NonnullRefPtr<Range> create(Node& start_container, size_t start_offset, Node& end_container, size_t end_offset)
    {
        return adopt(*new Range(start_container, start_offset, end_container, end_offset));
    }

    Node* start_container() { return m_start_container; }
    unsigned start_offset() { return m_start_offset; }

    Node* end_container() { return m_end_container; }
    unsigned end_offset() { return m_end_offset; }

    bool collapsed()
    {
        return start_container() == end_container() && start_offset() == end_offset();
    }

    void set_start(Node& container, JS::Value& offset)
    {
        m_start_container = container;
        m_start_offset = (unsigned)offset.as_i32();
    }

    void set_end(Node& container, JS::Value& offset)
    {
        m_end_container = container;
        m_end_offset = (unsigned)offset.as_i32();
    }

    NonnullRefPtr<Range> inverted() const;
    NonnullRefPtr<Range> normalized() const;
    NonnullRefPtr<Range> clone_range() const;

private:
    explicit Range(Document&);
    Range(Node& start_container, size_t start_offset, Node& end_container, size_t end_offset);

    NonnullRefPtr<Node> m_start_container;
    unsigned m_start_offset;

    NonnullRefPtr<Node> m_end_container;
    unsigned m_end_offset;
};

}