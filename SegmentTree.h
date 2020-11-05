/**

   * SegmentTree.h
   *
   * The class described in this file
   * is a kind of extension for STL
   * library. As you already noticed
   * from the title, it is a tree of
   * segments. The reason for creating
   * this class was the miss of this
   * class in C++ Standart Library.
   *
   * @author Mikhail Korobkov
   * @version 1.0
   */

#ifndef SEGMENTTREE_H_INCLUDED
#define SEGMENTTREE_H_INCLUDED

#include <functional>
#include <vector>

/**
 * The class itself.
 *
 * Template parameter can be a type name,
 * structure or a class name. This parameter
 * defines the type of persistent values.
 */

template<class _TreeType>
class SegmentTree
{

public:

    /** \brief
     * C-tor that initializes the tree with the
     * help of fixed-size array.
     *
     * \param _array The array that the tree should
     *               be based on.
     *
     * \param _array_size The size of the array
     *                    committed to the c-tor.
     *
     * \param _operation The function that should
     *                   commit two homogeneous
     *                   values and return some
     *                   value as a result. This
     *                   function should be based
     *                   on the main operation of the
     *                   tree.
     *
     *        For example, you want your tree to count sum
     *        on some segment of integer array. Then the
     *        function may be declared like this:
     *        int add(int x, int y) { return x + y; }
     *
     *        You can also use lambda expression instead of
     *        the function.
     *
     * \param _non_influence_value The value that can't affect
     *                             on the result of the _operation,
     *                             as if it would take one parameter.
     *        For example, if add(0, y) returns y, then _non_influence_value
     *        should be 0. Another example: if you call std::max() for
     *        negative infinity and 5 it will return 5, so _non_influence_value
     *        for this function is negative infinity.
     */
    SegmentTree(_TreeType *_array, const size_t _array_size, std::function<_TreeType(_TreeType __first, _TreeType __second)> _operation, _TreeType _non_influence_value):
    __size(_array_size), __operation(_operation), NIV(_non_influence_value)
    {
        tree = new _TreeType[__size*4]{0};
        _TreeType *Array = new _TreeType[__size];
        for (size_t i = 0; i != __size; ++i)
            Array[i] = _array[i];
        build_tree(Array);
    }


    /** \brief
     * C-tor that initializes the tree with the
     * help of std::vector.
     * \param _container The std::vector that tree should
     *                   be based on.
     * \param _operation No difference with the first c-tor.
     * \param _non_influence_value No difference with the first c-tor.
     */
    SegmentTree(std::vector<_TreeType> &_container, std::function<_TreeType> _operation, _TreeType _non_influence_value):
    __size(_container.size()), __operation(_operation), NIV(_non_influence_value)
    {
        tree = new _TreeType[__size*4]{0};
        _TreeType *Array = new _TreeType[__size];
        for (size_t i = 0; i != __size; ++i)
            Array[i] = _container[i];
        build_tree(Array);
    }

    /** \brief
     * Returns the size of the array that was committed
     * to the constructor.
     *
     * \return __size private member of the class.
     *
     */
    const size_t size() { return __size; }


    /** \brief
     * Replaces single array element with a new one and updates
     * the tree according to the new element value.
     *
     * \param _index An index of an element that should be replaced.
     * \param _n_value New value of an element.
     */
    void upd_elem(size_t _index, _TreeType _n_value, size_t id = 0, size_t l = 0, size_t r = 0)
    {
        if (id == 0)
            r = __size;

        if (r - l == 1 && _index == l)
        {
            tree[id] = _n_value;
            return;
        }
        size_t mid = (l + r) / 2;
        if (_index < mid)
            upd_elem(_index, _n_value, id*2 + 1, l, mid);
        else
            upd_elem(_index, _n_value, id*2 + 2, mid, r);

        tree[id] = __operation(tree[id*2 + 1], tree[id*2 + 2]);
    }

    /** \brief
     * Get the required value from an array segment [_l; _r).
     * note: _l and _r must be indexes, not a number of an element.
     * \param _l Index of a left element.
     * \param _r Index of a right element.
     * \return The required value.
     */
    _TreeType get_seg_value(size_t _l, size_t _r, size_t id = 0, size_t l = 0, size_t r = 0)
    {
        if (id == 0)
            r = __size;

        if (r <= _l || _r <= l)
            return NIV;
        if (_l <= l && r <= _r)
            return tree[id];

        size_t mid = (l + r) / 2;
        return __operation(get_seg_value(_l, _r, id*2 + 1, l, mid), get_seg_value(_l, _r, id*2 + 2, mid, r));
    }

private:

    _TreeType *tree;                                                                            //the tree itself
    const _TreeType NIV;                                                                        //non-influence value
    size_t __size;                                                                              //tree size
    const std::function<_TreeType(_TreeType __first, _TreeType __second)> __operation;          //the operation

    /**
     * Warning: do not use this function anywhere else. Only the constructor requires it.
     */
    void build_tree(_TreeType *Array, size_t id = 0, size_t l = 0, size_t r = 0)
    {
        if (id == 0)
            r = __size;

        if (r - l == 1)
        {
            tree[id] = Array[l];
            return;
        }
        size_t mid = (l + r) / 2;
        build_tree(Array, id*2 + 1, l, mid);
        build_tree(Array, id*2 + 2, mid, r);
        tree[id] = __operation(tree[id*2 + 1], tree[id*2 + 2]);

    }
};

#endif // SEGMENTTREE_H_INCLUDED
