/// Keep <Common/assert_cast.h> the first include: it compiles its type check only under DEBUG_OR_SANITIZER_BUILD,
/// so it has to define that macro itself instead of relying on whatever was included before it.
#include <Common/assert_cast.h>

#ifdef DEBUG_OR_SANITIZER_BUILD
constexpr bool assert_cast_header_enables_type_check = true;
#else
constexpr bool assert_cast_header_enables_type_check = false;
#endif

#include <base/sanitizer_defs.h>

#ifdef DEBUG_OR_SANITIZER_BUILD
constexpr bool build_requires_type_check = true;
#else
constexpr bool build_requires_type_check = false;
#endif

#include <gtest/gtest.h>

TEST(AssertCast, TypeCheckDoesNotDependOnIncludeOrder)
{
    EXPECT_EQ(assert_cast_header_enables_type_check, build_requires_type_check)
        << "assert_cast is a bare static_cast in a translation unit that includes <Common/assert_cast.h> first";
}
