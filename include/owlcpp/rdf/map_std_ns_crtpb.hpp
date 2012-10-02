/** @file "/owlcpp/include/owlcpp/rdf/map_std_crtpb.hpp" 
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#ifndef MAP_STD_NS_CRTPB_HPP_
#define MAP_STD_NS_CRTPB_HPP_
#include "boost/assert.hpp"

#include "owlcpp/rdf/detail/map_traits.hpp"
#include "owlcpp/rdf/store_concepts.hpp"

namespace owlcpp{

/**Enable interaction between a mutable maps of namespaces and nodes and
immutable map of standard IRI nodes.
Base for CRTP (Curiously Recurring Template Pattern).
*******************************************************************************/
template<class Super> class Map_std_ns_crtpb {
   typedef detail::Map_traits<Super> traits;
   typedef typename traits::map_std_type map_std_type;
   typedef typename traits::map_ns_type map_ns_type;

   map_std_type const& _map_std() const {
      return static_cast<Super const&>(*this).map_std_;
   }

   map_ns_type const& _map_ns() const {
      return static_cast<Super const&>(*this).map_ns_;
   }

   map_ns_type& _map_ns() {
      return static_cast<Super&>(*this).map_ns_;
   }

public:
   bool valid(const Ns_id nsid) const {
      BOOST_ASSERT(! (_map_std().valid(nsid) && _map_ns().valid(nsid)) );
      return _map_std().valid(nsid) || _map_ns().valid(nsid);
   }

   std::string operator[](const Ns_id nsid) const {
      BOOST_ASSERT( valid(nsid) );
      return nsid < _map_std().ns_id_next() ? _map_std()[nsid] : _map_ns()[nsid];
   }

   std::string at(const Ns_id nsid) const {
      return nsid < _map_std().ns_id_next() ?
               _map_std().at(nsid) : _map_ns().at(nsid);
   }

   /**
    @param iid namespace IRI ID
    @return IRI prefix string or "" if no prefix was defined
   */
   std::string prefix(const Ns_id nsid) const {
      BOOST_ASSERT( valid(nsid) );
      return nsid < _map_std().ns_id_next() ?
               _map_std().prefix(nsid) : _map_ns().prefix(nsid);
   }

   /**
    @param iri namespace IRI string
    @return pointer to namespace IRI ID or NULL if iri is unknown
   */
   Ns_id const* find_ns(std::string const& iri) const {
      if( Ns_id const*const id = _map_std().find_iri(iri) ) return id;
      return _map_ns().find_iri(iri);
   }

   /**
    @param pref prefix for namespace IRI
    @return pointer to namespace IRI ID or NULL if prefix is unknown
   */
   Ns_id const* find_prefix(std::string const& pref) const {
      if( Ns_id const*const id = _map_std().find_prefix(pref) ) return id;
      return _map_ns().find_prefix(pref);
   }

   Ns_id insert_ns(std::string const& iri) {
      if( Ns_id const*const iid = find_ns(iri) ) return *iid;
      return _map_ns().insert(iri);
   }

   /**
    @param iid namespace IRI ID
    @param pref namespace IRI prefix
    @details Define or re-define the prefix for a user-defined namespace IRI.
   */
   void insert_prefix(const Ns_id nsid, std::string const& pref) {
      typedef typename Super::Err Err;
      if( nsid < _map_std().ns_id_next() ) {
         if( pref.empty() || pref == _map_std().prefix(nsid) ) return;
         BOOST_THROW_EXCEPTION(
                  Err()
                  << typename Err::msg_t("cannot re-define standard prefix")
                  << typename Err::str1_t(pref)
                  << typename Err::str2_t(_map_std().prefix(nsid))
         );
      }
      BOOST_ASSERT( _map_ns().valid(nsid) );
      if( pref.empty() ) {
         _map_ns().set_prefix(nsid);
         return;
      }
      Ns_id const*const iid0 = _map_ns().find_prefix(pref);
      if( iid0 ) {
         if( *iid0 == nsid ) return; //prefix already defined for same IRI
         BOOST_THROW_EXCEPTION(
                  Err()
                  << typename Err::msg_t("prefix reserved for different IRI")
                  << typename Err::str1_t(pref)
                  << typename Err::str2_t(at(nsid))
                  << typename Err::str3_t(at(*iid0))
         );
      }
      _map_ns().set_prefix(nsid, pref);
   }
};

}//namespace owlcpp
#endif /* MAP_STD_NS_CRTPB_HPP_ */
