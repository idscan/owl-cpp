/** @file "/owlcpp/include/owlcpp/rdf/map_std.hpp"
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#ifndef MAP_STD_HPP_
#define MAP_STD_HPP_
#include "boost/assert.hpp"
#include "boost/range.hpp"
#include "boost/range/algorithm/max_element.hpp"
#include "boost/utility.hpp"
#include "boost/concept/assert.hpp"

#include "owlcpp/rdf/map_ns.hpp"
#include "owlcpp/rdf/map_node_iri.hpp"
#include "owlcpp/terms/node_tags_system.hpp"
#include "owlcpp/terms/detail/max_standard_id.hpp"

namespace owlcpp{

/**@brief Immutable static set of namespace IRIs and nodes
@details Contains at least blank and empty (literal) namespaces and empty node.
*******************************************************************************/
class Map_std : boost::noncopyable {

   template<class Inserter> explicit Map_std(Inserter const& ins)
   {
      insert_ns_tag(terms::N_empty());
      insert_ns_tag(terms::N_blank());
      insert_node_tag(terms::T_empty_());

      ins(*this);
   }

public:

   /**@brief Get instance of standard nodes map
    @tparam T SHOULD be callable with IRI map and node map inserting
    standard namespace IRIs and standard nodes.

    @code
   struct Inserter {
   void operator()(Map_std& map) const;
   };
   Map_std const& nms = Map_std::get(Inserter());
   @endcode

   */
   template<class T> static Map_std const& get(T const& t) {
      BOOST_CONCEPT_ASSERT((boost::UnaryFunction<T, void, Map_std&>));
      static const Map_std map(t);
      return map;
   }

   /**Insert standard namespace;
   non-constant method, can be used only during construction */
   template<class NsTag> void insert_ns_tag(NsTag const&) {
      BOOST_ASSERT(ns_.size() < detail::max_std_ns_id()());
      ns_.insert(NsTag::id(), NsTag::iri());
      ns_.set_prefix(NsTag::id(), NsTag::prefix());
   }

   /**Insert standard IRI node;
   non-constant method, can be used only during construction */
   template<class NTag> void insert_node_tag(NTag const&) {
      BOOST_ASSERT(node_.size() < detail::max_std_node_id()());
      typedef typename NTag::ns_type ns_type;
      insert_ns_tag(ns_type());
      node_.insert(NTag::id(), ns_type::id(), NTag::name());
   }

   /**
    @param nsid namespace IRI ID
    @return true if nodes should not be added to this namespace by user;
    e.g., in case of RDF or OWL namespaces.
    That is, all nodes from this namespace should reside in this map.
   */
   bool is_standard(const Ns_id nsid) const {
      return
               ! is_empty(nsid) &&
               ! is_blank(nsid) &&
               nsid < detail::max_std_ns_id()
               ;
   }

   bool valid(const Ns_id nsid) const {return ns_.valid(nsid);}
   Ns_id const* find_iri(std::string const& iri) const {return ns_.find_iri(iri);}
   Ns_id const* find_prefix(std::string const& pref) const {return ns_.find_prefix(pref);}
   std::string operator[](const Ns_id nsid) const {return ns_[nsid];}
   std::string at(const Ns_id nsid) const {return ns_.at(nsid);}
   std::string prefix(const Ns_id nsid) const {return ns_.prefix(nsid);}

   bool valid(const Node_id nid) const {return node_.valid(nid);}
   Node_iri const& operator[](const Node_id nid) const {return node_[nid];}
   Node_iri const& at(const Node_id nid) const {return node_.at(nid);}
   Node_id const* find(Node_iri const& node) const {return node_.find(node);}

   Node_id const* find(const Ns_id ns, std::string const& val) const {
      if( is_blank(ns) || ns >= detail::max_std_ns_id() ) return 0;
      return node_.find(Node_iri(ns, val));
   }

private:
   Map_ns ns_;
   Map_node_iri node_;
};

}//namespace owlcpp
#endif /* MAP_STD_HPP_ */
