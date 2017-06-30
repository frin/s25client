// Copyright (c) 2017 - 2017 Settlers Freaks (sf-team at siedler25.org)
//
// This file is part of Return To The Roots.
//
// Return To The Roots is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Return To The Roots is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Return To The Roots. If not, see <http://www.gnu.org/licenses/>.

#ifndef XorShift_h__
#define XorShift_h__

#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <stdint.h>
#include <iosfwd>

class Serializer;

/// XorShift64* RNG according to http://vigna.di.unimi.it/ftp/papers/xorshift.pdf
class XorShift
{
public:
    typedef uint64_t return_type;

    static return_type min() { return 1; }
    static return_type max() { return UINT64_MAX; }

    XorShift() { seed(); }
    explicit XorShift(unsigned initSeed) { seed(initSeed); }
    template<class T_SeedSeq>
    explicit XorShift(T_SeedSeq& seedSeq, typename boost::disable_if<boost::is_integral<T_SeedSeq> >::type* dummy = 0) { seed(seedSeq); }

    void seed() { seed(0x1337); }
    void seed(uint64_t newSeed);
    template<class T_SeedSeq>
    void seed(T_SeedSeq& seedSeq, typename boost::disable_if<boost::is_integral<T_SeedSeq> >::type* dummy = 0);

    /// Return random value in [min, max]
    return_type operator()();
    /// Return random value in [0, maxVal] for a small maxVal
    unsigned operator()(unsigned maxVal);

    void discard(uint64_t j);

    void Serialize(Serializer& ser) const;
    void Deserialize(Serializer& ser);

private:
    friend std::ostream& operator<<(std::ostream& os, const XorShift& obj);
    friend std::istream& operator>>(std::istream& is, XorShift& obj);
    friend bool operator==(const XorShift& lhs, const XorShift& rhs){ return lhs.state_ == rhs.state_; }
    friend bool operator!=(const XorShift& lhs, const XorShift& rhs){ return !(lhs == rhs); }

    uint64_t state_;
};

template<class T_SeedSeq>
inline void XorShift::seed(T_SeedSeq& seedSeq, typename boost::disable_if<boost::is_integral<T_SeedSeq> >::type*)
{
    unsigned seeds[2];
    seedSeq.generate(&seeds[0], &seeds[1]);
    seed(*static_cast<uint64_t*>(seeds));
}

inline XorShift::return_type XorShift::operator()()
{
    state_ ^= state_ >> 12; // a
    state_ ^= state_ << 25; // b
    state_ ^= state_ >> 27; // c
    return state_ * UINT64_C(2685821657736338717);
}

inline unsigned XorShift::operator()(unsigned maxVal)
{
    uint64_t value = (*this)() - 1;
    return static_cast<unsigned>(value % (maxVal + 1));
}

#endif // XorShift_h__
