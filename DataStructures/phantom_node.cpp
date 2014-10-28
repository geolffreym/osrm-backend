/*

Copyright (c) 2013, Project OSRM, Dennis Luxen, others
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list
of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this
list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "phantom_node.hpp"

PhantomNode::PhantomNode(NodeID forward_node_id, NodeID reverse_node_id, unsigned name_id,
            int forward_weight, int reverse_weight, int forward_offset, int reverse_offset,
            unsigned packed_geometry_id, FixedPointCoordinate &location,
            unsigned short fwd_segment_position,
            TravelMode forward_travel_mode, TravelMode backward_travel_mode) :
    forward_node_id(forward_node_id),
    reverse_node_id(reverse_node_id),
    name_id(name_id),
    forward_weight(forward_weight),
    reverse_weight(reverse_weight),
    forward_offset(forward_offset),
    reverse_offset(reverse_offset),
    packed_geometry_id(packed_geometry_id),
    location(location),
    fwd_segment_position(fwd_segment_position),
    forward_travel_mode(forward_travel_mode),
    backward_travel_mode(backward_travel_mode)
{ }

PhantomNode::PhantomNode() :
    forward_node_id(SPECIAL_NODEID),
    reverse_node_id(SPECIAL_NODEID),
    name_id(std::numeric_limits<unsigned>::max()),
    forward_weight(INVALID_EDGE_WEIGHT),
    reverse_weight(INVALID_EDGE_WEIGHT),
    forward_offset(0),
    reverse_offset(0),
    packed_geometry_id(SPECIAL_EDGEID),
    fwd_segment_position(0),
    forward_travel_mode(TRAVEL_MODE_INACCESSIBLE),
    backward_travel_mode(TRAVEL_MODE_INACCESSIBLE)
{ }

int PhantomNode::GetForwardWeightPlusOffset() const
{
    if (SPECIAL_NODEID == forward_node_id)
    {
        return 0;
    }
    return forward_offset + forward_weight;
}

int PhantomNode::GetReverseWeightPlusOffset() const
{
    if (SPECIAL_NODEID == reverse_node_id)
    {
        return 0;
    }
    return reverse_offset + reverse_weight;
}

bool PhantomNode::isBidirected() const
{
    return (forward_node_id != SPECIAL_NODEID) &&
           (reverse_node_id != SPECIAL_NODEID);
}

bool PhantomNode::IsCompressed() const
{
    return (forward_offset != 0) || (reverse_offset != 0);
}

bool PhantomNode::isValid(const unsigned numberOfNodes) const
{
    return
        location.isValid() &&
        (
            (forward_node_id < numberOfNodes) ||
            (reverse_node_id < numberOfNodes)
        ) &&
        (
            (forward_weight != INVALID_EDGE_WEIGHT) ||
            (reverse_weight != INVALID_EDGE_WEIGHT)
        ) &&
        (name_id != std::numeric_limits<unsigned>::max()
    );
}

bool PhantomNode::isValid() const
{
    return location.isValid() &&
           (name_id != std::numeric_limits<unsigned>::max());
}

bool PhantomNode::operator==(const PhantomNode & other) const
{
    return location == other.location;
}