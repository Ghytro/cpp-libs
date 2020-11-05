









//   /******************************************************************/
//  /******************************************************************/ |
// /******************************************************************///|
  /******************************************************************////|
 /******************************************************************/////|
/**                                                              **//////|
/**         BIGINTCPP - БИБЛИОТЕКА БОЛЬШИХ ЧИСЕЛ ДЛЯ C++         **//////|
/**         VERSION: 1.0                                         **//////|
/**         RELEASE DATE: 20.07.2019                             **//////|
/**         COPYRIGHT: (C) MIKHAIL KOROBKOV                      **//////|
/**                                                              **//////|
/**         DESCRIPTION: ДАННАЯ БИБЛИОТЕКА ПРЕДНАЗНАЧЕНА ДЛЯ     **//////|
/**         РАБОТЫ С БОЛЬШИМИ ЗНАКОВЫМИ ЦЕЛЫМИ ЧИСЛАМИ,          **//////|
/**         ВЫХОДЯЩИМИ ЗА ПРЕДЕЛЫ ЗНАЧЕНИЙ ТИПА "long long".     **//////|
/**         ЕДИНСТВЕННОЕ ОГРАНИЧЕНИЕ, НАКЛАДЫВАЕМОЕ НА           **//////|
/**         МАКСИМАЛЬНОЕ ЗНАЧЕНИЕ ДАННЫХ ЧИСЕЛ ЗАВИСИТ ОТ        **//////|
/**         ОГРАНИЧЕНИЙ, НАКЛАДЫВАЕМЫХ ВАШЕЙ СИСТЕМОЙ.           **//////|
/**         ВО ВСЕМ ОСТАЛЬНОМ ДАННЫЙ ТИП МАКСИМАЛЬНО ПРИБЛИЖЕН   **//////|
/**         К СТАНДАРТНЫМ ТИПАМ ЦЕЛЫХ ЧИСЕЛ C И C++ И СПОСОБЕН   **//////|
/**         С НИМИ ВЗАИМОДЕЙСТВОВАТЬ.                            **//////|
/**                                                              **//////|
/**         СО ВСЕМИ ПРЕДЛОЖЕНИЯМИ И НАЙДЕННЫМИ БАГАМИ           **//////|
/**         ОБРАЩАТЬСЯ ПО EMAIL.                                 **//////|
/**                                                              **//////
/**         EMAIL: korobkov200364@gmail.com                      **/////
/**                                                              **////
///****************************************************************/ /
/*******************************************************************/











#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Bigint;

/**
 *  @brief Объявление функций преобразования типов данных в Bigint.
 *  @ingroup Преобразования.
 *  @param  num      Число, которое нужно преобразовать в Bigint.
 *  @return   Число Bigint с заданным значением.
 *
*/

Bigint itoBI(int num);
Bigint ltoBI(long num);
Bigint lltoBI(long long num);
Bigint strtoBI(string s);

/**
 *  @brief Объявление функций преобразования Bigint в другие типы данных.
 *  @ingroup Преобразования
 *  @param  num     Число, которое нужно преобразовать.
 *  @return Число Bigint со значением num.
 *  @note Есть смысл только в преобразованиях в string и const char*,
 *        так как если преобразовывать слишком большое число в long long
 *        или другой стандартный целочисленный тип С++, может произойти
 *        выход за допустимые границы памяти, выделенной под число.
*/

string BItostr(Bigint num);
const char* BItocchar(Bigint num);

class Bigint
{
private:
    string value;
public:

    /**
     *  @brief Объявление всех конструкторов класса.
     *  @ingroup Конструкторы
     *  @param  num      Число, которое присваивается объекту Bigint.
     *
    */

    Bigint(string num);
    Bigint(long long num);
    Bigint();

    string getstrvalue();

    Bigint& operator =(const Bigint& num)
    {
        value = num.value;
        return *this;
    }

    Bigint& operator =(const long long& num)
    {
        value = to_string(num);
        return *this;
    }

    Bigint& operator =(const char* num)
    {
        value = num;
        return *this;
    }



    friend ostream& operator <<(ostream& os, const Bigint& num);
    friend istream& operator >>(istream& is, const Bigint& num);

    /**
     *  @brief Объявление всех операций сравнения,
     *  выполняемых при помощи операторов.
     *  @ingroup Арифметические алгоритмы
     *  @param  left     Значение слева от бинарного оператора.
     *  @param  right    Значение справа от бинарного оператора.
     *  @param  num      Число, к которому применяется унарный оператор.
     *  @return          Во всех случаях возвращается bool.
     *
    */

    friend bool operator ==(const Bigint& left, const Bigint& right);
    friend bool operator ==(const Bigint& left, const long long& right);
    friend bool operator !=(const Bigint& left, const Bigint& right);
    friend bool operator !=(const Bigint& left, const long long& right);
    friend bool operator <(const Bigint& left, const Bigint& right);
    friend bool operator <(const Bigint& left, const long long& right);
    friend bool operator >(const Bigint& left, const Bigint& right);
    friend bool operator >(const Bigint& left, const long long& right);
    friend bool operator <=(const Bigint& left, const Bigint& right);
    friend bool operator <=(const Bigint& left, const long long& right);
    friend bool operator >=(const Bigint& left, const Bigint& right);
    friend bool operator >=(const Bigint& left, const long long& right);

    /**
     *  @brief Объявление всех арифметических операций,
     *  выполняемых при помощи операторов.
     *  @ingroup Арифметические алгоритмы
     *  @param  left     Значение слева от бинарного оператора.
     *  @param  right    Значение справа от бинарного оператора.
     *  @param  num      Число, к которому применяется унарный оператор.
     *  @return          Во всех случаях возвращается Bigint&.
     *
     *  @note Оператор, объявленный в строке 113 - нерабочий
     *  (Segmentation fault). При вводе пользоваться только конструктором.
    */

    //операции сложения
    //
    friend const Bigint operator +(const Bigint& left, const Bigint& right);
    friend const Bigint operator +(const Bigint& left, const long long& right);
    friend const Bigint operator +(const long long& left, const Bigint& right);
    friend Bigint& operator +=(Bigint& left, const Bigint& right);
    friend Bigint& operator +=(Bigint& left, const long long& right);
    friend const Bigint& operator ++(Bigint& num);
    friend const Bigint& operator ++(Bigint& num, int);

    //операции вычитания
    //
    friend const Bigint operator -(const Bigint& left, const Bigint& right);
    friend const Bigint operator -(const Bigint& left, const long long& right);
    friend const Bigint operator -(const long long& left, const Bigint& right);
    friend const Bigint operator -(const Bigint& num)
    {
        return Bigint("-" + num.value);
    }
    friend Bigint& operator -=(Bigint& left, const Bigint& right);
    friend Bigint& operator -=(Bigint& left, const long long& right);
    friend const Bigint& operator --(Bigint &num);
    friend const Bigint& operator --(Bigint &num, int);

    //операции умножения
    //
    friend const Bigint operator *(const Bigint& left, const Bigint& right);
    friend const Bigint operator *(const Bigint& left, const long long& right);
    friend const Bigint operator *(const long long& left, const Bigint& right);
    friend Bigint& operator *= (Bigint& left, const Bigint& right);
    friend Bigint& operator *=(Bigint& left, const long long& right);

    //операции целочисленного деления
    //
    friend const Bigint operator /(const Bigint& left, const Bigint& right);
    friend const Bigint operator /(const Bigint& left, const long long& right);
    friend const Bigint operator /(const long long& left, const Bigint& right);
    friend Bigint& operator /=(Bigint& left, const Bigint& right);
    friend Bigint& operator /=(Bigint& left, const long long& right);

    //операции взятия остатка
    //
    friend const Bigint operator %(const Bigint& left, const Bigint& right);
    friend const Bigint operator %(const Bigint& left, const long long& right);
    friend const Bigint operator %(const long long& left, const Bigint& right);
    friend Bigint& operator %= (Bigint& left, const Bigint& right);
    friend Bigint& operator %=(Bigint& left, const long long& right);

    //операции возведения в степень
    //
    friend const Bigint operator ^(const Bigint& left, const Bigint& right);
    friend const Bigint operator ^(const Bigint& left, const long long& right);
    friend Bigint& operator ^=(Bigint& left, const Bigint& right);
    friend Bigint& operator ^=(Bigint& left, const long long& right);
};

/**
 *  @brief Реализация всех конструкторов класса.
 *  @ingroup Конструкторы
 *  @param  num      Число, которое присваивается объекту Bigint.
 *
*/

Bigint::Bigint(string num)
{
    while (*(num.begin()) == '0')
        num.erase(0, 1);
    if (num.length() == 0)
        num = "0";
    Bigint::value = num;
}

Bigint::Bigint(long long num)
{
    string snum = to_string(num);
    while (*(snum.begin()) == '0')
        snum.erase(0, 1);
    if (snum.length() == 0)
        snum = "0";
    Bigint::value = snum;
}

Bigint::Bigint()
{
    Bigint::value = "0";
}

string Bigint::getstrvalue()
{
    return Bigint::value;
}

ostream& operator <<(ostream& os, const Bigint& num)
{
    os << num.value;
    return os;
}

istream& operator >>(istream& is, const Bigint& num)
{
    is >> num.value;
    return is;
}

/**
 *  @brief Реализация всех операций сравнения,
 *  выполняемых при помощи операторов.
 *  @ingroup Арифметические алгоритмы
 *  @param  left     Значение слева от бинарного оператора.
 *  @param  right    Значение справа от бинарного оператора.
 *  @param  num      Число, к которому применяется унарный оператор.
 *  @return          Во всех случаях возвращается bool.
 *
*/

bool operator ==(const Bigint& left, const Bigint& right)
{
    return (left.value == right.value);
}

bool operator ==(const Bigint& left, const long long& right)
{
    return (left.value == to_string(right));
}

 bool operator !=(const Bigint& left, const Bigint& right)
{
    return !(left == right);
}

bool operator !=(const Bigint& left, const long long& right)
{
    return !(left == lltoBI(right));
}

bool operator <(const Bigint& left, const Bigint& right)
{
    string lv = left.value, rv = right.value;
    if (*(lv.begin()) == '-')
    {

        if (*(rv.begin()) == '-')
        {

            lv.erase(0, 1);
            rv.erase(0, 1);
            return lv > rv;
        }
        else
            return true;
    }
    if (*(rv.begin()) == '-')
        return false;
    if (lv.length() < rv.length())
        return true;
    if (lv.length() > rv.length())
        return false;
    bool ans = false;
    for (string::iterator i1 = lv.begin(), i2 = rv.begin(); i1 != lv.end(); i1++, i2++)
    {
        if (*i1 > *i2)
            break;
        if (*i1 < *i2)
        {
            ans = true;
            break;
        }
    }
    return ans;
}

bool operator <(const Bigint& left, const long long& right)
{
    return left < lltoBI(right);
}

bool operator >(const Bigint& left, const Bigint& right)
{
    string lv = left.value, rv = right.value;
    if (*(lv.begin()) == '-')
    {
        if (*(rv.begin()) == '-')
        {
            lv.erase(0, 1);
            rv.erase(0, 1);
            return lv < rv;
        }
        else
            return true;
    }
    if (lv.length() > rv.length())
        return true;
    if (lv.length() < rv.length())
        return false;
    bool ans = false;
    for (string::iterator i1 = lv.begin(), i2 = rv.begin(); i1 != lv.end(); i1++, i2++)
    {
        if (*i1 < *i2)
            break;
        if (*i1 > *i2)
        {
            ans = true;
            break;
        }
    }
    return ans;
}

bool operator >(const Bigint& left, const long long& right)
{
    return left > lltoBI(right);
}

bool operator <=(const Bigint& left, const Bigint& right)
{
    return !(left > right);
}

bool operator <=(const Bigint& left, const long long& right)
{
    return !(left > lltoBI(right));
}

bool operator >=(const Bigint& left, const Bigint& right)
{
    return !(left < right);
}

bool operator >=(const Bigint& left, const long long& right)
{
    return !(left < lltoBI(right));
}

/**
 *  @brief Реализация всех арифметических операций,
 *  выполняемых при помощи операторов.
 *  @ingroup Арифметические алгоритмы
 *  @param  left     Значение слева от бинарного оператора.
 *  @param  right    Значение справа от бинарного оператора.
 *  @param  num      Число, к которому применяется унарный оператор.
 *  @return          Во всех случаях возвращается Bigint.
*/

//операции сложения
//
const Bigint operator +(const Bigint& left, const Bigint& right)
{
    string a = left.value, b = right.value;

    if (*(a.begin()) == '-')
    {
        a.erase(0, 1);
        if (*(b.begin()) == '-')
        {
            b.erase(0, 1);
            return -(Bigint(a) + Bigint(b));
        }
        return right - Bigint(a);
    }

    if (*(b.begin()) == '-')
    {
        b.erase(0, 1);
        return left - Bigint(b);
    }

    if (a.length() < b.length())
        swap(a, b);

    for (string::iterator ia = a.end() - 1, ib = b.end() - 1; ib != b.begin() - 1; ia--, ib--)
    {
        *ia = *ia + *ib - '0';
        if (*ia > '9')
        {
            *ia -= 10;
            string::iterator temp = ia - 1;
            while (*temp == '9' && temp != a.begin() - 1)
            {
                *temp = '0';
                temp--;
            }

            if (temp == a.begin() - 1)
                a.insert(0, "1");
            else
                *temp = *temp + 1;
        }
    }

    return Bigint(a);
}

const Bigint operator +(const Bigint& left, const long long &right)
{
    Bigint BIright = lltoBI(right);
    return left + BIright;
}

const Bigint operator +(const long long& left, const Bigint& right)
{
    Bigint BIleft = lltoBI(left);
    return left + right;
}

Bigint& operator +=(Bigint& left, const Bigint& right)
{
    left = left + right;
    return left;
}

Bigint& operator +=(Bigint& left, const long long& right)
{
    left = left + lltoBI(right);
    return left;
}

const Bigint& operator ++(Bigint& num)
{
    num = num + 1;
    return num;
}

const Bigint& operator ++(Bigint& num, int)
{
    Bigint& oldValue = num;
    num = num + 1;
    return oldValue;
}

//операции вычитания
//
const Bigint operator -(const Bigint& left, const Bigint &right)
{
    string a = left.value, b = right.value;

    if (*(a.begin()) == '-')
    {
        a.erase(0, 1);
        if (*(b.begin()) == '-')
        {
            b.erase(0, 1);
            return Bigint(b) - Bigint(a);
        }
        else
            return -(Bigint(a) + right);
    }

    if (*(b.begin()) == '-')
    {
        b.erase(0, 1);
        return left + Bigint(b);
    }

    bool negative = false;
    if (left < right)
    {
        swap(a, b);
        negative = true;
    }

    for (string::iterator ia = a.end() - 1, ib = b.end() - 1; ib != b.begin() - 1; ia--, ib--)
    {
        *ia = *ia - *ib + '0';
        if (*ia < '0')
        {
            *ia += 10;
            string::iterator temp = ia - 1;
            while (*temp == '0' && temp != a.begin() - 1)
            {
                *temp = '9';
                temp--;
            }
            if (temp == a.begin() - 1)
                a.erase(0, 1);
            else
                *temp = *temp - 1;
        }
    }

    while (*(a.begin()) == '0')
        a.erase(0, 1);
    if (a.length() == 0)
        a += "0";
    a.insert(0, (negative) ? "-" : "");
    return Bigint(a);
}

const Bigint operator -(const Bigint& left, const long long& right)
{
    Bigint BIright = lltoBI(right);
    return (left - BIright);
}

const Bigint operator -(const long long& left, const Bigint& right)
{
    Bigint BIleft = lltoBI(left);
    return (BIleft- right);
}

Bigint& operator -=(Bigint& left, const Bigint& right)
{
    left = left - right;
    return left;
}

Bigint& operator -=(Bigint& left, const long long& right)
{
    left = left - right;
    return left;
}

const Bigint& operator --(Bigint &num)
{
    num = num - 1;
    return num;
}

const Bigint& operator --(Bigint &num, int)
{
    Bigint& oldValue = num;
    num = num - 1;
    return oldValue;
}

//операции умножения
//
const Bigint operator *(const Bigint& left, const Bigint& right)
{
    bool negative = false;
    if (left == 0 || right == 0)
        return Bigint(0);
    const short PifagorTable[10][10] =
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {0, 2, 4, 6, 8, 10, 12, 14, 16, 18},
        {0, 3, 6, 9, 12, 15, 18, 21, 24, 27},
        {0, 4, 8, 12, 16, 20, 24, 28, 32, 36},
        {0, 5, 10, 15, 20, 25, 30, 35, 40, 45},
        {0, 6, 12, 18, 24, 30, 36, 42, 48, 54},
        {0, 7, 14, 21, 28, 35, 42, 49, 56, 63},
        {0, 8, 16, 24, 32, 40, 48, 56, 64, 72},
        {0, 9, 18, 27, 36, 45, 54, 63, 72, 81}
    };

    string a = left.value, b = right.value;

    if (*(a.begin()) == '-')
    {
        a.erase(0, 1);
        negative = !negative;
        if (*(b.begin()) == '-')
        {
            b.erase(0, 1);
            negative = !negative;
        }
    }

    if (*(b.begin()) == '-')
    {
        b.erase(0, 1);
        negative = !negative;
    }

    if (a.length() < b.length())
        swap(a, b);

    vector<string> SumTable;
    int margin;
    string::iterator i;
    for (i = b.end() - 1, margin = 0; i != b.begin() - 1; i--, margin++)
    {
        string CurNum = "";
        int mind = 0;

        for (string::iterator j = a.end() - 1; j != a.begin() - 1; j--)
        {
            int ed = (PifagorTable[*i - '0'][*j - '0'] + mind) % 10;
            CurNum = to_string(ed) + CurNum;
            mind = (PifagorTable[*i - '0'][*j - '0'] + mind) / 10;
        }

        if (mind != 0)
            CurNum.insert(0, to_string(mind));

        string space = "";
        for (int i = 0; i < margin; i++)
            space += "0";

        CurNum = CurNum + space;
        SumTable.push_back(CurNum);
    }

    size_t maxlen = SumTable.back().length();
    for (vector<string>::iterator i = SumTable.begin(); i != SumTable.end() - 1; i++)

        while (i->length() != maxlen)
            *i = "0" + *i;

    string CurSum = SumTable.front();
    for (vector<string>::iterator i = SumTable.begin() + 1; i != SumTable.end(); i++)
    {
        string a = *i;
        for (string::iterator i1 = CurSum.end() - 1, i2 = a.end() - 1; i1 != CurSum.begin() - 1; i1--, i2--)
        {
                *i1 = *i1 + *i2 - '0';
                if (*i1 > '9')
                {
                    *i1 -= 10;
                    string::iterator temp = i1 - 1;
                    while (*temp == '9' && temp != CurSum.begin() - 1)
                    {
                        *temp = '0';
                        temp--;
                    }
                    if (temp == a.begin() - 1)
                        a.insert(0, "1");
                    else
                        *temp = *temp + 1;
                }
        }
    }
    while (*(CurSum.begin()) == '0')
        CurSum.erase(0, 1);
    return (negative) ? -Bigint(CurSum) : Bigint(CurSum);

}

const Bigint operator *(const Bigint& left, const long long& right)
{
    return left * lltoBI(right);
}

const Bigint operator *(const long long& left, const Bigint& right)
{
    return lltoBI(left) * right;
}

Bigint& operator *= (Bigint& left, const Bigint& right)
{
    left = left * right;
    return left;
}

Bigint& operator *=(Bigint& left, const long long& right)
{
    left = left * lltoBI(right);
    return left;
}

//операции целочисленного деления
//
const Bigint operator /(const Bigint& left, const Bigint& right)
{
    string a = left.value, b = right.value;
    if (*(a.begin()) == '-')
    {
        a.erase(0, 1);
        if (*b.begin() == '-')
        {
            b.erase(0, 1);
            return Bigint(Bigint(a) / Bigint(b));
        }
        return -Bigint(Bigint(a) / Bigint(b));
    }
    if (*(b.begin()) == '-')
    {
        b.erase(0, 1);
        return -Bigint(Bigint(a) / Bigint(b));
    }
    string res = "";
    Bigint mod;
    string strmod = "";

    for (string::iterator i = a.begin(); i != a.end(); i++)
    {
        Bigint div;
        strmod = strmod + *i;
        mod = Bigint(strmod);

        for (int j = 1; j <= 10; j++)
            if (Bigint(right * itoBI(j)) > mod)
            {
                div = j - 1;
                break;
            }

        mod -= right * div;
        res += BItostr(div);
        strmod = BItostr(mod);
    }
    return Bigint(res);
}

const Bigint operator /(const Bigint& left, const long long& right)
{
    return left / lltoBI(right);
}

const Bigint operator /(const long long& left, const Bigint& right)
{
    return lltoBI(left) / right;
}


Bigint& operator /= (Bigint& left, const Bigint& right)
{
    left = left / right;
    return left;
}

Bigint& operator /=(Bigint& left, const long long& right)
{
    left = left / lltoBI(right);
    return left;
}

//операции взятия остатка
//
const Bigint operator %(const Bigint& left, const Bigint& right)
{
    return (left - right * (left / right));
}


Bigint& operator %= (Bigint& left, const Bigint& right)
{
    left = left % right;
    return left;
}

Bigint& operator %=(Bigint& left, const long long& right)
{
    left = left % lltoBI(right);
    return left;
}

//операции возведения в степень
//
const Bigint operator ^(const Bigint& left, const Bigint& right)
{
    Bigint ans = left;
    for (Bigint i = 1; i < right; i++)
        ans *= ans;
    return ans;
}

const Bigint operator ^(const Bigint& left, const long long& right)
{
    return left^lltoBI(right);
}

Bigint& operator ^=(Bigint& left, const Bigint& right)
{
    left = left^right;
    return left;
}

Bigint& operator ^=(Bigint& left, const long long& right)
{
    left = left^right;
    return left;
}

/**
 *  @brief Реализация функций преобразования типов данных в Bigint.
 *  @ingroup Преобразования.
 *  @param  num      Число, которое нужно преобразовать в Bigint.
 *  @return   Число Bigint с заданным значением.
 *
*/

Bigint itoBI(int num)
{
    return Bigint(to_string(num));
}

Bigint ltoBI(long num)
{
    return Bigint(to_string(num));
}

Bigint lltoBI(long long num)
{
    return Bigint(to_string(num));
}

Bigint strtoBI(string s)
{
    const string numerals = "0123456789";
    for (string::iterator i = s.begin(); i != s.end(); i++)
    {
        if (numerals.find(*i) == string::npos)
        {
            printf("Error: String must contain numerals only. Cannot be converted to Bigint.\n");
            exit(0);
        }
    }
    return Bigint(s);
}

/**
 *  @brief Объявление функций преобразования Bigint в другие типы данных.
 *  @ingroup Преобразования
 *  @param  num     Число, которое нужно преобразовать.
 *  @return Число Bigint со значением num.
 *  @note Есть смысл только в преобразованиях в string и const char*,
 *        так как если преобразовывать слишком большое число в long long
 *        или другой стандартный целочисленный тип С++, может произойти
 *        выход за допустимые границы памяти, выделенной под число.
*/

string BItostr(Bigint num)
{
    return num.getstrvalue();
}

const char* BItocchar(Bigint num)
{
    return num.getstrvalue().c_str();
}

#endif // BIGINT_H

//COPYRIGHT (C) Mikhail Korobkov, 2019
//ALL RIGHTS RESERVED.
