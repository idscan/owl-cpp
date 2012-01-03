/** @file "/owlcpp/lib/rdf/test/iri_store01_run.cpp"
part of %owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2011
*******************************************************************************/
#define BOOST_TEST_MODULE iri_store01
#include "boost/test/unit_test.hpp"
#include "test/exception_translator.hpp"
#include "owlcpp/rdf/iri_store.hpp"
#include "owlcpp/terms/uri_tags.hpp"
#include <exception>
#include "boost/exception/all.hpp"

namespace owlcpp{ namespace test{

BOOST_GLOBAL_FIXTURE( Exception_translator );

/**
*******************************************************************************/
BOOST_AUTO_TEST_CASE( iri_store01_case01 ) {
   Iri_store is;
   const std::string iri1("http://iri1");
   const std::string iri2("http://iri2");
   const std::string iri3("http://iri3");
   const Ns_id id1 = is.insert(iri1);
   BOOST_CHECK_MESSAGE( id1 == is.insert(iri1), "same ID from inserting duplicates" );
   const Ns_id id2 = is.insert(iri2);
   BOOST_CHECK_EQUAL(is[id1], iri1);
   BOOST_CHECK_MESSAGE( ! is.prefix(id1), "should return NULL pointer" );
   is.remove(iri1);
   BOOST_CHECK_THROW(is.remove(iri1), Iri_store::Err);
   BOOST_CHECK_THROW(is.remove(id1), Iri_store::Err);
   const Ns_id id3 = is.insert(iri3);
   BOOST_CHECK_MESSAGE(id1 == id3, "id should be recycled");
}

}//namespace test
}//namespace owlcpp
