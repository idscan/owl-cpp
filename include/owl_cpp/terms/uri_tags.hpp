/** @file "/owl_cpp/include/owl_cpp/terms/uri_tags.hpp"
part of owl_cpp project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2010
*******************************************************************************/
#ifndef URI_TAGS_HPP_
#define URI_TAGS_HPP_
#include <string>
#include "uri_macro.hpp"
#include "owl_cpp/ns_id.hpp"

namespace owl_cpp{ namespace terms{

/**@struct Ns_xxx
@brief Namespace tag classes generated by macro OWLCPP_GENERATE_NAMESPACE_TYPES
@details Declare types for each standard URI, e.g.: @code
 struct Ns_rdfs {
   static const unsigned index = 3;
   static const std::string name;
   static const std::string prefix;
   typedef Ns_id id_type;
}; @endcode
*******************************************************************************/
OWLCPP_GENERATE_STD_NAMESPACE_TYPES


}//namespace terms
}//namespace owl_cpp

#endif /* URI_TAGS_HPP_ */
