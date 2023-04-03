//
// Created by User on 2023/3/28.
//

#ifndef STUDYCXX_VEC_H
#define STUDYCXX_VEC_H

#include <cstddef>
#include <memory>

template<class T>
class Vec {
public:
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef size_t size_type;
    typedef T value_type;//值类型

    size_type size() const { return avail - data; }

    iterator begin() { return data; }

    const_iterator begin() const { return data; }

    iterator end() { return avail; }

    const_iterator end() const { return avail; }

    void push_back(const T &val);

    iterator erase(iterator position);

    iterator erase(iterator b, iterator e);

    bool isempty() { return !data; };

    void clear();

    std::ostream &print_vec(std::ostream &os);

    const T &operator[](size_type i) const { return data[i]; }

    T &operator[](size_type i) { return data[i]; }

    Vec &operator=(Vec &);

    Vec() { create(); }

    Vec(const Vec &val) { create(val.begin(), val.end()); }

    explicit Vec(size_type n, const T &val = T()) { create(n, val); }

    ~Vec() { un_create(); }

private:
    iterator data;//指针指向Vec的第一个元素
    iterator avail;//指针指向构造元素后面的一个元素
    iterator limit;//指针指向最后一个可获得元素后面的一个元素

    std::allocator<T> alloc;

    void create();

    void create(size_type n, const T &val = T());

    void create(const_iterator begin, const_iterator end);

    void un_create();

    void grow();

    void unchecked_append(const T &val);
};

template<class T>
Vec<T> &Vec<T>::operator=(Vec<T> &rth) {
    if (&rth != this) {
        //删除左值数组内存
        un_create();
        //复制右值
        create(rth.begin(), rth.end());
    }
    return *this;
}

//初始化
//1、如果对象中有数据元素，data指向首元素，否则为0
//2、data<=avail<=limit
//3、在[data,avail)区间的元素被初始化
//4、在[data,limit)区间的元素不会被初始化

template<class T>
void Vec<T>::create() {
    data = limit = avail = 0;
}

template<class T>
void Vec<T>::create(size_type n, const T &val) {
    data = alloc.allocate(n);
    limit = avail = data + n;
    std::uninitialized_fill(data, limit, val);
}

template<class T>
void Vec<T>::create(const_iterator begin, const_iterator end) {
    data = alloc.allocate(end - begin);
    limit = avail = std::uninitialized_copy(begin, end, data);
}

template<class T>
void Vec<T>::un_create() {
    if (data) {
        //反序删除元素
        iterator it = avail;
        while (it != data)
            alloc.destroy(--it);
        //返回占用的内存空间
        alloc.deallocate(data, limit - data);
    }
    //重置对象指针
    data = limit = avail = 0;
}

template<class T>
void Vec<T>::push_back(const T &val) {
    if (avail == limit) {
        //空间不足，分配足够的空间
        grow();
    }
    unchecked_append(val);//末尾添加元素
}

template<class T>
void Vec<T>::grow() {
    //扩展内存空间大小，分配原来空间的2倍大小
    size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));//Vec为空的时候，选择一个元素进行分配
    iterator new_data = alloc.allocate(new_size);
    //复制原来是元素到新的内存空间
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);
    //释放原来的内存空间
    un_create();
    //重置指针到新的内存地址
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template<class T>
void Vec<T>::unchecked_append(const T &val) {
    alloc.construct(avail++, val);
}

template<class T>
typename
Vec<T>::iterator Vec<T>::erase(Vec::iterator pos) {
    /*if(data && pos != avail){
        alloc.destroy(pos);
        iterator it = pos + 1;
        while(it != avail){
            alloc.construct(pos++, *it++);
            alloc.destroy(pos);
        }
        avail = pos;
    }
    return avail;*/
    return erase(pos, pos + 1);
}

template<class T>
typename
Vec<T>::iterator Vec<T>::erase(Vec::iterator b, Vec::iterator e) {
    if (data && b != avail && b != e) {
        iterator it = b;
        while (it != e) {
            alloc.destroy(it++);
        }
        while (e != avail) {
            alloc.construct(b++, *e);
            alloc.destroy(e++);
        }
        avail = b;
    }
    return avail;
}

template<class T>
std::ostream &Vec<T>::print_vec(std::ostream &os) {
    if (avail - data > 0) {
        const_iterator iter = data;
        os << *iter++;
        while (iter != avail) {
            os << " " << *iter++;
        }
        os << std::endl;
    }
    return os;
}

template<class T>
void Vec<T>::clear() {
    iterator it = avail;
    while (it != data) {
        alloc.destroy(--it);
    }
    avail = data;
}

#endif //STUDYCXX_VEC_H
