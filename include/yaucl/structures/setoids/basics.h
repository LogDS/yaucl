//
// Created by giacomo on 25/11/22.
//

#ifndef KNOBAB_SERVER_BASICS_H
#define KNOBAB_SERVER_BASICS_H

#include <set>
#include <unordered_set>

template<typename T>
std::unordered_set<T> unordered_intersection(const std::unordered_set<T> &a,
                                             const std::unordered_set<T> &b){
    if (a.size() > b.size()) return unordered_intersection(b, a);



    std::unordered_set<T> v3;
    for (auto i = a.begin(); i != a.end(); i++) {
        if (b.find(*i) != b.end()) v3.insert(*i);
    }
    return v3;
}

template<typename T>
std::set<T> ordered_intersection(const std::set<T> &a, const std::set<T> &b){
    std::set<T> v3;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(v3, v3.begin()));
    return v3;
}

template<typename T>
bool isSubsetOf(const std::set<T> &a, const std::set<T> &b) {
    return std::includes(b.begin(), b.end(), a.begin(), a.end());
}




template<typename T>
std::unordered_set<T> unordered_difference(const std::unordered_set<T> &a,
                                           const std::unordered_set<T> &b){
    std::unordered_set<T> v3;
    for (auto i = a.begin(); i != a.end(); i++) {
        if (b.find(*i) == b.end()) v3.insert(*i);
    }
    return v3;
}

template<typename T>
std::set<T> ordered_difference(const std::set<T> &a, const std::set<T> &b){
    std::set<T> v3;
    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(v3, v3.begin()));
    return v3;
}


template<typename T>
double unodreded_distance(const std::unordered_set<T> &a,
                          const std::unordered_set<T> &b) {
    if (a.size() < b.size()) return unodreded_distance(b, a);
    double total = a.size();
    for (auto i = b.begin(); i != b.end(); i++) {
        if (a.find(*i) == a.end()) total++;
    }
    if (total == 0.0) return 0.0;
    return (((double )unordered_difference(a,b).size())+((double )unordered_difference(b,a).size()))/total;
}

#include <vector>
#include <cmath>

template
        <typename T>
std::vector<std::unordered_set<T>> powerset(const std::unordered_set<T> & a) {
    std::vector<T> set{a.begin(), a.end()};
    std::vector<std::unordered_set<T>> result;
    /*set_size of power set of a set with set_size
    n is (2**n -1)*/

    unsigned long long int pow_set_size = std::pow(2, a.size()), set_size = a.size();
    unsigned long long int counter, j;

    /*Run from counter 000..0 to 111..1*/
    for(counter = 0; counter < pow_set_size; counter++)
    {
        std::unordered_set<T> subset;
        for(j = 0; j < set_size; j++)
        {

            /* Check if jth bit in the counter is set
                If set then print jth element from set */
            if(counter & (1 << j))
                subset.insert(set.at(j));
        }
        result.emplace_back(subset);
    }
    return result;
}



#include <numeric>
#include <vector>

template <typename T>
std::unordered_set<std::unordered_set<T>> cartesian_product(const std::vector<std::vector<T>> & v ) {
    const long long N = std::accumulate( v.begin(), v.end(), 1LL, []( long long a, const std::vector<T>& b ) { return a*b.size(); } );
    std::unordered_set<std::unordered_set<T>> result;
    for( long long n=0 ; n<N ; ++n ) {
        lldiv_t q { n, 0 };
        std::unordered_set<T> u;
        for( long long i=v.size()-1 ; 0<=i ; --i ) {
            q = std::div( q.quot, v[i].size() );
            u.insert(v[i][q.rem]);
            //u[i] = v[i][q.rem];
        }
        result.insert(u);
    }
    return result;
}
/*
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> &s)
{
    os << '[';
    for (auto const& i: s) {
        os << i << ", ";
    }
    return os << ']';
}*/

#include <map>
#include <functional>
#include <algorithm>
#include <yaucl/functional/assert.h>

template <typename Iterator, typename Key, typename Value>
std::map<Key, std::vector<Value>> GroupByKeyExtractor(Iterator begin, Iterator end, std::function<Key(const Value&)> keyExtractor)
{
    DEBUG_ASSERT(std::is_sorted(begin, end));
    std::map<Key, std::vector<Value>> groups;
    decltype(end) upper;

    for(auto lower = begin; lower != end; lower = upper)
    {
        Key k = keyExtractor(*lower);

        // get the upper position of all elements with the same ID
        upper = std::upper_bound(begin, end,  *lower,[keyExtractor](const Value& x, const Value& y) { return keyExtractor(x) < keyExtractor(y); });

        // add those elements as a group to the output vector
        groups[k] = {lower, upper};
    }

    return groups;
}

template <typename Iterator, typename Key, typename Value>
std::vector<std::pair<Key, std::vector<Value>>> GroupByKeyExtractorAsVector(Iterator begin, Iterator end, std::function<Key(const Value&)> keyExtractor)
{
    DEBUG_ASSERT(std::is_sorted(begin, end));
    std::vector<std::pair<Key, std::vector<Value>>> groups;
    decltype(end) upper;

    for(auto lower = begin; lower != end; lower = upper)
    {
        Key k = keyExtractor(*lower);

        // get the upper position of all elements with the same ID
        upper = std::upper_bound(begin, end,  *lower,[keyExtractor](const Value& x, const Value& y) { return keyExtractor(x) < keyExtractor(y); });

        // add those elements as a group to the output vector
        groups.emplace_back(k, std::vector<Value>{lower, upper});
    }

    return groups;
}

#include <cassert>

template <typename Iterator, typename Key, typename Value>
std::vector<std::vector<Value>> GroupByKeyExtractorIgnoreKey(Iterator begin, Iterator end, std::function<Key(const Value&)> keyExtractor)
{
    DEBUG_ASSERT(std::is_sorted(begin, end));
    std::vector<std::vector<Value>> groups;
    decltype(end) upper;

    for(auto lower = begin; lower != end; lower = upper)
    {
        Key k = keyExtractor(*lower);

        // get the upper position of all elements with the same ID
        upper = std::upper_bound(begin, end,  *lower,[keyExtractor](const Value& x, const Value& y) { return keyExtractor(x) < keyExtractor(y); });

        // add those elements as a group to the output vector
        groups.emplace_back(std::vector<Value>{lower, upper});
    }

    return groups;
}

template <typename T>
void remove_duplicates(std::vector<T>& vec){
    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
}

#endif //KNOBAB_SERVER_BASICS_H