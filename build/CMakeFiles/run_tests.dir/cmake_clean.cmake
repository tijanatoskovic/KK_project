file(REMOVE_RECURSE
  "CMakeFiles/run_tests"
  "tests_out/test1.ll"
  "tests_out/test1_out.ll"
  "tests_out/test2.ll"
  "tests_out/test2_out.ll"
  "tests_out/test3.ll"
  "tests_out/test3_out.ll"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/run_tests.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
