#ifndef INTEGER_H
#define INTEGER_H

#include <istream>
#include <ostream>
#include <bitset>

template<size_t len>
class Integer
{
public:
    Integer();
    Integer(long long);
    Integer(const Integer&);

    virtual ~Integer();

    inline char toChar();
    inline unsigned char toUChar();
    inline short toShort();
    inline unsigned short toUShort();
    inline int toInt() const;
    inline unsigned int toUInt();
    inline long toLong();
    inline unsigned long toULong();
    inline long long toLongLong();
    inline unsigned long long toULongLong();

    //Integer& operator =(const Integer&);

    template<size_t _len>
    friend std::ostream& operator <<(std::ostream&, const Integer<_len>&);

    template<size_t _len>
    friend std::istream& operator >>(std::istream&, const Integer<_len>&);


    template<size_t _len>
    friend inline bool operator ==(const Integer<_len>&, const Integer<_len>&);

    template<size_t _len>
    friend inline bool operator ==(const Integer<_len>&, const long long&);

    template<size_t _len>
    friend inline bool operator ==(const long long&, const Integer<_len>&);

    template<size_t _len>
    friend inline bool operator !=(const Integer<_len>&, const Integer<_len>&);

    template<size_t _len>
    friend inline bool operator !=(const Integer<_len>&, const long long&);

    template<size_t _len>
    friend inline bool operator !=(const long long&, const Integer<_len>&);

    template<size_t _len>
    friend inline bool operator <(const Integer<_len>&, const Integer<_len>&);

    template<size_t _len>
    friend inline bool operator <(const Integer<_len>&, const long long&);

    template<size_t _len>
    friend inline bool operator <(const long long&, const Integer<_len>&);

    template<size_t _len>
    friend inline bool operator >(const Integer<_len>&, const Integer<_len>&);

    template<size_t _len>
    friend inline bool operator >(const Integer<_len>&, const long long&);

    template<size_t _len>
    friend inline bool operator >(const long long&, const Integer<_len>&);

    template<size_t _len>
    friend inline bool operator <=(const Integer<_len>&, const Integer<_len>&);

    template<size_t _len>
    friend inline bool operator <=(const Integer<_len>&, const long long&);

    template<size_t _len>
    friend inline bool operator <=(const long long&, const Integer<_len>&);

    template<size_t _len>
    friend inline bool operator >=(const Integer<_len>&, const Integer<_len>&);

    template<size_t _len>
    friend inline bool operator >=(const Integer<_len>&, const long long&);

    template<size_t _len>
    friend inline bool operator >=(const long long&, const Integer<_len>&);


    Integer operator -() const;
    Integer operator +() const;

    template<size_t _len>
    friend inline const Integer<_len> operator +(const Integer<_len>&, const Integer<_len>&);

    template<size_t _len>
    friend inline const Integer<_len> operator +(const Integer<_len>&, const long long&);

    template<size_t _len>
    friend inline const Integer<_len> operator+(const long long&, const Integer<_len>&);

    template<size_t _len>
    friend inline const Integer<_len> operator -(const Integer<_len>&, const Integer<_len>&);

    template<size_t _len>
    friend inline const Integer<_len> operator -(const Integer<_len>&, const long long&);

    template<size_t _len>
    friend inline const Integer<_len> operator -(const long long&, const Integer<_len>&);

    Integer operator ++();
    Integer operator ++(int);
    Integer operator --();
    Integer operator --(int);


private:
    Integer(std::bitset<len>);
    std::bitset<len> bits;
    static inline std::bitset<len> sum_bitsets(const std::bitset<len>&, const std::bitset<len>&);
    static inline void to_additional_code(std::bitset<len>&);
};

//idk why but linker doesn't see this in a separate cpp file
//

template<size_t len>
Integer<len>::Integer()
{
    this->bits.reset();
}

template<size_t len>
Integer<len>::Integer(long long num)
{
    bool sign = (num < 0);
    if (num < 0)
        num = -num;

    //setting bits of a number
    this->bits.reset(0);
    for (size_t i = 0; i < len - 1; ++i)
        this->bits[i] = (num & (1 << i)) >> i;

    if (sign)
        Integer<len>::to_additional_code(this->bits);
}

template<size_t len>
Integer<len>::Integer(const Integer &num)
{
    this->bits = num.bits;
}

template<size_t len>
Integer<len>::Integer(std::bitset<len> b)
{
    this->bits = b;
}

template<size_t len>
Integer<len>::~Integer()
{

}

template<size_t len>
inline int Integer<len>::toInt() const
{
    std::bitset<len> temp = this->bits;
    bool sign = temp.test(len - 1);
    if (sign)
        Integer<len>::to_additional_code(temp);

    int ans = 0;
    for (size_t i = 0; i < len; ++i)
        ans += temp.test(i) * (1 << i);

    return sign ? -ans : ans;
}

template <size_t len>
std::ostream& operator <<(std::ostream& os, const Integer<len>& integer)
{
    return os << integer.toInt();
}

template<size_t len>
std::istream& operator >>(std::istream& is, Integer<len>& integer)
{
    long long temp;
    is >> temp;
    integer = temp;
    return is;
}

template<size_t len>
inline bool operator ==(const Integer<len> &a, const Integer<len> &b)
{
    return a.bits == b.bits;
}

template<size_t len>
inline bool operator ==(const Integer<len> &a, const long long &b)
{
    return a.bits == std::bitset<len>(b);
}

template<size_t len>
inline bool operator ==(const long long &a, const Integer<len> &b)
{
    return std::bitset<len>(a) == b.bits;
}

template<size_t len>
inline bool operator !=(const Integer<len> &a, const Integer<len> &b)
{
    return !(a.bits == b.bits);
}

template<size_t len>
inline bool operator !=(const Integer<len> &a, const long long &b)
{
    return !(a.bits == std::bitset<len>(b));
}

template<size_t len>
inline bool operator !=(const long long &a, const Integer<len> &b)
{
    return !(std::bitset<len>(a) == b.bits);
}

template<size_t len>
inline bool operator <(const Integer<len> &a, const Integer<len> &b)
{
    if (!a.bits.test(len - 1) && b.bits.test(len - 1))
        return false;

    if (a.bits.test(len - 1) && !b.bits.test(len - 1))
        return true;

    for (size_t i = len - 1; i != 0; --i)
    {
        if (!a.bits.test(i) && b.bits.test(i))
            return true;

        if (a.bits.test(i) && !b.bits.test(i))
            return false;
    }
    return false;
}

template<size_t len>
inline bool operator <(const Integer<len> &a, const long long &b)
{
    return a < Integer<len>(b);
}

template<size_t len>
inline bool operator <(const long long &a, const Integer<len> &b)
{
    return Integer<len>(a) < b;
}

template<size_t len>
inline bool operator >(const Integer<len> &a, const Integer<len> &b)
{
    if (!a.bits.test(len - 1) && b.bits.test(len - 1))
        return true;

    if (a.bits.test(len - 1) && !b.bits.test(len - 1))
        return false;

    for (size_t i = len - 1; i != 0; --i)
    {
        if (!a.bits.test(i) && b.bits.test(i))
            return false;

        if (a.bits.test(i) && !b.bits.test(i))
            return true;
    }
    return false;
}

template<size_t len>
inline bool operator >(const Integer<len> &a, const long long &b)
{
    return a > Integer<len>(b);
}

template<size_t len>
inline bool operator >(const long long &a, const Integer<len> &b)
{
    return Integer<len>(a) > b;
}

template<size_t len>
inline bool operator <=(const Integer<len> &a, const Integer<len> &b)
{
    return !(a > b);
}

template<size_t len>
inline bool operator <=(const Integer<len> &a, const long long &b)
{
    return !(a > Integer<len>(b));
}

template<size_t len>
inline bool operator <=(const long long &a, const Integer<len> &b)
{
    return !(Integer<len>(a) > b);
}

template<size_t len>
inline bool operator >=(const Integer<len> &a, const Integer<len> &b)
{
    return !(a < b);
}

template<size_t len>
inline bool operator >=(const Integer<len> &a, const long long &b)
{
    return !(a < Integer<len>(b));
}

template<size_t len>
inline bool operator >=(const long long &a, const Integer<len> &b)
{
    return !(Integer<len>(a) < b);
}

/*
template<size_t len>
Integer<len>& Integer<len>::operator =(const Integer &num)
{
    this->bits = num.bits;
    return *this;
}
*/
template<size_t len>
Integer<len> Integer<len>::operator -() const
{
    std::bitset<len> temp = this->bits;
    to_additional_code(temp);
    return Integer(temp);
}

template<size_t len>
Integer<len> Integer<len>::operator +() const
{
    return *this;
}

template<size_t len>
inline const Integer<len> operator +(const Integer<len> &a, const Integer<len> &b)
{
    return Integer<len>(Integer<len>::sum_bitsets(a.bits, b.bits));
}

template<size_t len>
inline const Integer<len> operator +(const Integer<len> &a, const long long &b)
{
    return a + Integer<len>(b);
}

template<size_t len>
inline const Integer<len> operator +(const long long &a, const Integer<len> &b)
{
    return Integer<len>(a) + b;
}

template<size_t len>
inline const Integer<len> operator -(const Integer<len> &a, const Integer<len> &b)
{
    std::bitset<len> b_temp = b.bits;
    Integer<len>::to_additional_code(b_temp);
    return Integer<len>(Integer<len>::sum_bitsets(a.bits, b_temp));
}

template<size_t len>
inline const Integer<len> operator -(const Integer<len> &a, const long long &b)
{
    return a - Integer<len>(b);
}

template<size_t len>
inline const Integer<len> operator -(const long long &a, const Integer<len> &b)
{
    return Integer<len>(a) - b;
}

template<size_t len>
Integer<len> Integer<len>::operator ++()
{
    for (size_t i = 0; i < len; ++i)
    {
        if (!this->bits[i])
        {
            this->bits.set(i);
            break;
        }
        this->bits.reset(i);
    }
    return *this;
}

template<size_t len>
Integer<len> Integer<len>::operator ++(int)
{
    Integer<len> old_value = *this;
    ++*this;
    return old_value;
}

template<size_t len>
Integer<len> Integer<len>::operator --()
{
    *this = *this + Integer<len>(-1);
    return *this;
}

template<size_t len>
Integer<len> Integer<len>::operator --(int)
{
    Integer<len> old_value = *this;
    *this = *this + Integer<len>(-1);
    return old_value;
}

template <size_t len>
std::bitset<len> Integer<len>::sum_bitsets(const std::bitset<len> &b1, const std::bitset<len> &b2)
{
    std::bitset<len> ans;
    bool add = 0;
    for (size_t i = 0; i < len; ++i)
    {
        ans[i] = b1[i] ^ b2[i] ^ add;
        add = ((b1[i] & b2[i]) | (b1[i] & add) | (b2[i] & add));
    }
    return ans;
}

template<size_t len>
inline void Integer<len>::to_additional_code(std::bitset<len> &b)
{
    b.flip();

    //adding 0x1
    for (size_t i = 0; i < len; ++i)
    {
        if (!b[i])
        {
            b.set(i);
            break;
        }
        b.reset(i);
    }
}

#endif // INTEGER_H
