/*!
    \file
    \brief Header file

    That file contain main class and helper namespace with some featches
*/

#pragma once
#include <iostream>
#include <type_traits>
#include <list>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

/*!
	\brief Helper namespace
    \version 1.0
    \author 4l3x77

	That namespace contain some featches for print_ip class.
    
    \defgroup print_ip_helper
    @{
*/
namespace print_ip_helper 
{ 
    /*!
        \brief Helper variable. Determines ip address octets's delimeter.
    */
    static const char ip_delimeter = '.';
    /*!
        \brief Helper structs. Determines template type is vector or list.
        \defgroup is_vector_or_list
        @{
    */
    template <typename>
    struct is_vector_or_list : false_type {};

    template <typename T, typename... Args>
    struct is_vector_or_list<std::vector<T, Args...>> : true_type {};

    template <typename T, typename... Args>
    struct is_vector_or_list<std::list<T, Args...>> : true_type {};
    /*! @} */

    /**
        \brief Helper structs for printing ip addresses as tuples of same types.
        \defgroup helper_print_tuple
        @{
    */
    template <size_t typle_size>
    struct helper_print_tuple
    {
        template <typename element0, typename... tail>
        static constexpr void print(const tuple<element0, tail...>& tuple) 
        {
            auto element = get<sizeof...(tail) + 1 - typle_size>(tuple);
            static_assert(is_same_v<element0, decltype(element)>, "Different element's types in tuple!");
            cout << element;
            if (typle_size > 1) cout << ip_delimeter;
            helper_print_tuple<typle_size - 1>::print(tuple);
        }
    };

    template <>
    struct helper_print_tuple<0>
    {
        template <typename... tail>
        static constexpr void print(const tuple<tail...>&) {}
    };
    /*! @} */
}
/*! @} */


/*!
	\brief Main class.
    \version 1.0
    \author 4l3x77

	That class contain print_ip constructors for release metaprogramming SFINAE technique.

    \defgroup print_ip
    @{
*/
class print_ip 
{
public:
    /*!
        \brief Prints ip address represented as an integral type.
        \param value is any integral value
        \returns print ip to stdout
    */
    template <typename T, typename std::enable_if<is_integral_v<T>,bool>::type = true>
    print_ip(T value) 
    {
        static const size_t constexpr number_of_octets = sizeof(T);
        for (size_t i = number_of_octets; i--;) 
        {
            cout << (value >> (i << 3) & 0xff);
            if (i > 0) cout << print_ip_helper::ip_delimeter;
        }
        cout << endl;
    }

    /*!
        \brief Prints ip address represented as a string.
        \param value is reference to string
        \returns print ip to stdout
    */
    print_ip(const string& value) 
    {
        cout << value << endl;
    }

    /*!
        \brief Prints ip address represented as vector or list.
        \param container is reference to vector or list
        \returns print ip to stdout
    */
    template<class T, typename std::enable_if<print_ip_helper::is_vector_or_list<T>{},bool>::type = true>
    print_ip(const T& container) 
    {
        for (auto it = container.begin(); it != container.end(); ++it) 
        {
            cout << *it;
            if (it != prev(container.end())) cout << print_ip_helper::ip_delimeter;
        }
        cout << endl;
    }

    /*!
        \brief Prints ip address represented as tuple.
        \param container is reference to tuple with determine all octet's type
        \returns print ip to stdou
    */
    template <typename... tail>
    print_ip(const tuple<tail...>& tuple) 
    {
        print_ip_helper::helper_print_tuple<sizeof...(tail)>::print(tuple);
        cout << endl;
    }
};
/*! @} */