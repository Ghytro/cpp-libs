#ifndef INTEGER_H
#define INTEGER_H

#include <iostream>
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

    inline char toChar() const;
    inline unsigned char toUChar() const;
    inline short toShort() const;
    inline unsigned short toUShort() const;
    inline int toInt() const;
    inline unsigned int toUInt() const;
    inline long toLong() const;
    inline unsigned long toULong() const;
    inline long long toLongLong() const;
    inline unsigned long long toULongLong() const;
    inline std::string toString() const;

    Integer& operator =(const Integer&);
    Integer& operator =(const long long&);

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
    friend inline const Integer<_len> operator +(const long long&, const Integer<_len>&);

    template<size_t _len>
    friend inline const Integer<_len> operator -(const Integer<_len>&, const Integer<_len>&);

    template<size_t _len>
    friend inline const Integer<_len> operator -(const Integer<_len>&, const long long&);

    template<size_t _len>
    friend inline const Integer<_len> operator -(const long long&, const Integer<_len>&);

    template<size_t _len>
    friend inline const Integer<_len> operator *(const Integer<_len>&, const Integer<_len>&);

    template<size_t _len>
    friend inline const Integer<_len> operator *(const Integer<_len>&, const long long&);

    template<size_t _len>
    friend inline const Integer<_len> operator *(const long long&, const Integer<_len>&);

    template<size_t _len>
    friend inline const Integer<_len> operator /(const Integer<_len>&, const Integer<_len>&);

    template<size_t _len>
    friend inline const Integer<_len> operator /(const Integer<_len>&, const long long&);

    template<size_t _len>
    friend inline const Integer<_len> operator /(const long long&, const Integer<_len>&);

    template<size_t _len>
    friend inline const Integer<_len> operator %(const Integer<_len>&, const Integer<_len>&);

    template<size_t _len>
    friend inline const Integer<_len> operator %(const Integer<_len>&, const long long&);

    template<size_t _len>
    friend inline const Integer<_len> operator %(const long long&, const Integer<_len>&);




    template<size_t _len>
    friend inline const Integer<_len> operator &(const Integer<_len>&, const Integer<_len>&);

    template<size_t _len>
    friend inline const Integer<_len> operator &(const Integer<_len>&, const long long&);

    template<size_t _len>
    friend inline const Integer<_len> operator &(const long long&, const Integer<_len>&);

    template<size_t _len>
    friend inline const Integer<_len> operator |(const Integer<_len>&, const Integer<_len>&);

    template<size_t _len>
    friend inline const Integer<_len> operator |(const Integer<_len>&, const long long&);

    template<size_t _len>
    friend inline const Integer<_len> operator |(const long long&, const Integer<_len>&);

    template<size_t _len>
    friend inline const Integer<_len> operator ^(const Integer<_len>&, const Integer<_len>&);

    template<size_t _len>
    friend inline const Integer<_len> operator ^(const Integer<_len>&, const long long&);

    template<size_t _len>
    friend inline const Integer<_len> operator ^(const long long&, const Integer<_len>&);

    template<size_t _len>
    friend inline const Integer<_len> operator <<(const Integer<_len>&, const size_t&);

    template<size_t _len>
    friend inline const Integer<_len> operator >>(const Integer<_len>&, const size_t&);

    Integer operator ++();
    Integer operator ++(int);
    Integer operator --();
    Integer operator --(int);


private:
    Integer(std::bitset<len>);

    std::bitset<len> bits;

    static inline std::bitset<len> sum_bitsets(const std::bitset<len>&, const std::bitset<len>&);
    static inline std::bitset<len> mult_bitsets(const std::bitset<len>&, const std::bitset<len>&);
    static inline std::bitset<len> div_bitsets(const std::bitset<len>&, const std::bitset<len>&);
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
    size_t minlen = (len > 64) ? 64 : len;
    for (size_t i = 0; i < minlen - 1; ++i)
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
inline char Integer<len>::toChar() const
{
    std::bitset<len> temp = this->bits;
    bool sign = temp.test(len - 1);
    if (sign)
        Integer<len>::to_additional_code(temp);

    char ans = 0;
    for (size_t i = 0; i < len - 1; ++i)
        ans += temp.test(i) * (1 << i);

    return sign ? -ans : ans;
}

template<size_t len>
inline unsigned char Integer<len>::toUChar() const
{
    unsigned char ans = 0;
    for (size_t i = 0; i < len; ++i)
        ans += this->bits.test(i) * (1 << i);
    return ans;
}

template<size_t len>
inline short Integer<len>::toShort() const
{
    std::bitset<len> temp = this->bits;
    bool sign = temp.test(len - 1);
    if (sign)
        Integer<len>::to_additional_code(temp);

    short ans = 0;
    for (size_t i = 0; i < len - 1; ++i)
        ans += temp.test(i) * (1 << i);

    return sign ? -ans : ans;
}

template<size_t len>
inline unsigned short Integer<len>::toUShort() const
{
    unsigned short ans = 0;
    for (size_t i = 0; i < len; ++i)
        ans += this->bits.test(i) * (1 << i);
    return ans;
}

template<size_t len>
inline int Integer<len>::toInt() const
{
    std::bitset<len> temp = this->bits;
    bool sign = temp.test(len - 1);
    if (sign)
        Integer<len>::to_additional_code(temp);

    int ans = 0;
    for (size_t i = 0; i < len - 1; ++i)
        ans += temp.test(i) * (1 << i);

    return sign ? -ans : ans;
}

template<size_t len>
inline unsigned int Integer<len>::toUInt() const
{
    unsigned int ans = 0;
    for (size_t i = 0; i < len; ++i)
        ans += this->bits.test(i) * (1 << i);

    return ans;
}

template<size_t len>
inline long Integer<len>::toLong() const
{
    std::bitset<len> temp = this->bits;
    bool sign = temp.test(len - 1);
    if (sign)
        Integer<len>::to_additional_code(temp);

    long ans = 0;
    for (size_t i = 0; i < len - 1; ++i)
        ans += temp.test(i) * (1 << i);

    return sign ? -ans : ans;
}

template<size_t len>
inline unsigned long Integer<len>::toULong() const
{
    unsigned long ans = 0;
    for (size_t i = 0; i < len; ++i)
        ans += this->bits.test(i) * (1 << i);

    return ans;
}

template<size_t len>
inline long long Integer<len>::toLongLong() const
{
    std::bitset<len> temp = this->bits;
    bool sign = temp.test(len - 1);
    if (sign)
        Integer<len>::to_additional_code(temp);

    long long ans = 0;
    for (size_t i = 0; i < len - 1; ++i)
        ans += temp.test(i) * (1 << i);

    return sign ? -ans : ans;
}

template<size_t len>
inline unsigned long long Integer<len>::toULongLong() const
{
    unsigned long long ans = 0;
    for (size_t i = 0; i < len; ++i)
        ans += this->bits.test(i) * (1 << i);

    return ans;
}

template<size_t len>
inline std::string Integer<len>::toString() const
{
    Integer<len> temp(this->bits);
    //std::cout << this->bits;
    std::string ans;
    while (temp > 0)
    {

        ans += (temp % 10).toChar() + '0';
        temp = temp / 10;
        //std::cout << temp << std::endl;
    }
    //std::cout << "here";
    for (size_t i = 0; i < ans.length() / 2; ++i)
    {
        char buf = ans[i];
        ans[i] = ans[ans.length() - 1 - i];
        ans[ans.length() - 1 - i] = buf;
    }
    //std::cout << "here";
    return ans;
}

template <size_t len>
std::ostream& operator <<(std::ostream& os, const Integer<len>& integer)
{

    return os << integer.toString();
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

    if (a.bits.test(len - 1))
    {
        std::bitset<len> num1 = a.bits, num2 = b.bits;
        Integer<len>::to_additional_code(num1);
        Integer<len>::to_additional_code(num2);
        return Integer<len>(num1) > Integer<len>(num2);
    }

    for (size_t i = len - 1; ; --i)
    {
        if (!a.bits.test(i) && b.bits.test(i))
            return true;

        if (a.bits.test(i) && !b.bits.test(i))
            return false;

        if (i == 0)
            break;
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

    if (a.bits.test(len - 1))
    {
        std::bitset<len> num1 = a.bits, num2 = b.bits;
        Integer<len>::to_additional_code(num1);
        Integer<len>::to_additional_code(num2);
        return Integer<len>(num1) < Integer<len>(num2);
    }

    for (size_t i = len - 1; ; --i)
    {
        if (!a.bits.test(i) && b.bits.test(i))
            return false;

        if (a.bits.test(i) && !b.bits.test(i))
            return true;

        if (i == 0)
            break;
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


template<size_t len>
Integer<len>& Integer<len>::operator =(const Integer &num)
{
    this->bits = num.bits;
    return *this;
}

template<size_t len>
Integer<len>& Integer<len>::operator =(const long long &num)
{
    *this = Integer<len>(num);
    return *this;
}

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
inline const Integer<len> operator *(const Integer<len> &a, const Integer<len> &b)
{
    return Integer<len>(Integer<len>::mult_bitsets(a.bits, b.bits));
}

template<size_t len>
inline const Integer<len> operator *(const Integer<len> &a, const long long &b)
{
    return a * Integer<len>(b);
}

template<size_t len>
inline const Integer<len> operator *(const long long &a, const Integer<len> &b)
{
    return Integer<len>(a) * b;
}

template<size_t len>
inline const Integer<len> operator /(const Integer<len> &a, const Integer<len> &b)
{
    return Integer<len>(Integer<len>::div_bitsets(a.bits, b.bits));
}

template<size_t len>
inline const Integer<len> operator /(const Integer<len> &a, const long long &b)
{
    return a / Integer<len>(b);
}

template<size_t len>
inline const Integer<len> operator /(const long long &a, const Integer<len> &b)
{
    return Integer<len>(a) / b;
}

template<size_t len>
inline const Integer<len> operator %(const Integer<len> &a, const Integer<len> &b)
{
    return a - (b * (a / b));
}

template<size_t len>
inline const Integer<len> operator %(const Integer<len> &a, const long long &b)
{
    return a % Integer<len>(b);
}

template<size_t len>
inline const Integer<len> operator %(const long long &a, const Integer<len> &b)
{
    return Integer<len>(a) % b;
}

template<size_t len>
inline const Integer<len> operator &(const Integer<len> &a, const Integer<len> &b)
{
    return Integer<len>(a.bits & b.bits);
}

template<size_t len>
inline const Integer<len> operator &(const Integer<len> &a, const long long &b)
{
    return a & Integer<len>(b);
}

template<size_t len>
inline const Integer<len> operator &(const long long &a, const Integer<len> &b)
{
    return Integer<len>(a) & b;
}

template<size_t len>
inline const Integer<len> operator |(const Integer<len> &a, const Integer<len> &b)
{
    return Integer<len>(a.bits | b.bits);
}

template<size_t len>
inline const Integer<len> operator |(const Integer<len> &a, const long long &b)
{
    return a | Integer<len>(b);
}

template<size_t len>
inline const Integer<len> operator |(const long long &a, const Integer<len> &b)
{
    return Integer<len>(a) | b;
}

template<size_t len>
inline const Integer<len> operator ^(const Integer<len> &a, const Integer<len> &b)
{
    return Integer<len>(a.bits ^ b.bits);
}

template<size_t len>
inline const Integer<len> operator ^(const Integer<len> &a, const long long &b)
{
    return a ^ Integer<len>(b);
}

template<size_t len>
inline const Integer<len> operator ^(const long long &a, const Integer<len> &b)
{
    return Integer<len>(a) ^ b;
}

template<size_t len>
inline const Integer<len> operator <<(const Integer<len> &a, const size_t &b)
{
    return Integer<len>(a.bits << b);
}

template<size_t len>
inline const Integer<len> operator >>(const Integer<len> &a, const size_t &b)
{
    return Integer<len>(a.bits >> b);
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
inline std::bitset<len> Integer<len>::sum_bitsets(const std::bitset<len> &b1, const std::bitset<len> &b2)
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
inline std::bitset<len> Integer<len>::div_bitsets(const std::bitset<len> &b1, const std::bitset<len> &b2)
{
    if (b1 == std::bitset<len>())
        return std::bitset<len>();

    auto findSeniorDigit = [](const std::bitset<len>& b)
    {
        for (size_t i = len - 1; ; --i)
        {
            if (b.test(i))
                return i;

            if (i == 0)
                break;
        }
        return std::string::npos;
    };

    std::bitset<len> a = b1, b = b2;

    bool sign = a.test(len - 1) ^ b.test(len - 1);

    if (a.test(len - 1))
        Integer<len>::to_additional_code(a);

    if (b.test(len - 1))
        Integer<len>::to_additional_code(b);

    if (Integer<len>(a) < Integer<len>(b))
        return std::bitset<len>();

    const size_t d1 = findSeniorDigit(a), d2 = findSeniorDigit(b);

    if (d1 < d2)
        return std::bitset<len>();

    std::bitset<len> temp_b = b << (d1 - d2);
    std::bitset<len> add_b = temp_b;

    Integer<len>::to_additional_code(add_b);

    std::bitset<len> mod = Integer<len>::sum_bitsets(a, add_b);

    std::bitset<len> ans;
    bool mod_sign = mod.test(len - 1);
    size_t ind = d1 - d2;
    ans[ind--] = !mod_sign;
    //std::cout << mod << std::endl;
    //std::cout << "to ans written: " << !mod_sign << std::endl;

    for (size_t i = 0; i < d1 - d2; ++i)
    {
        /*
        if ((Integer<len>(mod) >= 0 && Integer<len>(mod) < Integer<len>(b)) || (Integer<len>(mod) < 0 && Integer<len>(mod) > -Integer<len>(b)))
        {
            std::cout << "broken" << std::endl;
            std::cout << Integer<len>(mod) << " " << Integer<len>(b) << std::endl;
            //ans >>= d1 - d2 - i;
            break;
        }
        */

        mod <<= 1;
        mod[len - 1] = mod_sign;

        if (mod.test(len - 1))
            mod = Integer<len>::sum_bitsets(mod, temp_b);
        else
            mod = Integer<len>::sum_bitsets(mod, add_b);

        //std::cout << mod << std::endl;

        mod_sign = mod.test(len - 1);
        ans[ind--] = !mod_sign;
        //std::cout << ans << std::endl;
        //std::cout << "to ans written: " << !mod_sign << std::endl;
    }
    //std::cout << ans << std::endl;
    if (sign)
        Integer<len>::to_additional_code(ans);
    return ans;
}

template<size_t len>
inline std::bitset<len> Integer<len>::mult_bitsets(const std::bitset<len> &b1, const std::bitset<len>& b2)
{
    std::bitset<len> a = b1, b = b2, ans;
    bool sign = a.test(len - 1) ^ b.test(len - 1);

    if (a.test(len - 1))
        Integer<len>::to_additional_code(a);

    if (b.test(len - 1))
        Integer<len>::to_additional_code(b);

    for (size_t i = 0; i < len - 1; ++i)
        if (a.test(i))
            ans = Integer<len>::sum_bitsets(ans, b << i);

    if (sign)
        Integer<len>::to_additional_code(ans);

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
