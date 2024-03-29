#include "catch.hpp"

#include "filesystem.hpp"
#include "path.hpp"
#include <sstream>

namespace fs = ft::filesystem;

TEST_CASE( "ft::filesystem::path - Construction", "[class][path][filesystem][construct]" )
{

	CHECK( fs::path().empty());
	CHECK( fs::path().root_directory().empty() );
	CHECK( fs::path().relative_path().empty() );


	CHECK( fs::path().has_root_directory() == false );
	CHECK( fs::path().has_root_path() == false );
	CHECK( fs::path().has_relative_path() == false );
	CHECK( fs::path().has_parent_path() == false );
	CHECK( fs::path().has_filename() == false );
	CHECK( fs::path().has_stem() == false );
	CHECK( fs::path().has_extension() == false );
	CHECK( fs::path().is_absolute() == false );
	CHECK( fs::path().is_relative() == true );


    CHECK(fs::path("///foo/bar").empty() == false);

    CHECK(fs::path("///foo////bar") == fs::path("/foo/bar"));
    CHECK(fs::path("///foo/bar") == "/foo/bar");
    CHECK(fs::path("//foo//bar") == "//foo/bar");
    CHECK("/usr/local/bin" == fs::path("/usr/local/bin"));


    CHECK(fs::path("foo") == "foo");
    CHECK(fs::path("foo/") == "foo/");
}

TEST_CASE( "path - Assign", "[class][path][filesystem][assign]" )
{
    fs::path p1("/foo/bar");
    fs::path p2("/usr/local");
    fs::path p3;
    p3 = p1;
    REQUIRE(p1 == p3);
    p3 = fs::path("/usr/local");
    REQUIRE(p2 == p3);
    p3 = fs::path("/usr/local");
    REQUIRE(p2 == p3);
	p3 = fs::path::string_type("/foo/bar");
    REQUIRE(p1 == p3);
}

TEST_CASE( "path - Append", "[class][path][filesystem][append]" ) {
    CHECK(fs::path("foo") / "" == "foo/");
    CHECK(fs::path("foo") / "/bar" == "/bar");
    CHECK(fs::path("/foo") / "/" == "/");

	CHECK(fs::path("/foo/bar") / "some///other" == "/foo/bar/some/other");
    fs::path p1("/tmp/test");
    fs::path p2("foobar.txt");
    fs::path p3 = p1 / p2;
    CHECK("/tmp/test/foobar.txt" == p3);
}

TEST_CASE( "fs::path - Concat", "[class][path][filesystem][concatenation]" )
{
    CHECK((fs::path("foo") += fs::path("bar")) == "foobar");
    CHECK((fs::path("foo") += fs::path("/bar")) == "foo/bar");

    CHECK((fs::path("foo") += std::string("bar")) == "foobar");
    CHECK((fs::path("foo") += std::string("/bar")) == "foo/bar");

    CHECK((fs::path("foo") += "bar") == "foobar");
    CHECK((fs::path("foo") += "/bar") == "foo/bar");

	CHECK((fs::path("foo") += 'b') == "foob");
    CHECK((fs::path("foo") += '/') == "foo/");

	CHECK((fs::path("foo") += std::string("bar")) == "foobar");
    CHECK((fs::path("foo") += std::string("/bar")) == "foo/bar");


    CHECK(fs::path("foo").concat("bar") == "foobar");
    CHECK(fs::path("foo").concat("/bar") == "foo/bar");

    std::string bar = "bar";
    CHECK(fs::path("foo").concat(bar.begin(), bar.end()) == "foobar");

    CHECK((fs::path("/foo/bar") += "/some///other") == "/foo/bar/some/other");


}

TEST_CASE( "fs::path - Modifiers", "[class][path][filesystem][modifier]" ) {

    CHECK(fs::path("foo/bar").remove_filename() == "foo/");
    CHECK(fs::path("foo/").remove_filename() == "foo/");
    CHECK(fs::path("/foo").remove_filename() == "/");
    CHECK(fs::path("/").remove_filename() == "/");

	CHECK(fs::path("/foo").replace_filename("bar") == "/bar");
    CHECK(fs::path("/").replace_filename("bar") == "/bar");
    CHECK(fs::path("/foo").replace_filename("b//ar") == "/b/ar");

    CHECK(fs::path("/foo/bar.txt").replace_extension("odf") == "/foo/bar.odf");
    CHECK(fs::path("/foo/bar.txt").replace_extension() == "/foo/bar");
    CHECK(fs::path("/foo/bar").replace_extension("odf") == "/foo/bar.odf");
    CHECK(fs::path("/foo/bar").replace_extension(".odf") == "/foo/bar.odf");
    CHECK(fs::path("/foo/bar.").replace_extension(".odf") == "/foo/bar.odf");
    CHECK(fs::path("/foo/bar/").replace_extension("odf") == "/foo/bar/.odf");

	fs::path p1 = "foo";
    fs::path p2 = "bar";
    p1.swap(p2);
    CHECK(p1 == "bar");
    CHECK(p2 == "foo");
}

TEST_CASE( "fs::path - Decompose", "[class][path][filesystem][decompose]" ) {
    CHECK(fs::path("").root_directory() == "");
    CHECK(fs::path(".").root_directory() == "");
    CHECK(fs::path("..").root_directory() == "");
    CHECK(fs::path("foo").root_directory() == "");
    CHECK(fs::path("/").root_directory() == "/");
    CHECK(fs::path("/foo").root_directory() == "/");
    CHECK(fs::path("foo/").root_directory() == "");
    CHECK(fs::path("/foo/").root_directory() == "/");
    CHECK(fs::path("foo/bar").root_directory() == "");
    CHECK(fs::path("/foo/bar").root_directory() == "/");
    CHECK(fs::path("///foo/bar").root_directory() == "/");


    CHECK(fs::path("").root_path() == "");
    CHECK(fs::path(".").root_path() == "");
    CHECK(fs::path("..").root_path() == "");
    CHECK(fs::path("foo").root_path() == "");
    CHECK(fs::path("/").root_path() == "/");
    CHECK(fs::path("/foo").root_path() == "/");
    CHECK(fs::path("foo/").root_path() == "");
    CHECK(fs::path("/foo/").root_path() == "/");
    CHECK(fs::path("foo/bar").root_path() == "");
    CHECK(fs::path("/foo/bar").root_path() == "/");
    CHECK(fs::path("///foo/bar").root_path() == "/");

	CHECK(fs::path("").relative_path() == "");
    CHECK(fs::path(".").relative_path() == ".");
    CHECK(fs::path("..").relative_path() == "..");
    CHECK(fs::path("foo").relative_path() == "foo");
    CHECK(fs::path("/").relative_path() == "");
    CHECK(fs::path("/foo").relative_path() == "foo");
    CHECK(fs::path("foo/").relative_path() == "foo/");
    CHECK(fs::path("/foo/").relative_path() == "foo/");
    CHECK(fs::path("foo/bar").relative_path() == "foo/bar");
    CHECK(fs::path("/foo/bar").relative_path() == "foo/bar");
    CHECK(fs::path("///foo/bar").relative_path() == "foo/bar");

	CHECK(fs::path("").parent_path() == "");
    CHECK(fs::path(".").parent_path() == "");
    CHECK(fs::path("..").parent_path() == "");  // unintuitive but as defined in the standard
    CHECK(fs::path("foo").parent_path() == "");
    CHECK(fs::path("/").parent_path() == "/");
    CHECK(fs::path("/foo").parent_path().string() == "/");
    CHECK(fs::path("foo/").parent_path().string() == "foo");
    CHECK(fs::path("/foo/").parent_path().string() == "/foo");
    CHECK(fs::path("foo/bar").parent_path().string() == "foo");
    CHECK(fs::path("/foo/bar").parent_path().string() == "/foo");
    REQUIRE(fs::path("///foo/bar").parent_path().string() == "/foo");

	CHECK(fs::path("").filename() == "");
    CHECK(fs::path(".").filename() == ".");
    CHECK(fs::path("..").filename() == "..");
    CHECK(fs::path("foo").filename() == "foo");
    CHECK(fs::path("/").filename() == "");
    CHECK(fs::path("/foo").filename() == "foo");
    CHECK(fs::path("foo/").filename() == "");
    CHECK(fs::path("/foo/").filename() == "");
    CHECK(fs::path("foo/bar").filename() == "bar");
    CHECK(fs::path("/foo/bar").filename() == "bar");
    CHECK(fs::path("///foo/bar").filename() == "bar");


	// stem()
    CHECK(fs::path("/foo/bar.txt").stem() == "bar");
    {
        fs::path p = "foo.bar.baz.tar";
        CHECK(p.extension() == ".tar");
        p = p.stem();
        CHECK(p.extension() == ".baz");
        p = p.stem();
        CHECK(p.extension() == ".bar");
        p = p.stem();
        CHECK(p == "foo");
        p = p.stem();
        CHECK(p == "foo");
    }
    CHECK(fs::path("/foo/.profile").stem() == ".profile");
    CHECK(fs::path(".bar").stem() == ".bar");
    CHECK(fs::path("..bar").stem() == ".");
    CHECK(fs::path(".").stem() == ".");
    CHECK(fs::path("..").stem() == "..");

    // extension()
    CHECK(fs::path("/foo/bar.txt").extension() == ".txt");
    CHECK(fs::path("/foo/bar").extension() == "");
    CHECK(fs::path("/foo/.profile").extension() == "");
    CHECK(fs::path(".bar").extension() == "");
    CHECK(fs::path("..bar").extension() == ".bar");
}

TEST_CASE( "fs::path - Query", "[class][path][filesystem][query]" ) {
   // has_relative_path()
    CHECK(!fs::path("").has_relative_path());
    CHECK(!fs::path("/").has_relative_path());
    CHECK(fs::path("/foo").has_relative_path());

    // has_parent_path()
    CHECK(!fs::path("").has_parent_path());
    CHECK(!fs::path(".").has_parent_path());
    CHECK(!fs::path("..").has_parent_path());  // unintuitive but as defined in the standard
    CHECK(!fs::path("foo").has_parent_path());
    CHECK(fs::path("/").has_parent_path());
    CHECK(fs::path("/foo").has_parent_path());
    CHECK(fs::path("foo/").has_parent_path());
    CHECK(fs::path("/foo/").has_parent_path());

    // has_filename()
    CHECK(fs::path("foo").has_filename());
    CHECK(fs::path("foo/bar").has_filename());
    CHECK(!fs::path("/foo/bar/").has_filename());

    // has_stem()
    CHECK(fs::path("foo").has_stem());
    CHECK(fs::path("foo.bar").has_stem());
    CHECK(fs::path(".profile").has_stem());
    CHECK(!fs::path("/foo/").has_stem());

    // has_extension()
    CHECK(!fs::path("foo").has_extension());
    CHECK(fs::path("foo.bar").has_extension());
    CHECK(!fs::path(".profile").has_extension());

    // is_absolute()
    CHECK(!fs::path("foo/bar").is_absolute());
    CHECK(fs::path("/foo").is_absolute());

    // is_relative()
    CHECK(fs::path("foo/bar").is_relative());
	CHECK(!fs::path("/foo").is_relative());

}

TEST_CASE( "fs::path - Non member functions", "[class][path][filesystem][non-member-function]" )
{
    fs::path p1("foo/bar");
    fs::path p2("some/other");
    fs::swap(p1, p2);
    CHECK(p1 == "some/other");
    CHECK(p2 == "foo/bar");
    CHECK(p2 < p1);
    CHECK(p2 <= p1);
    CHECK(p1 <= p1);
    CHECK(!(p1 < p2));
    CHECK(!(p1 <= p2));
    CHECK(p1 > p2);
    CHECK(p1 >= p2);
    CHECK(p1 >= p1);
    CHECK(!(p2 > p1));
    CHECK(!(p2 >= p1));
    CHECK(p1 != p2);
    CHECK((p1 / p2).string() == "some/other/foo/bar");
}

TEST_CASE( "fs::path - path compare", "[class][path][filesystem][compare]" )
{
    CHECK(fs::path("/foo/b").compare("/foo/a") > 0);
    CHECK(fs::path("/foo/b").compare("/foo/b") == 0);
    CHECK(fs::path("/foo/b").compare("/foo/c") < 0);

    CHECK(fs::path("/foo/b").compare(std::string("/foo/a")) > 0);
    CHECK(fs::path("/foo/b").compare(std::string("/foo/b")) == 0);
    CHECK(fs::path("/foo/b").compare(std::string("/foo/c")) < 0);

    CHECK(fs::path("/foo/b").compare(fs::path("/foo/a")) > 0);
    CHECK(fs::path("/foo/b").compare(fs::path("/foo/b")) == 0);
    CHECK(fs::path("/foo/b").compare(fs::path("/foo/c")) < 0);

    CHECK(fs::path("/a/b/").compare("/a/b/") == 0);
    CHECK(fs::path("/a/b/").compare("/a/b/c") < 0);
    CHECK(fs::path("/a/b/../b").compare("/a/b") > 0);
    CHECK(fs::path("/a/b").compare("/a/b/.") < 0);
    CHECK(fs::path("/a/b/").compare("a/c") > 0);

}

TEST_CASE( "fs::path - Generation", "[class][path][filesystem][generation][.]" ) {

    // lexically_normal()
    CHECK(fs::path("foo/./bar/..").lexically_normal() == "foo/");
    CHECK(fs::path("foo/.///bar/../").lexically_normal() == "foo/");
    CHECK(fs::path("/foo/../..").lexically_normal() == "/");
    CHECK(fs::path("foo/..").lexically_normal() == ".");
    CHECK(fs::path("ab/cd/ef/../../qw").lexically_normal() == "ab/qw");
    CHECK(fs::path("a/b/../../../c").lexically_normal() == "../c");
    CHECK(fs::path("../").lexically_normal() == "..");

	// lexically_relative()
//     CHECK(fs::path("/a/d").lexically_relative("/a/b/c") == "../../d");
//     CHECK(fs::path("/a/b/c").lexically_relative("/a/d") == "../b/c");
//     CHECK(fs::path("a/b/c").lexically_relative("a") == "b/c");
//     CHECK(fs::path("a/b/c").lexically_relative("a/b/c/x/y") == "../..");
//     CHECK(fs::path("a/b/c").lexically_relative("a/b/c") == ".");
//     CHECK(fs::path("a/b").lexically_relative("c/d") == "../../a/b");
//     CHECK(fs::path("a/b").lexically_relative("a/") == "b");

//  // lexically_proximate()
//     CHECK(fs::path("/a/d").lexically_proximate("/a/b/c") == "../../d");
//     CHECK(fs::path("a/d").lexically_proximate("/a/b/c") == "a/d");

//     CHECK(fs::path("/foo").lexically_proximate("bar") == "/foo");
//     CHECK(fs::path("foo").lexically_proximate("/bar") == "foo");
}

static std::string iterateResult(const fs::path& path)
{
    std::ostringstream result;
    for (fs::path::iterator i = path.begin(); i != path.end(); ++i) {
        if (i != path.begin()) {
            result << ",";
        }
        result << i->string();
    }
    return result.str();
}

std::string reverseIterateResult(const fs::path& path)
{
    std::ostringstream result;
    fs::path::iterator iter = path.end();
    bool first = true;
    if (iter != path.begin()) {
        do {
            --iter;
            if (!first) {
                result << ",";
            }
            first = false;
            result << iter->string();
        } while (iter != path.begin());
    }
    return result.str();
}

TEST_CASE("fs.path.itr - path iterators", "[filesystem][class][path][iterator]")
{
    CHECK(iterateResult(fs::path()).empty());
    CHECK("." == iterateResult(fs::path(".")));
    CHECK(".." == iterateResult(fs::path("..")));
    CHECK("foo" == iterateResult(fs::path("foo")));
    CHECK("/" == iterateResult(fs::path("/")));
    CHECK("/,foo" == iterateResult(fs::path("/foo")));
    CHECK("foo," == iterateResult(fs::path("foo/")));
    CHECK("/,foo," == iterateResult(fs::path("/foo/")));
    CHECK("foo,bar" == iterateResult(fs::path("foo/bar")));
    CHECK("/,foo,bar" == iterateResult(fs::path("/foo/bar")));
    CHECK("/,foo,bar" == iterateResult(fs::path("///foo/bar")));

    CHECK(reverseIterateResult(fs::path()).empty());
    CHECK("." == reverseIterateResult(fs::path(".")));
    CHECK(".." == reverseIterateResult(fs::path("..")));
    CHECK("foo" == reverseIterateResult(fs::path("foo")));
    CHECK("/" == reverseIterateResult(fs::path("/")));
    CHECK("foo,/" == reverseIterateResult(fs::path("/foo")));
    CHECK(",foo" == reverseIterateResult(fs::path("foo/")));
    CHECK(",foo,/" == reverseIterateResult(fs::path("/foo/")));
    CHECK("bar,foo" == reverseIterateResult(fs::path("foo/bar")));
    CHECK("bar,foo,/" == reverseIterateResult(fs::path("/foo/bar")));

    // Redundant slashes reduced to one
    CHECK("bar,foo,/" == reverseIterateResult(fs::path("///foo/bar")));

    CHECK(",bar,foo,/" == reverseIterateResult(fs::path("/foo/bar///")));
    CHECK(",..,bar,.,foo" == reverseIterateResult(fs::path("foo/.///bar/../")));


    {
        fs::path p1 = "/foo/bar/test.txt";
        fs::path p2 = "///";
        for (auto pe : p1) {
            p2 /= pe;
        }
        CHECK(p1 == p2);
        CHECK("bar" == *(--fs::path("/foo/bar").end()));
        auto p = fs::path("/foo/bar");
        auto pi = p.end();
        pi--;
        CHECK("bar" == *pi);
    }
}
