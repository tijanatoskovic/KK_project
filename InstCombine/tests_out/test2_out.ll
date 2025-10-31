; ModuleID = 'tests/test2.ll'
source_filename = "tests/test2.ll"

define i32 @test_add_chain(i32 %x) {
  %add1 = add i32 %x, 1
  %1 = add i32 %x, 3
  ret i32 %1
}
